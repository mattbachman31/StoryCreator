#include "Word.h"

using namespace std;

Word::Word(){
	actualWord = new char[7];
	wordLen = 6;
	isInPig = false;
	isInPigVowel = false;
	pigCharOffset = 0;
	allCaps = false;
	actualWord[0] = 'i';
	actualWord[1] = 'g';
	actualWord[2] = 'u';
	actualWord[3] = 'a';
	actualWord[4] = 'n';
	actualWord[5] = 'a';
}

Word::Word(int len){
	actualWord = new char[len];
	wordLen = len;
	isInPig = false;
	isInPigVowel = false;
	allCaps = false;
	pigCharOffset = 0;
}

Word::Word(const Word& copier){
	actualWord = new char[copier.wordLen];
	for(int i=0; i<copier.wordLen; i++){
		actualWord[i] = copier.actualWord[i];
	}
	wordLen = copier.wordLen;
	isInPig = copier.isInPig;
	isInPigVowel = copier.isInPigVowel;
	allCaps = copier.allCaps;
	pigCharOffset = copier.pigCharOffset;
}

Word::Word(char* array, int len){
	actualWord = new char[len];
	wordLen = len;
	for(int i=0; i<wordLen; i++){
		actualWord[i] = array[i];
	}
	isInPig = false;
	isInPigVowel = false;
	allCaps = false;
	pigCharOffset = 0;
}

Word& Word::operator--(int){
	int i;
	for(i = 0; i < wordLen; i++)
	{
		if(isupper(actualWord[i]))
		{
			int newChar = tolower(actualWord[i]);
			actualWord[i] = (char)newChar;
		}
	}
	allCaps = false;
	return (*this);
}

Word& Word::operator--(){
	char punc = actualWord[wordLen - 1];
	bool hasPunc = (isalpha(actualWord[wordLen-1]) ? false : true);
	bool wasUpper = isupper(actualWord[0]);
	if(hasPunc){
		char* del = actualWord;
		char* noPunc = new char[wordLen-1];
		actualWord = noPunc;
		for(int m=0; m<wordLen-1; m++){
			actualWord[m] = del[m];
		}
		wordLen--;
		delete [] del;
		--(*this);
		char* newActual = new char[wordLen + 1];
		char* oldActual = actualWord;
		actualWord = newActual;
		for(int n=0; n<wordLen; n++){
			actualWord[n] = oldActual[n];
		}
		actualWord[wordLen] = punc;
		wordLen++;
		delete [] oldActual;
		return (*this);
	}
	if(isInPig){
		char* temp = new char[wordLen-2];
		char* delPtr = actualWord;
		actualWord = temp;
		int offset = pigCharOffset;
		int begin = 0;
		while((offset)){
			temp[begin] = tolower(delPtr[wordLen-2-offset]);
			begin++;
			offset--;
		}
		for(int i=begin; i<wordLen-2; i++){
			temp[i] = tolower(delPtr[i-pigCharOffset]);
		}
		isInPig = false;
		wordLen = wordLen - 2;
		if(wasUpper) {actualWord[0] = toupper(actualWord[0]);}
		if(allCaps){
			for(int k=0; k<wordLen; k++){
				temp[k] = toupper(temp[k]);
			}
		}
		delete [] delPtr;
	}
	else if(isInPigVowel){
		char* temp = new char[wordLen - 3];
		char* delPtr = actualWord;
		actualWord = temp;
		for(int j=0; j<wordLen-3; j++){
			temp[j] = delPtr[j];
		}
		isInPigVowel = false;
		wordLen = wordLen - 3;
		if(wasUpper) {actualWord[0] = toupper(actualWord[0]);}
		if(allCaps){
			for(int m=0; m<wordLen; m++){
				temp[m] = toupper(temp[m]);
			}
		}
		delete [] delPtr;
	}
	return (*this);
}

Word& Word::operator++(){
	bool wasUpper = isupper(actualWord[0]);
	bool hasPunc = (isalpha(actualWord[wordLen-1]) ? false : true);
	char punc = actualWord[wordLen-1];
	char pig = toupper(actualWord[0]);
	int oldWordLen = wordLen;
	//starts with vowel case
	if(pig == 'A' || pig == 'E' || pig == 'I' || pig == 'O' || pig == 'U')
	{
		char *temp = new char[oldWordLen + 3];
		char *delPtr = actualWord;
		actualWord = temp;
		int i;
		for(i=0; i<oldWordLen; i++)
		{
			actualWord[i] = delPtr[i];
		}
		if(hasPunc){
			actualWord[oldWordLen-1] = 'w';
			actualWord[oldWordLen] = 'a';
			actualWord[oldWordLen+1] = 'y';
			actualWord[oldWordLen+2] = punc;
		}
		else{
			actualWord[oldWordLen] = 'w';
			actualWord[oldWordLen+1] = 'a';
			actualWord[oldWordLen+2] = 'y';
		}
		wordLen = oldWordLen + 3;
		delete [] delPtr;
		isInPigVowel = true;
		if(allCaps){
			for(int m=0; m<wordLen; m++){
				actualWord[m] = toupper(actualWord[m]);
			}
		}
		return (*this);
	}
	else
	{
		if(hasPunc){
			char* del = actualWord;
			char* intermediate = new char[wordLen-1];
			actualWord = intermediate;
			for(int q = 0; q < wordLen-1; q++){
				actualWord[q] = del[q];
			}
			oldWordLen--;
			delete [] del;
		}
		int j = 0;
		int offset = 0;
		bool noVowel = false;
		char pig2 = toupper(actualWord[0]);
		while(!(pig2 == 'A' || pig2 == 'E' || pig2 == 'I' || pig2 == 'O' || pig2 == 'U'))
		{
			offset++;
			if(offset == oldWordLen){
				//No vowels in the word, chose to append 'way'
				offset = 0;
				noVowel = true;
				break;
			}
			pig2 = toupper(actualWord[offset]);
		}
		if(noVowel){
			char *temp = new char[oldWordLen + 3];
			char *delPtr = actualWord;
			actualWord = temp;
			int i;
			for(i=0; (i+offset)<oldWordLen; i++)
			{
				actualWord[i] = delPtr[i+offset];
			}
			actualWord[oldWordLen] = 'w';
			actualWord[oldWordLen+1] = 'a';
			actualWord[oldWordLen+2] = 'y';
			wordLen = oldWordLen + 3;
			delete [] delPtr;
			isInPigVowel = true; //not quite accurate but will decode properly this way
			//return (*this);
		}
		else{ 
			pigCharOffset = offset;
			char *delPtr = actualWord;
			char* temp = new char[oldWordLen + 2];
			actualWord = temp;
			int i;
			for(i=0; (i+offset)<oldWordLen; i++)
			{
				actualWord[i] = delPtr[i+offset];
			}
			for(j=0; j<offset; j++)
			{
				actualWord[i+j] = delPtr[j];
			}
			actualWord[oldWordLen-offset] = tolower(actualWord[oldWordLen-offset]);
			wordLen = oldWordLen + 2;
			if(wasUpper) {actualWord[0] = toupper(actualWord[0]);}
			isInPig = true;
			actualWord[oldWordLen] = 'a';
			actualWord[oldWordLen+1] = 'y';
			delete [] delPtr;
			//return (*this);
		}
	}
	if(hasPunc){
		char* old = actualWord;
		char* withPunc = new char[wordLen+1];
		actualWord = withPunc;
		for(int c=0; c<wordLen; c++){
			actualWord[c] = old[c];
		}
		actualWord[wordLen] = punc;
		delete [] old;
		wordLen++;
		if(allCaps){
			for(int m=0; m<wordLen; m++){
				actualWord[m] = toupper(actualWord[m]);
			}
		}
	}
	return (*this);
}

Word& Word::operator++(int)
{
	for(int i=0; i<wordLen; i++)
	{
		actualWord[i] = toupper(actualWord[i]);
	}
	allCaps = true;
	return (*this);
}

Word& Word::operator+(int i)
{
	if(i != 1) {return (*this);}
	else
	{
		actualWord[0] = toupper(actualWord[0]);
		return (*this);
	}
}

Sentence Word::operator+(Word& second)
{
	Sentence ret;
	ret.addFront(this);
	ret.addBack(&second);
	return ret;
}

Sentence Word::operator+(Sentence& original){

	Sentence ret = original;
	ret.addFront(this);
	return ret;
}

Word& Word::operator=(const Word& copier){
	char* temp = new char[copier.wordLen];
	char* delPtr = actualWord;
	actualWord = temp;
	for(int i=0; i<copier.wordLen; i++){
		actualWord[i] = copier.actualWord[i];
	}
	wordLen = copier.wordLen;
	isInPig = copier.isInPig;
	isInPigVowel = copier.isInPigVowel;
	pigCharOffset = copier.pigCharOffset;
	delete [] delPtr;
	return (*this);
}	

ostream& operator<<(ostream& out, const Word& printer)
{
	int i = 0;
	while(i < printer.wordLen)
	{
		out << printer.actualWord[i];
		i++;
	}
	return out;
}

Word::~Word(){
	delete [] actualWord;
}
