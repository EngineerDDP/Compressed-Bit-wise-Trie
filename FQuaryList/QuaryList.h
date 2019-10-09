
#pragma once

#include <list>
#include <string>
#include <queue>

#define INVALIDDATA -1
#define INSERTSUCCESS -2

namespace FQuaryList {

	typedef unsigned char Byte;

	public class RadixTree
	{
	public:
		struct TNode {		//索引树节点	
			Byte * bits;
			Byte * mask;
			TNode * leftChild;
			TNode * rightChild;
			int data;
		};

	private:
		TNode * root;					//根节点
		std::list<Byte *> usedBits;		//bits内存管理
		unsigned int wordCount;

	public:
		RadixTree();
		~RadixTree();
	private:
		void SplitNode(TNode * node, Byte bit, int index);
		TNode * NewNode(char * str, Byte bit);
	public:
		int Insert(char * str, int index);		//插入数据
		void Delete(char * str);		//删除单词
		int Quary(char * str);			//查询单词
	};
}
