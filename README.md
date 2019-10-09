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
                        q.AddWord(str, 1, count++);
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
