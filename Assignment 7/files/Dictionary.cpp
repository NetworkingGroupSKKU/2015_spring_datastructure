/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment7 */
/* Dictionary.cpp */
/* by Ji Min Kim */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <list>
#include <cassert>
#include <algorithm>

/* Include 'Hash.h' that includes functions*/
#include "Hash.h"
using namespace std;


int Finish=0;			// When mean loading density is lower than 5, 'Finish' will be 1 

/* hash_1 is first hash function.
hash_2 is second hash function.
Dictionary is function that read <words.txt> and get various statics for two hash function */
int hash_1(char*, int);
int hash_2(char*, int);
void Dictionary(int);

int main(){

	/* Hash table size creater that ALL prime numbers no less than 167.
	If mean loading desity is lower than 5, terminate. */
	int i=167;
	while(!Finish){
		for(int j=2; j*j<=i; j++){
			if( i % j == 0 )
				break;
			else if( j+1 > sqrt(i) ){
				Dictionary(i);
			}
		}
		i++;
	}



	return 0;
}

/* hash_1 is hash function that use division method. */
int hash_1(char *key, int num_buckets){
	int hval=0;
	for(int i=0; i< strlen(key)-1; i++){
		hval = hval + key[i];
	}
	hval = hval % num_buckets;
	assert( hval < num_buckets );
	return hval;
}

/* hash_2 is hash function that use folding method. */
int hash_2(char *key, int num_buckets){
	int hval[3]={0,0,0};
	int hval_acc=0;

	for(int i=0; i<strlen(key)-1; i++){
		hval[i%3]=hval[i%3]+key[i%3];
	}

	hval_acc=hval[0]+hval[1]+hval[2];

	hval_acc = hval_acc % num_buckets;
	assert( hval_acc < num_buckets);
	return hval_acc;
}

/* Dictionary is function that read <words.txt> and get various statics for two hash function */
void Dictionary(int size){

	HashTable h1(size, hash_1);
	HashTable h2(size, hash_2);
	WordNode *p;

	string word_string;
	char* word_buffer;

	ifstream inputfile1("words.txt");
	if( inputfile1.is_open() ){
		while(getline(inputfile1, word_string)){
			word_buffer = new char[word_string.size()+1];
			strcpy(word_buffer, word_string.c_str());
			p=h1.insert(word_buffer);
			delete []word_buffer;
		}
		inputfile1.close();
	}

	double mean=0;
	double stdev=0;
	int min;
	int max;
	int compare;

	h1.get_statistics(&mean, &stdev);
	h1.get_chain_lengths(&min, &max);
	h1.number_of_comparisons(&compare);

	if( mean < 5 ) Finish = 1;

	if( !Finish ){
	cout<<"size is "<<size<<endl;
	cout<<"hash_1 mean loading density is "<<mean<<endl;
	cout<<"hash_1 stdev is "<<stdev<<endl;
	cout<<"hash_1 Minimum chain length is "<<min<<endl;
	cout<<"hash_1 Maximum chain length is "<<max<<endl;
	cout<<"hash_1 Number of comparisons are "<<compare<<endl;
	cout<<endl;
	}

	ifstream inputfile2("words.txt");
        if( inputfile2.is_open() ){
                while(getline(inputfile2, word_string)){
                        word_buffer = new char[word_string.size()+1];
                        strcpy(word_buffer, word_string.c_str());
                        p=h2.insert(word_buffer);
                        delete []word_buffer;
                }
                inputfile2.close();
        }

        h2.get_statistics(&mean, &stdev);
        h2.get_chain_lengths(&min, &max);
	h2.number_of_comparisons(&compare);

	if(!Finish){
        cout<<"hash_2 mean loading density is "<<mean<<endl;
        cout<<"hash_2 stdev is "<<stdev<<endl;
        cout<<"hash_2 Minimum chain length is "<<min<<endl;
        cout<<"hash_2 Maximum chain length is "<<max<<endl;
	cout<<"hash_2 Number of comparisons are "<<compare<<endl;
	cout<<"----------------------------------------------------"<<endl;

	}
	else h1.Occur_print();
}
