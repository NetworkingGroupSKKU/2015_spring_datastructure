/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment6 */
/* Word-list.h */
/* by Ji Min Kim */
#ifndef __WORD_LIST_H_
#define __WORD_LIST_H_


#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Wordlist{

private:
	/* Private parameter that contains word of each node and link. 
	And also includes Node pointer Head, Curr, Signature. */
	struct Node{
		char* word;
		Node *llink,*rlink;
	};

	Node *Head;
	Node *Curr;
	unsigned int signature[4];

	vector<string> action;
	string action_buffer;

	/* Private function 'insert' insert node in doubly linked list.*/
	bool insert(char* array){
		Node *NewNode = new Node;
		NewNode->word = new char[strlen(array)+1];
		strcpy(NewNode->word, array);

		NewNode->llink = Curr;
		NewNode->rlink = Curr->rlink;
		Curr->rlink->llink = NewNode;
		Curr->rlink = NewNode;
		Curr = NewNode;
		return true;
	}

	/* Private function 'remove' remove node in doubly linked list and
	bit-wise exclusive or operation with signature.*/
	bool remove(){
		if( Curr == Head ){
			return false;
		}

		Node *temp;

		temp = Curr;

		if(Curr->rlink == Head)
			Curr = Curr->llink;
		else
			Curr = Curr->rlink;

		temp->llink->rlink = temp->rlink;
		temp->rlink->llink = temp->llink;

		for(int i=0; i<strlen( temp->word )-1; i++){
			signature[i%4] = signature[i%4]^( temp->word[i] );
		}

		delete []temp->word;
		delete temp;

		return true;
	}

	/* Private function 'previous' move Curr pointer to previous node */
	bool previous(){
		if(Curr->llink != Head){
			Curr = Curr->llink;
			return true;
		}
		return false;
	}

	/* Private function 'next' move Curr pointer to next node */
	bool next(){
		if(Curr->rlink != Head){
			Curr = Curr->rlink;
			return true;
		}
		return false;
	}

	/* Private function 'front' move Curr pointer to front of list. */
	bool front(){
		if(Head->llink != Head){
			Curr = Head->llink;
			return true;
		}
		return false;
	}

	/* Private function 'back' move Curr pointer to back of list. */
	bool back(){
		if(Head->rlink != Head){
			Curr = Head->rlink;
			return true;
		}
		return false;
	}

	/* Private function 'get' return word that Curr pointed */
	string get(){
		string buffer;
		buffer = Curr->word;
		if( Curr == Head) {
			return NULL;
		}
		return buffer;
	}

	/* Private function 'end' terminate excution and return final signature. */
	bool end(){
		front();
		Node *temp;
		while(Curr != Head){
			temp = Curr->rlink;
			delete []Curr->word;
			delete Curr;
			Curr = temp;
		}
		delete Head->word;
		delete Head;

		cout<<hex;
		cout<<"signature is 0x"<<signature[0]<<signature[1]<<signature[2]<<signature[3]<< endl;
		return true;
	}



public:
	/* Public function description is in 'Word-list.cpp' */
	Wordlist();
	bool actionSaver();
	bool actionChecker();
	~Wordlist();
};

#endif

