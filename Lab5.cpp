#include <iostream>
#include "CreateFrequencyQueue.h"
#include "CreateHuffmanTree.h"
#include "ReadBinFile.h"

using namespace std;

int main()
{
	CreateFrequencyQueue c("Frequencies.txt");
	CreateHuffmanTree nuHuffman;

	c.readFreqFile();
	nuHuffman.createEncode(c.returnQueue());

	ReadBinFile r("Huffman.bin", "Output.txt", nuHuffman.returnTree());
	r.readFile();
	return 0;
} 