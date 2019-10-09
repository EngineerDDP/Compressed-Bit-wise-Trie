// 这是主 DLL 文件。

#include "stdafx.h"
#include "QuaryList.h"

#if DEBUG

#include <iostream>

#endif

using namespace FQuaryList;

//找到从左起第一个不相同的位
// @param a 字节A
// @param b 字节B
// @param mask 判断需要比较位置的mask
Byte getFirstDifferentBit(Byte a, Byte b, Byte mask)		
{
	Byte set;

	for (set = 0x80; (mask & set) == 0; set >>= 1);		//取到左起第一位有效位

	while (mask & set)
	{
		if ((a & set) != (b & set))
			return set;
		set >>= 1;
	}
	return 0;
}

//获取值为Ture（1）的位数
int getTrueBitsCount(Byte b)
{
	Byte set;
	int count = 0;

	for (set = 0x80; set; set >>= 1)
		if (b & set)
			count++;

	return count;
}

//复制字节串，遇0截止
Byte * copyBytes(Byte * b)						
{
	int i, k;
	Byte * r;

	for (i = 0; b[i] != 0; ++i);
	i++;
	r = new Byte[i];
	for (k = 0; k < i; k++)
		r[k] = b[k];

	return r;
}

//从指定位开始截取mask，遇0截止
// @param b			参照字节数组，用于确定截止字节，遇0x00截止
// @param offset	要截取的起始bit位，该位为1，其余位为0，从该位开始截取
Byte * copyMasks(Byte * b, Byte offset)			
{
	int i, k;
	Byte * r;
	for (i = 0; b[i] != 0; ++i);
	r = new Byte[i + 1];

	r[0] = offset + offset - 1;
	for (k = 1; k < i; ++k)
		r[k] = 0xff;
	r[i] = 0;
	return r;
}

FQuaryList::RadixTree::RadixTree()
{
	root = nullptr;
}

FQuaryList::RadixTree::~RadixTree()
{
	using namespace std;
	
	queue<TNode *> que;
	TNode * temp;
	if(root != nullptr)
		que.push(root);
	while (!que.empty())				//析构所有节点	
	{	
		temp = que.front();
		que.pop();
		if(temp->leftChild != nullptr)
			que.push(temp->leftChild);
		if(temp->rightChild != nullptr)
			que.push(temp->rightChild);

		delete[] temp->mask;
		delete temp;
	}
	for (auto b : usedBits)
		delete[] b;
}

//分割已有节点	
// @param node	要分割的节点
// @param bit	要分割的bit位，设为1，其余位为0
// @param index	要分割的bit所在的mask数组下标
void FQuaryList::RadixTree::SplitNode(TNode * node, Byte b, int index)
{
	TNode * newNode;
	Byte * newmask, *newbits;

	if (b == 1)			//复制mask,处理跨越
	{
		newmask = copyBytes(node->mask + index + 1);		//分割位是当前字节最后一位
		newbits = node->bits + index + 1;
	}
	else
	{
		newmask = copyBytes(node->mask + index);
		newmask[0] &= b - 1;
		newbits = node->bits + index;
	}

	node->mask[index] &= 0x100 - (b << 1);					//重新取mask值
	node->mask[index + 1] = 0;

	newNode = new TNode();								//新建节点，替代原有节点
	newNode->bits = newbits;
	newNode->mask = newmask;
	newNode->data = node->data;
	newNode->leftChild = node->leftChild;
	newNode->rightChild = node->rightChild;

	if (node->bits[index] & b)									//将新节点作为原有节点的子节点
	{
		node->rightChild = newNode;
		node->leftChild = nullptr;
	}
	else
	{
		node->leftChild = newNode;
		node->rightChild = nullptr;
	}
	node->data = INVALIDDATA;
}

//创建新节点
// @param str	要创建的节点的识别bit值，指针指向第一个有效字节
// @param bit	要创建节点的起始bit位，设为1，其余位为0
RadixTree::TNode * FQuaryList::RadixTree::NewNode(char * str, Byte bit)
{
	TNode * r;
	Byte * newmask, * newbits;

	newbits = copyBytes((Byte *)(str));						//复制bit位
	usedBits.push_back(newbits);							//录入内存管理

	newmask = copyMasks((Byte *)(str), bit);				//复制mask

	r = new TNode();
	r->bits = newbits;
	r->mask = newmask;

	return r;
}

int FQuaryList::RadixTree::Insert(char * str, int index)
{
	TNode * temp,* parent, * newNode;
	int i, k = 0;
	int bitCount = 0;
	Byte bit;
	temp = root;
	parent = temp;

	while (temp != nullptr)
	{
		for (i = 0; temp->mask[i]; ++i, ++k)							//和中间节点进行匹配
		{
			if ((str[k] & temp->mask[i]) != (temp->bits[i] & temp->mask[i]))			//目标字符串和中间节点的值不匹配
			{
				bit = getFirstDifferentBit(str[k], temp->bits[i], temp->mask[i]);		//找出不匹配的位置

				SplitNode(temp, bit, i);		//分离节点
			}
			bitCount += getTrueBitsCount(temp->mask[i]);
		}
		//目标字符串和当前中间节点完全匹配
		parent = temp;
		k = bitCount >> 3;							//确定当前匹配的字符串下标
		if (str[k] == '\0')							//字符串已经匹配结束，该字符串已存在
			break;

		bit = 0x80 >> (bitCount & 0x07);			//确定当前匹配位
		if (str[k] & bit)							//按照下一位的值选择左子树或右子树
			temp = temp->rightChild;
		else
			temp = temp->leftChild;

		bitCount++;									//提高一位
		k = bitCount >> 3;							//提升一个下标
	}

	if (temp == nullptr)							//需要创建外部节点
	{
		newNode = NewNode(str + k, 0x80 >> (bitCount & 0x07));
		if (root == nullptr)
			root = newNode;
		else if (str[(bitCount - 1) >> 3] & bit)
			parent->rightChild = newNode;
		else
			parent->leftChild = newNode;
		newNode->data = index;
	}
	else											//需要更新内部节点
	{
		if (temp->data == INVALIDDATA)
			temp->data = index;
		else
			return temp->data;
	}
	return INSERTSUCCESS;
}

int FQuaryList::RadixTree::Quary(char * str)
{
	TNode * temp = root;
	int i, k = 0;
	int bitCount = 0;
	Byte bit;

	while (temp != nullptr)
	{
		for (i = 0; temp->mask[i]; ++i, ++k)							//和中间节点进行匹配
		{
			if ((str[k] & temp->mask[i]) != (temp->bits[i] & temp->mask[i]))	//目标字符串和中间节点的值不匹配
			{
				return INVALIDDATA;
			}
			bitCount += getTrueBitsCount(temp->mask[i]);
		}
		k = bitCount >> 3;					//确定当前匹配的字符串下标
		if (str[k] == '\0')							//字符串匹配结束
			break;

		bit = 0x80 >> (bitCount & 0x07);			//确定当前匹配位
		if (str[k] & bit)							//按照下一位的值选择左子树或右子树
			temp = temp->rightChild;
		else
			temp = temp->leftChild;

		bitCount++;									//提高一位
		k = bitCount >> 3;							//提升一个下标
	}
	if (temp == nullptr || temp->data == INVALIDDATA)
		return INVALIDDATA;
	else
		return temp->data;
}
