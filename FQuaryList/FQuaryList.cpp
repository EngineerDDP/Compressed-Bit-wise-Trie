#include "Stdafx.h"
#include "FQuaryList.h"

#include <fstream>

using System::Collections::ICollection;
using namespace System::IO;

char * to_Cstr(System::String ^ str)
{
	int k = 0;
	array<unsigned char> ^ b = System::Text::Encoding::Default->GetBytes(str);
	char * c = new char[b->Length + 1];

	for each(auto i in b)
		c[k++] = i;

	c[k] = 0;

	return c;
}

FQuaryList::FQuary::FQuary()
{
	catalog = new RadixTree();
	content = gcnew ArrayList();
}

FQuaryList::FQuary::~FQuary()
{
	catalog->~RadixTree();
}


Void FQuaryList::FQuary::AddWord(System::String ^ str, System::Int32 page, System::Int32 block)
{
	int index = content->Count;			//先取下标
	int j = 0;
	char * c = to_Cstr(str);

	j = catalog->Insert(c, index);

	if (j == INSERTSUCCESS)				//插入成功后再创建对象
	{
		content->Add(gcnew Data(str, page, block));
	}
	else								//已存在无需再插入,更新对象
	{
		static_cast<Data ^>(content[j])->Insert(page, block);
	}
}

FQuaryList::Data ^ FQuaryList::FQuary::QuaryWord(System::String ^ str)
{
	int j = 0;
	char * c = to_Cstr(str);

	j = catalog->Quary(c);
	if (j == INVALIDDATA)
		return nullptr;
	else
		return static_cast<Data ^>(content[j]);
}

Void FQuaryList::FQuary::Serialize(System::String ^ filename)
{
	using namespace std;

	fstream fs;
	fs.open(to_Cstr(filename), ios::trunc | ios::out);

	if (fs.is_open())
	{
		for each(Data ^ i in content)
		{
			fs << to_Cstr(i->Check()) << ' ';
			fs << i->QuaryData()->Count << endl;
			for each(auto j in i->QuaryData())
			{
				fs << j->Page << ' ';
				fs << j->Blocks->Count << ' ';
				for each(auto k in j->Blocks)
				{
					fs << k << ' ';
				}
				fs << endl;
			}
		}

		fs.close();
	}
}

Void FQuaryList::FQuary::DeSerialize(System::String ^ filename)
{
	using namespace std;

	fstream fs;
	fs.open(to_Cstr(filename), ios::_Noreplace | ios::in);

	if (fs.is_open())
	{

		char * word = new char[256];
		int page, block = 0;
		int i = 0, j = 0;
		Data ^ data;

		while (fs >> word)
		{
			data = gcnew Data(gcnew String(word));
			fs >> i;
			while (i > 0)
			{
				fs >> page;
				fs >> j;
				while (j > 0)
				{
					fs >> block;
					data->Insert(page, block);
					j--;
				}
				i--;
			}
			catalog->Insert(word, content->Count);
			content->Add(data);
		}

		fs.close();
	}
}

Int32 FQuaryList::FQuary::QuaryWordCount()
{
	return content->Count;
}


