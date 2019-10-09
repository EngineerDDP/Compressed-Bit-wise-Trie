
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
		struct TNode {		//�������ڵ�	
			Byte * bits;
			Byte * mask;
			TNode * leftChild;
			TNode * rightChild;
			int data;
		};

	private:
		TNode * root;					//���ڵ�
		std::list<Byte *> usedBits;		//bits�ڴ����
		unsigned int wordCount;

	public:
		RadixTree();
		~RadixTree();
	private:
		void SplitNode(TNode * node, Byte bit, int index);
		TNode * NewNode(char * str, Byte bit);
	public:
		int Insert(char * str, int index);		//��������
		void Delete(char * str);		//ɾ������
		int Quary(char * str);			//��ѯ����
	};
}
