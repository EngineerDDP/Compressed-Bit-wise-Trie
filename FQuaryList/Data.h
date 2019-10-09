#pragma once

using namespace System::Collections::Generic;
using namespace System;

namespace FQuaryList {


	public ref struct Index {
		System::Int32 page;
		System::Int32 loc;
	};

	public ref struct Location			//����λ�ã�ҳ��+���
	{
		Int32 Page;						//ҳ��
		LinkedList<Int32> ^ Blocks;		//���
		Location(int page, int block)
		{
			Blocks = gcnew LinkedList<Int32>();
			Page = page;
			Blocks->AddLast(block);
		}
	};

	public ref class Data			//������Ϣ�ڵ�
	{
	private:
		String ^ str;						//����У��
		LinkedList<Location ^> ^ indexList;	//�����б�
	public:
		Data(String ^ s)
		{
			str = s;
			indexList = gcnew LinkedList<Location ^>();
		}
		Data(String ^ s, Int32 page, Int32 block) : Data(s)
		{
			indexList->AddLast(gcnew Location(page, block));
		}
		~Data()
		{
			
		}
		void Insert(Int32 page, Int32 block)
		{
			for each (auto i in indexList)
			{
				if (i->Page == page)
				{
					for each (auto j in i->Blocks)
						if (j == block)
							return;
					i->Blocks->AddLast(block);
					return;
				}
			}
			indexList->AddLast(gcnew Location(page, block));
		}
		LinkedList<Location ^> ^ QuaryData()
		{
			return indexList;
		}
		String ^ Check()
		{
			return str;
		}
		void Delete(int page, int block)
		{
		}
		Int32 BlockCounts()
		{
			int r = 0;

			for each (auto i in indexList)
			{
				for each (auto j in i->Blocks)
					r++;
			}
			return r;
		}
	};

}