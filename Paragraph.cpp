#include "Paragraph.h"

using namespace std;

Paragraph::Node::~Node(){
	if(data) {delete data;}
}

Paragraph::Paragraph(){
	firstNode = 0;
	length = 0;
}

Paragraph::Paragraph(Sentence array[], int numSentence){
	firstNode = 0;
	length = numSentence;
	int len = 0;
	Node* currentNode;
	Node* previousNode;
	while(len < length){
		currentNode = new Node();
		Sentence* newSentence = new Sentence(array[len]);
		currentNode->data = newSentence;
		currentNode->next = 0;
		if(len == 0) {firstNode = currentNode;}
		else {previousNode->next = currentNode;}
		previousNode = currentNode;
		len++;
	}
}

Paragraph::Paragraph(const Paragraph& copier){
	length = copier.length;
	firstNode = 0;
	int len=1;
	Node* thisNode = copier.firstNode;
	Node* nextNode;
	if(thisNode != 0){
		firstNode = new Node();
		Sentence* firstNewSentence = new Sentence(*(thisNode->data));
		firstNode->data = firstNewSentence;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Sentence* newSentence = new Sentence(*(original->data));
			current->next->data = newSentence;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

Paragraph Paragraph::operator+(Sentence& additional){
	Paragraph ret = Paragraph((*this));
	ret.addBack(&additional);
	return (ret);
}

Story Paragraph::operator+(Paragraph& para){
	Paragraph array[] = {(*this), para};
	Story ret(array, 2);
	return ret;
}

Story Paragraph::operator+(Story& story){
	Story ret = Story(story);
	ret.addFront(this);
	return ret;
}

Paragraph& Paragraph::operator++(int){
	Node* first = firstNode;
	while(first != 0){
		Sentence* test = (first->data);
		(*test)++;
		first = first->next;
	}
	return (*this);
}

Paragraph& Paragraph::operator--(int){
	Node* first = firstNode;
	while(first != 0){
		Sentence* test = (first->data);
		(*test)--;
		first = first->next;
	}
	return (*this);
}

Paragraph& Paragraph::operator+(const int add){
	if(add == 1){
		Node* current = firstNode;
		while(current != 0){
			Sentence* cap = current->data;
			(*cap) + 1;
			current = current->next;
		}
	}
	return (*this);
}

Paragraph& Paragraph::operator++(){
	Node* first = firstNode;
	while(first != 0){
		Sentence* test = (first->data);
		++(*test);
		first = first->next;
	}
	return (*this);
}

Paragraph& Paragraph::operator--(){
	Node* first = firstNode;
	while(first != 0){
		Sentence* test = (first->data);
		--(*test);
		first = first->next;
	}
	return (*this);
}

Paragraph& Paragraph::operator=(const Paragraph& copier){
	if(this == &copier) {return (*this);}
	Node* current1 = firstNode;
	Node* afterCurr;
	while(current1 != 0){
		afterCurr = current1->next;
		delete current1;
		current1 = afterCurr;
	}
	length = copier.length;
	firstNode = 0;
	Node* thisNode = copier.firstNode;
	if(thisNode != 0){
		firstNode = new Node();
		Sentence* firstNewSentence = new Sentence(*(thisNode->data));
		firstNode->data = firstNewSentence;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Sentence* newSentence = new Sentence(*(original->data));
			current->next->data = newSentence;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

ostream& operator<<(ostream& out, const Paragraph& printer){
	int len = printer.length;
	Paragraph::Node* current = printer.firstNode;
	while(len > 0){
		out << *(current->data);
		len--;
		current = current->next;
	}
	return out;
}

Sentence Paragraph::first(){
	return *(firstNode->data);
}

Paragraph Paragraph::rest(){
	Node* keepFirstNode = firstNode;
	firstNode = firstNode->next;
	length--;
	Paragraph ret = Paragraph(*(this));
	length++;
	firstNode = keepFirstNode;
	return ret;
}

bool Paragraph::isEmpty(){
	return(firstNode == 0);
}

void Paragraph::addFront(Sentence* newData){
	Node* oldFront = firstNode;
	Node* newFirstNode = new Paragraph::Node();
	Sentence* newSentence = new Sentence(*newData);
	newFirstNode->data = newSentence;
	newFirstNode->next = oldFront;
	firstNode = newFirstNode;
	length++;
}

void Paragraph::addBack(Sentence* newData){
	Node* current = firstNode;
	Node* previous = 0;
	while(current != 0){
		previous = current;
		current = current->next;
	}
	Node* newNode = new Node();
	Sentence* newSentence = new Sentence(*newData);
	newNode->data = newSentence;
	if(previous) {previous->next = newNode;}
	else{firstNode = newNode;}
	newNode->next = 0;
	length++;
}

Paragraph::~Paragraph(){
	Node* current = firstNode;
	Node* afterCurr;
	while(current != 0){
		afterCurr = current->next;
		delete current;
		current = afterCurr;
	}
}
