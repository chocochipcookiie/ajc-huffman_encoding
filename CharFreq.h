#ifndef CHARFREQ_H
#define CHARFREQ_H

#include <iostream>
#include <string>

using namespace std;

class CharFreq
{
	private:
		int freq;
		string key;
	public:
		CharFreq() { }
		CharFreq(int f, string c) : freq(f), key(c) {}
		CharFreq(const CharFreq& other) : freq(other.freq), key(other.key) {}
		string getKey() const { return key; }
		int getFreq() const { return freq; }
		void setValues(string c, int i);
		bool operator<(const CharFreq & other) const;
};

void CharFreq::setValues(string c, int i)
{
	freq = i;
	key = c;
}

bool CharFreq::operator<(const CharFreq &other) const {
	return this->getFreq() < other.getFreq();
}


#endif CHARFREQ_H