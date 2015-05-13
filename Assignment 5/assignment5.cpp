#include <iostream>
#include <fstream>
#include <string>
#define MaxQsize 32

using namespace std;

void signature(char**cq, int* strlen, char *sig, int front){
	int j=-1;
	for(int i=0; i<strlen[front]; i++){
		j+=1;
		if(j==4){
			j=0;
		}
		sig[j] = sig[j]^cq[front][i];
	}
}

class Q
{
public:
	int front;
	int rear;
	int count;
	char** cq;

	void create();
	bool enqueue(char** cq, int* strlen, string s, int size);
	bool dequeue(char** cq, int* strlen, char *sig);
	bool is_full();
	bool is_empty();
};

void Q::create(){
	Q::front = Q::rear = Q::count = 0;
	Q::cq = new char* [MaxQsize];
}

bool Q::enqueue(char** cq, int* strlen, string s, int size){
	if(Q::is_full())
		return false;

	Q::rear=(Q::rear+1)%MaxQsize;
	const char *ch = s.c_str();
	cq[Q::rear] = new char[size];
	memmove(cq[Q::rear],ch,size+1 * sizeof(char));
	strlen[Q::rear] = size;
	count++;
	return true;
}

bool Q::dequeue(char** cq, int* strlen, char *sig){
	if(is_empty())
		return false;

	Q::front=(Q::front+1)%MaxQsize;
	signature(cq, strlen, sig, Q::front);
	count--;
	return true;
}

bool Q::is_full(){
	return count==MaxQsize;
}
	
bool Q::is_empty(){
	return count==0;
}





void main()
{
	Q q;

	int size;
	char *sig = new char[4];
	for(int i=0; i<4; i++)
		sig[i] = 0;
	int *strlen = new int[MaxQsize];
	char temp;
	string s;

	q.create();

	ifstream wor;
	ifstream act;
	wor.open("words.txt");
	act.open("action-queue.txt");

	while(!act.eof()){
		act.get(temp);
		if (temp == '+' || temp == '-'){
			if(temp=='+'){
				getline(wor,s);
				size = s.size();
				q.enqueue(q.cq, strlen, s, size); 
			}
			else if(temp=='-'){
					q.dequeue(q.cq, strlen, sig);
			}
		}
	}
	cout << "MaxQsize = " << MaxQsize << ",  signiture value is" << endl;
	for(int i=0; i<4; i++)
		cout << sig[i];
	cout << endl;
}
