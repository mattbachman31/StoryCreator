#include "Sentence.h"

using namespace std;

Sentence::Node::~Node(){
	if(data) { delete data;}
}

Sentence::Sentence(){
	firstNode = 0;
	length = 0;
}

Sentence::Sentence(Word array[], int numWords){
	firstNode = 0;
	length = numWords;
	int len = 0;
	Node* currentNode;
	Node* previousNode;
	while(len < length){
		Word* newWord = new Word(array[len]);
		currentNode = new Node();
		currentNode->data = newWord;
		currentNode->next = 0;
		if(len == 0) {firstNode = currentNode;}
		else {previousNode->next = currentNode;}
		previousNode = currentNode;
		len++;
	}
}

Sentence::Sentence(const Sentence& copier){
	length = copier.length;
	firstNode = 0;
	int len=1;
	Node* thisNode = copier.firstNode;
	Node* nextNode;
	if(thisNode != 0){
		firstNode = new Node();
		Word* firstNewWord = new Word(*(thisNode->data));
		firstNode->data = firstNewWord;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Word* newWord = new Word(*(original->data));
			current->next->data = newWord;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

Sentence Sentence::operator+(Word& newWord){
	Sentence ret = Sentence((*this));
	ret.addBack(&newWord);
	return (ret);
}

Paragraph Sentence::operator+(Sentence& sentence2){
	Sentence array[] = {(*this), sentence2};
	Paragraph ret(array, 2);
	return ret;
}

Paragraph Sentence::operator+(Paragraph& original){
	Paragraph ret = Paragraph(original);
	ret.addFront(this);
	return ret;
}

Sentence& Sentence::operator++(int){
	Node* first = firstNode;
	while(first != 0){
		Word* test = (first->data);
		(*test)++;
		first = first->next;
	}
	return (*this);
}
Sentence& Sentence::operator--(int){
	Node* first = firstNode;
	while(first != 0){
		Word* test = (first->data);
		(*test)--;
		first = first->next;
	}
	return (*this);
}

Sentence& Sentence::operator+(int i){
	if(i == 1){
		Word* old = firstNode->data;
		Word* newWord = new Word(*old);
		(*newWord) + 1; // Can't do (*newWord) = this expression??
		firstNode->data = newWord;
		delete old;
	}
	return (*this);
}

Sentence& Sentence::operator++(){
	Node* first = firstNode;
	while(first != 0){
		Word* test = (first->data);
		if(!((*test).isInPig) && !((*test).isInPigVowel)) {++(*test);}
		first = first->next;
	}
	return (*this);
}

Sentence& Sentence::operator--(){
	Node* first = firstNode;
	while(first != 0){
		Word* test = (first->data);
		if(((*test).isInPig) || ((*test).isInPigVowel)) {--(*test);}
		first = first->next;
	}
	return (*this);
}

Sentence& Sentence::operator=(const Sentence& copier){
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
		Word* firstNewWord = new Word(*(thisNode->data));
		firstNode->data = firstNewWord;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Word* newWord = new Word(*(original->data));
			current->next->data = newWord;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

ostream& operator<<(ostream& out, const Sentence& printer){
	int len = printer.length;
	Sentence::Node* current = printer.firstNode;
	while(len > 0){
		out << *(current->data) << " ";
		len--;
		current = current->next;
	}
	return out;
}

Word Sentence::first(){
	return *(firstNode->data);
}

Sentence Sentence::rest(){
	Node* keepFirstNode = firstNode;
	firstNode = firstNode->next;
	length--;
	Sentence ret = Sentence(*(this));
	length++;
	firstNode = keepFirstNode;
	return ret;
}

bool Sentence::isEmpty(){
	return(firstNode == 0);
}

void Sentence::addFront(Word* newData){
	Node* oldFront = firstNode;
	Node* newFirstNode = new Sentence::Node();
	Word* newWord = new Word(*newData);
	newFirstNode->data = newWord;
	newFirstNode->next = oldFront;
	firstNode = newFirstNode;
	length++;
}

void Sentence::addBack(Word* newData){
	Node* current = firstNode;
	Node* previous = 0;
	while(current != 0){
		previous = current;
		current = current->next;
	}
	Node* newNode = new Node();
	Word* newWord = new Word(*newData);
	newNode->data = newWord;
	if(previous) {previous->next = newNode;}
	else{firstNode = newNode;}
	newNode->next = 0;
	length++;
}

Sentence::~Sentence(){
	Node* current = firstNode;
	Node* afterCurr;
	while(current != 0){
		afterCurr = current->next;
		delete current;
		current = afterCurr;
	}
}
