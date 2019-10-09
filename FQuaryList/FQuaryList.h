#pragma once

#include "QuaryList.h"
#include "Data.h"

using namespace System;
using namespace System::Collections;

namespace FQuaryList {

	public ref class FQuary 
	{
	private:
		RadixTree * catalog;		//Ë÷Òý
		ArrayList ^ content;		//ÄÚÈÝ
	public:
		FQuary();
		~FQuary();
		Void AddWord(System::String ^ str, System::Int32 page, System::Int32 block);
		Data ^ QuaryWord(System::String ^ str);
		Void Serialize(System::String ^ filename);
		Void DeSerialize(System::String ^ filename);
		Int32 QuaryWordCount();
	};

	public ref class WordNotFoundException : Exception
	{

	};
}