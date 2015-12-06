#ifndef READBINFILE_H
#define READBINFILE_H

#include <iostream>
#include <fstream>
#include <set>
#include <bitset>
#include "TreeNode.h"
#include "CharFreq.h"

using namespace std;

const int BITSET_SIZE = 8;
class ReadBinFile
{
	private:
		string inputFilename;
		string outputFilename;
		multiset<shared_ptr<TreeNode <CharFreq> >, NodeComparison> hTree;
	public:
		ReadBinFile(string iFile, string oFile, multiset<shared_ptr<TreeNode<CharFreq> >, NodeComparison> h);
		void readFile();
		void parseFile(unsigned char* buffer, streampos size);
		void writeToFile();
		shared_ptr<TreeNode <CharFreq> > traverseTree(bool c, shared_ptr<TreeNode<CharFreq> > root);
		bool getChar(shared_ptr<TreeNode<CharFreq> > nu, ofstream &output);
};

ReadBinFile::ReadBinFile(string iFile, string oFile, multiset<shared_ptr<TreeNode<CharFreq> >, NodeComparison> h)
{
	inputFilename = iFile;
	outputFilename = oFile;
	hTree = h;
}

void ReadBinFile::readFile()
{
	ifstream bOut(inputFilename, ios::binary | ios::in);
	unsigned char* buffer;
	streampos size;

	if (bOut.is_open())
	{
		bOut.seekg(0, ios::end);
		size = bOut.tellg();
		buffer = new unsigned char[size];
		bOut.seekg(0, ios::beg);
		bOut.read((char*)buffer, size);
		parseFile(buffer, size);
		delete[] buffer;
	}
	
	bOut.close();
}

shared_ptr<TreeNode <CharFreq> > ReadBinFile::traverseTree(bool c, shared_ptr<TreeNode<CharFreq> > root)
{
	if (c == 0)
	{
		//cout << "0" << endl;
		return root->left;
	}
	else if (c == 1)
	{
		//cout << "1" << endl;
		return root->right;
	}
	return NULL;
}

bool ReadBinFile::getChar(shared_ptr<TreeNode<CharFreq> > nu, ofstream &output)
{
	if (nu->left == NULL && nu->right == NULL)
	{
		//cout << nu->getData().getKey();
		output << nu->getData().getKey();
		return true;
	}
	return false;
}

void ReadBinFile::parseFile(unsigned char* buffer, streampos size)
{
	int arraySize = (int)size;
	bool temp;
	multiset<shared_ptr<TreeNode<CharFreq> >, NodeComparison>::iterator root = hTree.begin();
	shared_ptr<TreeNode<CharFreq> > current = *root;
	ofstream output(outputFilename, ofstream::out);

	for (int i = 0; i < arraySize; i++)
	{
		//cout << "Char: " << *(buffer + i) << endl;
		int input = (int)*(buffer + i);
		//cout << input << endl;
		bitset<BITSET_SIZE> bTemp(input);
		//cout << bTemp << endl;

		for (int j = 0; j < BITSET_SIZE ; j++)
		{
			temp = bTemp[BITSET_SIZE - j - 1];
			//cout << temp;
			if (getChar(current, output))
			{
				current = *root;
			}
			current = traverseTree(temp, current);
		}
	}
	output.close();

	//cout << temp;
}

void ReadBinFile::writeToFile()
{

}

#endif READBINFILE_H