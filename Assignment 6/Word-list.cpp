/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment6 */
/* Word-list.cpp */
/* by Ji Min Kim */

/////* This file is function description that included in 'Word-list.cpp'. */////

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

#include "Word-list.h"

using namespace std;

/* Wordlist() is constructor that make head and initialize signature. */
Wordlist::Wordlist(){
	Head = new Node;
	Head->word = new char;
	Head->word = NULL;
	Head->llink = Head->rlink = Curr = Head;
	for(int i=0; i<4; i++)
		signature[i] = 0;
}

/* actionSaver() is function that store action at vector from "action-doubly.txt" */
bool Wordlist::actionSaver(){
	ifstream actionfile("action-doubly.txt");
	if( actionfile.is_open() ){
		while( !actionfile.eof() ){
			getline(actionfile, action_buffer);
			action.push_back(action_buffer);
		}
		actionfile.close();
	}
	return true;
}

/* actionChecker() is function that check current action and call proper PRIVATE function */
bool Wordlist::actionChecker(){
	string action_word;
	string current_word;
	char *buffer;

	ifstream wordfile("words.txt");
	if( wordfile.is_open() ){
		for(int i=0; i<action.size(); i++){
			if(action[i] == "+"){
				getline(wordfile, action_word);
				buffer = new char[action_word.size()+1];
				strcpy(buffer, action_word.c_str());
				insert(buffer);
				delete []buffer;
			}
			else if(action[i] == "-") remove();
			else if(action[i] == "<") previous();
			else if(action[i] == ">") next();
			else if(action[i] == "<<") front();
			else if(action[i] == ">>") back();
			else if(action[i] == "?"){
				current_word = get();
				buffer = new char[current_word.size()+1];
				strcpy(buffer, current_word.c_str());
            			cout<<" Current Word is " <<buffer<< endl;
				delete []buffer;
			}
			else if(action[i] == "!"){
				if(end()) break;
			}
			else{ }
		}
	wordfile.close();
	}

	return true;
}

Wordlist::~Wordlist(){
}
