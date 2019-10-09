// ������ DLL �ļ���

#include "stdafx.h"
#include "QuaryList.h"

#if DEBUG

#include <iostream>

#endif

using namespace FQuaryList;

//�ҵ��������һ������ͬ��λ
// @param a �ֽ�A
// @param b �ֽ�B
// @param mask �ж���Ҫ�Ƚ�λ�õ�mask
Byte getFirstDifferentBit(Byte a, Byte b, Byte mask)		
{
	Byte set;

	for (set = 0x80; (mask & set) == 0; set >>= 1);		//ȡ�������һλ��Чλ

	while (mask & set)
	{
		if ((a & set) != (b & set))
			return set;
		set >>= 1;
	}
	return 0;
}

//��ȡֵΪTure��1����λ��
int getTrueBitsCount(Byte b)
{
	Byte set;
	int count = 0;

	for (set = 0x80; set; set >>= 1)
		if (b & set)
			count++;

	return count;
}

//�����ֽڴ�����0��ֹ
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

//��ָ��λ��ʼ��ȡmask����0��ֹ
// @param b			�����ֽ����飬����ȷ����ֹ�ֽڣ���0x00��ֹ
// @param offset	Ҫ��ȡ����ʼbitλ����λΪ1������λΪ0���Ӹ�λ��ʼ��ȡ
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
	while (!que.empty())				//�������нڵ�	
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

//�ָ����нڵ�	
// @param node	Ҫ�ָ�Ľڵ�
// @param bit	Ҫ�ָ��bitλ����Ϊ1������λΪ0
// @param index	Ҫ�ָ��bit���ڵ�mask�����±�
void FQuaryList::RadixTree::SplitNode(TNode * node, Byte b, int index)
{
	TNode * newNode;
	Byte * newmask, *newbits;

	if (b == 1)			//����mask,�����Խ
	{
		newmask = copyBytes(node->mask + index + 1);		//�ָ�λ�ǵ�ǰ�ֽ����һλ
		newbits = node->bits + index + 1;
	}
	else
	{
		newmask = copyBytes(node->mask + index);
		newmask[0] &= b - 1;
		newbits = node->bits + index;
	}

	node->mask[index] &= 0x100 - (b << 1);					//����ȡmaskֵ
	node->mask[index + 1] = 0;

	newNode = new TNode();								//�½��ڵ㣬���ԭ�нڵ�
	newNode->bits = newbits;
	newNode->mask = newmask;
	newNode->data = node->data;
	newNode->leftChild = node->leftChild;
	newNode->rightChild = node->rightChild;

	if (node->bits[index] & b)									//���½ڵ���Ϊԭ�нڵ���ӽڵ�
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

//�����½ڵ�
// @param str	Ҫ�����Ľڵ��ʶ��bitֵ��ָ��ָ���һ����Ч�ֽ�
// @param bit	Ҫ�����ڵ����ʼbitλ����Ϊ1������λΪ0
RadixTree::TNode * FQuaryList::RadixTree::NewNode(char * str, Byte bit)
{
	TNode * r;
	Byte * newmask, * newbits;

	newbits = copyBytes((Byte *)(str));						//����bitλ
	usedBits.push_back(newbits);							//¼���ڴ����

	newmask = copyMasks((Byte *)(str), bit);				//����mask

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
		for (i = 0; temp->mask[i]; ++i, ++k)							//���м�ڵ����ƥ��
		{
			if ((str[k] & temp->mask[i]) != (temp->bits[i] & temp->mask[i]))			//Ŀ���ַ������м�ڵ��ֵ��ƥ��
			{
				bit = getFirstDifferentBit(str[k], temp->bits[i], temp->mask[i]);		//�ҳ���ƥ���λ��

				SplitNode(temp, bit, i);		//����ڵ�
			}
			bitCount += getTrueBitsCount(temp->mask[i]);
		}
		//Ŀ���ַ����͵�ǰ�м�ڵ���ȫƥ��
		parent = temp;
		k = bitCount >> 3;							//ȷ����ǰƥ����ַ����±�
		if (str[k] == '\0')							//�ַ����Ѿ�ƥ����������ַ����Ѵ���
			break;

		bit = 0x80 >> (bitCount & 0x07);			//ȷ����ǰƥ��λ
		if (str[k] & bit)							//������һλ��ֵѡ����������������
			temp = temp->rightChild;
		else
			temp = temp->leftChild;

		bitCount++;									//���һλ
		k = bitCount >> 3;							//����һ���±�
	}

	if (temp == nullptr)							//��Ҫ�����ⲿ�ڵ�
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
	else											//��Ҫ�����ڲ��ڵ�
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
		for (i = 0; temp->mask[i]; ++i, ++k)							//���м�ڵ����ƥ��
		{
			if ((str[k] & temp->mask[i]) != (temp->bits[i] & temp->mask[i]))	//Ŀ���ַ������м�ڵ��ֵ��ƥ��
			{
				return INVALIDDATA;
			}
			bitCount += getTrueBitsCount(temp->mask[i]);
		}
		k = bitCount >> 3;					//ȷ����ǰƥ����ַ����±�
		if (str[k] == '\0')							//�ַ���ƥ�����
			break;

		bit = 0x80 >> (bitCount & 0x07);			//ȷ����ǰƥ��λ
		if (str[k] & bit)							//������һλ��ֵѡ����������������
			temp = temp->rightChild;
		else
			temp = temp->leftChild;

		bitCount++;									//���һλ
		k = bitCount >> 3;							//����һ���±�
	}
	if (temp == nullptr || temp->data == INVALIDDATA)
		return INVALIDDATA;
	else
		return temp->data;
}
