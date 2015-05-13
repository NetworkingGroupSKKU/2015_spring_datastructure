/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment4 */
/* checker.cpp */
/* by Ji Min Kim */


#include <iostream>
#include <fstream>
#include <cstring>


#include <cstdlib>
using namespace std;

/* count is global varible that represent line number */
int count =0;

/* Stack is class that contain stacking space and functions */
class Stack{
	/* buffer is stacking space parameter.
	cnt is stack pointer that represent next pushing point*/
	char *buffer;
	int cnt;

public:
	/* Stack() is constructor*/
	Stack(){
		cnt = 0;
	}

	/* empty() is function that check whether stack is empty*/
	bool empty( Stack *s ){
		if( s->cnt == 0){
			return true;
		}
		return false;
	}

	/* push() is function that push character into stack */
	void push( Stack *s, char ch ){
		s->buffer[s->cnt] = ch;
		s->cnt ++;
	}

	/* pop() is function that pop character from stack */
	void pop( Stack *s ){
		if( !empty(s)){
		s->cnt --;
		s->buffer[s->cnt] = '\0';
		}
	}

	/* top() is function that return top position character*/
	char top( Stack *s ){
		if( empty(s) ) return '\0';
		return s->buffer[s->cnt-1];
	}

	/* creat() is function that create proper stack and initialize */
	void create( Stack *s, int length){
		s->buffer = new char[length];
		for(int i=0; i<length; i++){
			s->buffer[i] = '\0';
		}
	}

	/* clear() is function that clear stack and cnt */
	void clear( Stack *s ){
		s->cnt = 0;
		delete []s->buffer;
	}

};


int main(){

	string line;
	char *line_array;
	Stack s;


	ifstream inputfile("paren.txt");
	if(inputfile.is_open()){
			while( getline(inputfile, line) ){
				line_array = new char[line.length()];
				strcpy(line_array, line.c_str());

			/* Empty line skip*/
			if(line_array[0]!='\r'){
				s.create(&s, line.length());
				for(int i=0; i<line.length() ; i++){
					if(line_array[i] == '(' || line_array[i] == '[') s.push(&s, line_array[i]);
					else if(line_array[i] == ')'){
						if( s.top(&s) == '(') s.pop(&s);
						else break;
					}
					else if(line_array[i] == ']'){
						if( s.top(&s) == '[') s.pop(&s);
						else break;
					}
				}

				count ++;
				/* After scanning, if stack is empty, the line is well-formed. */
				if(s.empty(&s))  cout << count << " Correct" << endl;
	                        else cout << count << " Wrong" << endl;

	       	                s.clear(&s);

			}
			delete []line_array;

			}

		inputfile.close();
	}

	return 0;
}
