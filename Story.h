#ifndef STORY
#define STORY

class Story;

#include "Paragraph.h"

using namespace std;

class Story{
	public:
		Story();
		Story(Paragraph array[], int num);
		Story(const Story& copier);
		Story(char* filename);
		~Story();
		Story operator+(Story& story);
		Story operator+(Paragraph& para);
		Story& operator++(int);
		Story& operator--(int);
		Story& operator+(int i);
		Story& operator++();
		Story& operator--();
		Story& operator=(const Story& copier);
		friend ostream& operator<<(ostream& out, const Story& printer);
		Paragraph first();
		Story rest();
		void save(char* filename);
		bool isEmpty();
		void addFront(Paragraph* newData);
		void addBack(Paragraph* newData);
	
	private:
		class Node
		{
			public:
				Paragraph* data;
				Node* next;
				~Node();
		};
		Node* firstNode;
		int length;
};
#endif
