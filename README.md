# Compressed-Bit-wise-Trie
A compressed bit-wise Trie used for fast searching in inverted index. Like a primitive search engine.

## Structure
### ConsoleTest
Used for testing C++ Library. <br>
Records query time.
### Window
Graphic User Interface Project for FQuaryList Library.
### FQuaryList
C++ Library for fast word quering and locating.

## Usage
```
using System;
using FQuaryList;
using System.IO;
using System.Diagnostics;

namespace ConsoleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            FQuary q = new FQuary();

            using (FileStream fs = File.OpenRead("test.txt"))
            {
                StreamReader sr = new StreamReader(fs);
                while (!sr.EndOfStream)
                {
                    c = (char)(sr.Read());
                    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                        str += c;
                    else if (str != "")
                    {
                        q.AddWord(str, 1, count++); // Parameters are "word to query", "page No." and "block No.".
                        str = "";
                    }
                }

                //q.DeSerialize("trie.library");  //Deserialize from saved trie if possible.

                Data d = q.QuaryWord("the");

                if (d != null)
                {
                    foreach (var result in d.QuaryData())
                    {
                        foreach (var block in result.Blocks)
                        {
                            Console.WriteLine("Get result in Page {0}, Block {1}", result.Page, block); //Print result
                        }
                    }
                }

                q.Serialize("trie.library");  //Serialize and save query trie for further usage.
            }
        }
    }
}
```
Use *q.AddWord(word, page, block)* to add page and block informations. <br>
Use *q.QuaryWord(string)* to quary a word and find the information saved in previous.<br>
Node: The trie doesn't contains extra information except page number and block number.

## Algorithm Result

* The algorithm has *O(1)* of querying time in the best case.
* The algorithm has *O(n)* of querying time in the worst case.(n stands for length of the word in bits)
* Querying time only related with the length of a word in bits.
