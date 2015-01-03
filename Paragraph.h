#ifndef PARAGRAPH
#define PARAGRAPH

class Paragraph;

#include "Sentence.h"
#include "Story.h"

using namespace std;

class Paragraph{
	public:
		Paragraph();
		Paragraph(Sentence array[], int numSentence);
		Paragraph(const Paragraph& copier);
		~Paragraph();
		Paragraph operator+(Sentence& additional);
		Story operator+(Paragraph& para);
		Story operator+(Story& story);
		Paragraph& operator++(int);
		Paragraph& operator--(int);
		Paragraph& operator+(const int add);
		Paragraph& operator++();
		Paragraph& operator--();
		Paragraph& operator=(const Paragraph& para);
		friend ostream& operator<<(ostream& out, const Paragraph& printer);
		Sentence first();
		Paragraph rest();
		bool isEmpty();
		void addFront(Sentence* newData);
		void addBack(Sentence* newData);
		
	private:
		class Node
		{
			public:
				Sentence* data;
				Node* next;
				~Node();
		};
		Node* firstNode;
		int length;
		
};
#endif
