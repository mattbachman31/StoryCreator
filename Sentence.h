#ifndef SENTENCE
#define SENTENCE

class Sentence;

#include "Word.h"
#include "Paragraph.h"

using namespace std;

class Sentence{
	public:
		Sentence();
		Sentence(Word[], int);
		Sentence(const Sentence& copier);
		~Sentence();
		Sentence operator+(Word& newWord);
		Paragraph operator+(Sentence& sentence2);
		Paragraph operator+(Paragraph& original);
		Sentence& operator++(int);
		Sentence& operator--(int);
		Sentence& operator+(int i);
		Sentence& operator++();
		Sentence& operator--();
		Sentence& operator=(const Sentence& copier);
		friend ostream& operator<<(ostream& out, const Sentence& printer);
		Word first();
		Sentence rest();
		bool isEmpty();
		void addFront(Word* newData);
		void addBack(Word* newData);
	private:
		class Node
		{
			public:
				Word* data;
				Node* next;
				~Node();
		};
		Node* firstNode;
		int length;
};

#endif
