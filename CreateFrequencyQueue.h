#ifndef CREATEFREQUENCYQUEUE_H
#define CREATEFREQUENCYQUEUE_H

#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <memory>
#include <regex>
#include "CharFreq.h"

using namespace std;

const string CHAR_REGEX = "\<(.*?)>(.*?)\<(.*?)>";

class CFComparison
{
	public:
		bool operator() (const CharFreq& lhs, const CharFreq& rhs) const
		{
			return lhs.getFreq() < rhs.getFreq();
		}
};

class CreateFrequencyQueue
{
	private:
		priority_queue<CharFreq, vector<CharFreq>, CFComparison> freqQueue;
		string freqFilename;
	public:
		CreateFrequencyQueue(string fName) : freqFilename(fName) {};
		void insertNewEntry(int i, string c);
		void readFreqFile();
		void parseFile(string temp);
		priority_queue<CharFreq, vector<CharFreq>, CFComparison> returnQueue() { return freqQueue; }
		void printQueue();
};

void CreateFrequencyQueue::insertNewEntry(int i, string c)
{
	CharFreq r(i, c);
	freqQueue.push(r);
}

void CreateFrequencyQueue::readFreqFile()
{
	ifstream fFile;
	string temp;

	fFile.open(freqFilename.c_str());

	while (!(fFile.peek() == EOF))
	{
		//cout << "File is open..." << endl;
		getline(fFile, temp);
		//cout << "File line: " << temp << endl;
		parseFile(temp);
	}
	fFile.close();
}

void CreateFrequencyQueue::parseFile(string fileLine)
{
	regex charPattern(CHAR_REGEX);
	sregex_token_iterator end;
	string temp = "", freqNum = "";

	if (regex_search(fileLine.begin(), fileLine.end(), charPattern))
	{
		//cout << "Found pattern..." << endl;
		for (sregex_token_iterator iter(fileLine.begin(), fileLine.end(), charPattern); iter != end; ++iter)
		{
			if ((*iter).length() > 0)
			{
				temp += static_cast<string>(*iter)[1];				
			}
		}
		for (sregex_token_iterator iter(fileLine.begin(), fileLine.end(), charPattern, 2); iter != end; ++iter)
		{
			if ((*iter).length() > 0)
			{
				freqNum += static_cast<string>(*iter);
			}
		}
		/*cout << "Character: " << temp << endl;
		cout << "Frequency Num: " << freqNum << endl;*/
		insertNewEntry(stoi(freqNum), temp);
	}
}

void CreateFrequencyQueue::printQueue()
{
	while (!freqQueue.empty())
	{
		cout << freqQueue.top().getKey() << " " << freqQueue.top().getFreq() << endl;
		freqQueue.pop();
	}
}
#endif CREATEFREQUENCYQUEUE_H