#ifndef WORD
#define WORD

class Word;

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "Sentence.h"

using namespace std;

class Word{
	public:
		Word();
		Word(int len);
		Word(const Word& copier);
		Word(char* array, int len);
		~Word();
		Word& operator--(int);
		Word& operator--();
		Word& operator++();
		Word& operator++(int);
		Word& operator+(int i);
		Sentence operator+(Word& second);
		Sentence operator+(Sentence& original);
		Word& operator=(const Word& copier);
		friend ostream& operator<<(ostream& out, const Word& printer); 
		bool isInPig;
		bool isInPigVowel;
		bool allCaps;
	private:
		char* actualWord;
		int wordLen;
		int pigCharOffset;
};

#endif
