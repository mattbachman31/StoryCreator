#include "Story.h"

using namespace std;

Story::Node::~Node(){
	if(data) { delete data;}
}

Story::Story(){
	firstNode = 0;
	length = 0;
}

Story::Story(Paragraph array[], int num){
	firstNode = 0;
	length = num;
	int len = 0;
	Node* currentNode;
	Node* previousNode;
	while(len < length){
		currentNode = new Node();
		Paragraph* newParagraph = new Paragraph(array[len]);
		currentNode->data = newParagraph;
		currentNode->next = 0;
		if(len == 0) {firstNode = currentNode;}
		else {previousNode->next = currentNode;}
		previousNode = currentNode;
		len++;
	}
}

Story::Story(const Story& copier){
	length = copier.length;
	firstNode = 0;
	Node* thisNode = copier.firstNode;
	if(thisNode != 0){
		firstNode = new Node();
		Paragraph* firstNewParagraph = new Paragraph(*(thisNode->data));
		firstNode->data = firstNewParagraph;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Paragraph* newParagraph = new Paragraph(*(original->data));
			current->next->data = newParagraph;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

Story::Story(char* filename){
	char ch = '0';
	length=0;
	ifstream in(filename);
	if(in.fail()) { cout << "Bad filename" << endl;}
	else { cout << "OK so far (Story file constructor)..." << endl;}
	int sentCount = 0, wordCount = 1, paraCount = 0;
	bool hadBeenNull = false;
	bool hadBeenSpaceOrNull = false;
	paraCount = 1;
	in.get(ch);
	while(in.get(ch)){
		if(hadBeenSpaceOrNull) {
			wordCount++;
			hadBeenSpaceOrNull = false;
		}
		if(ch == ' ' || ch == '\n') {hadBeenSpaceOrNull = true;}
		if(ch == '!' || ch == '.' || ch == '?'){
			sentCount++;
		}
		if(hadBeenNull){
			if(ch == '\t') {paraCount++;}
			hadBeenNull = false;
		}
		if(ch == '\n') {hadBeenNull = true;}
	}
	//cout << "Paragraphs: " << paraCount << " Sentences: " << sentCount << " Words: " << wordCount << endl;
	hadBeenNull = false;
	hadBeenSpaceOrNull = false;
	in.close();
	Paragraph storyPara[paraCount];
	Sentence storySent[sentCount];
	Word storyWord[wordCount];
	ifstream in2(filename);
	if(in2.fail()) { cout << "Bad filename" << endl;}
	else { cout << "OK so far (Story file constructor)..." << endl;}
	int charCount=0, words=0, sentOffset = 0, numSentence=0, currentPara = 0;
	char* temp = new char[30];
	bool prevWordEndSentence = false;
	bool firstPara = true;
	bool firstSentence = true;
	bool willBeNewPara = false;
	in2.get(ch);
	while(in2.get(ch)){
		if(hadBeenSpaceOrNull) {
			if(ch != ' ' && ch != '\n' && ch != '\t'){
				wordCount++;
				char* del = temp;
				temp = new char[30];
				Word newWord(del,charCount);
				storyWord[words] = newWord;
				delete [] del;
				words++;
				sentOffset++;
				if(prevWordEndSentence){
					Word* tempArray = new Word[sentOffset];
					for(int j=0; j<sentOffset; j++){
						tempArray[j] = storyWord[words-sentOffset+j];
					}
					Sentence tempSent(tempArray,sentOffset);
					storySent[numSentence] = tempSent;
					if(firstSentence){
						(storyPara[currentPara]).addFront(&(storySent[numSentence]));
						firstSentence = false;
					}
					else{(storyPara[currentPara]).addBack(&(storySent[numSentence]));}
					if(willBeNewPara){
						willBeNewPara = false;
						currentPara++;
						firstSentence = true;
					}
					numSentence++;
					delete [] tempArray;
					sentOffset = 0;
					prevWordEndSentence = false;
				}
				charCount=0;
			}
			hadBeenSpaceOrNull = false;
		}
		if(ch == ' ' || ch == '\n' || ch == '\t') {hadBeenSpaceOrNull = true;}
		if(hadBeenNull){
			if(ch == '\t') {
				willBeNewPara = true;
			}
			hadBeenNull = false;
		}
		if(ch == '\n') {hadBeenNull = true;}
		if(ch == '!' || ch == '.' || ch == '?'){
			prevWordEndSentence = true;
		}
		if(ch != ' ' && ch != '\n' && ch != '\t'){
			temp[charCount] = ch;
			charCount++;
		}
	}
	in2.close();
	Word newWord(temp, charCount);
	storyWord[words] = newWord;
	words++;
	sentOffset++;
	Word* tempArray = new Word[sentOffset];
	for(int j=0; j<sentOffset; j++){
		tempArray[j] = storyWord[words-sentOffset+j];
	}
	Sentence tempSent(tempArray,sentOffset);
	storySent[numSentence] = tempSent;
	(storyPara[currentPara]).addBack(&(storySent[numSentence]));
	delete [] tempArray;
	delete [] temp;
	firstNode = 0;
	length = paraCount;
	int len = 0;
	Node* currentNode;
	Node* previousNode;
	//cout << length << endl;
	while(len < length){
		currentNode = new Node();
		Paragraph* newParagraph = new Paragraph(storyPara[len]);
		currentNode->data = newParagraph;
		currentNode->next = 0;
		if(len == 0) {firstNode = currentNode;}
		else {previousNode->next = currentNode;}
		previousNode = currentNode;
		len++;
	}
}

Story Story::operator+(Story& story){
	Story ret(*(this));
	Node* first = story.firstNode;
	Node* original;
	while(first != 0){
		ret.addBack(first->data);
		first = first->next;
	}
	return ret;
}

Story Story::operator+(Paragraph& para){
	Story ret = Story((*this));
	ret.addBack(&para);
	return (ret);
}

Story& Story::operator++(int){
	Node* first = firstNode;
	while(first != 0){
		Paragraph* test = (first->data);
		(*test)++;
		first = first->next;
	}
	return (*this);
}

Story& Story::operator--(int){
	Node* first = firstNode;
	while(first != 0){
		Paragraph* test = (first->data);
		(*test)--;
		first = first->next;
	}
	return (*this);
}

Story& Story::operator+(int i){
	if(i == 1){
		Node* current = firstNode;
		while(current != 0){
			Paragraph* cap = current->data;
			(*cap) + 1;
			current = current->next;
		}
	}
	return (*this);
}

Story& Story::operator++(){
	Node* first = firstNode;
	while(first != 0){
		Paragraph* test = (first->data);
		++(*test);
		first = first->next;
	}
	return (*this);
}

Story& Story::operator--(){
	Node* first = firstNode;
	while(first != 0){
		Paragraph* test = (first->data);
		--(*test);
		first = first->next;
	}
	return (*this);
}

Story& Story::operator=(const Story& copier){
	if(this == &copier) {return (*this);}
	Node* current = firstNode;
	Node* afterCurr;
	while(current != 0){
		afterCurr = current->next;
		delete current;
		current = afterCurr;
	}
	length = copier.length;
	firstNode = 0;
	int len=1;
	Node* thisNode = copier.firstNode;
	if(thisNode != 0){
		firstNode = new Node();
		Paragraph* firstNewParagraph = new Paragraph(*(thisNode->data));
		firstNode->data = firstNewParagraph;
		firstNode->next = 0;
		Node* current = firstNode;
		Node* original = copier.firstNode->next;
		while(original != 0){
			current->next = new Node();
			Paragraph* newParagraph = new Paragraph(*(original->data));
			current->next->data = newParagraph;
			current = current->next;
			current->next = 0;
			original = original->next;
		}
	}
}

ostream& operator<<(ostream& out, const Story& printer){
	int len = printer.length;
	Story::Node* current = printer.firstNode;
	if(len>0) {out << '\t';}
	while(len > 0){
		out << *(current->data);
		if(len != 1){out << '\n' << '\n' << '\t';}
		len--;
		current = current->next;
	}
	return out;
}

Paragraph Story::first(){
	return *(firstNode->data);
}

Story Story::rest(){
	Node* keepFirstNode = firstNode;
	firstNode = firstNode->next;
	length--;
	Story ret = Story(*(this));
	length++;
	firstNode = keepFirstNode;
	return ret;
}

void Story::save(char* filename){
	ofstream out(filename);
	int len = length;
	Node* current = firstNode;
	if(len > 0){out << '\t';}
	while(len > 0){
		out << *(current->data);
		if(len != 1){out << '\n' << '\n' << '\t';}
		len--;
		current = current->next;
	}
}

bool Story::isEmpty(){
	return(firstNode == 0);
}

void Story::addFront(Paragraph* newData){
	Node* oldFront = firstNode;
	Node* newFirstNode = new Story::Node();
	Paragraph* newPara = new Paragraph(*newData);
	newFirstNode->data = newPara;
	newFirstNode->next = oldFront;
	firstNode = newFirstNode;
	length++;
}

void Story::addBack(Paragraph* newData){
	Node* current = firstNode;
	Node* previous = 0;
	while(current != 0){
		previous = current;
		current = current->next;
	}
	Node* newNode = new Node();
	Paragraph* newPara = new Paragraph(*newData);
	newNode->data = newPara;
	if(previous) {previous->next = newNode;}
	else{firstNode = newNode;}
	newNode->next = 0;
	length++;
}

Story::~Story(){
	Node* current = firstNode;
	Node* afterCurr;
	while(current != 0){
		afterCurr = current->next;
		delete current;
		current = afterCurr;
	}
}
