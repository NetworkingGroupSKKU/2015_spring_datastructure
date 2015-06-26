/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment7 */
/* Hash.cpp */
/* by Ji Min Kim */

/////* This file is function description that included in 'Hash.h'. */////

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <list>
#include <cassert>
#include <algorithm>

#include "Hash.h"
using namespace std;

/* HashTable() is constructor that initialize parameters and set which hash function be used */
HashTable::HashTable(int num, int (*h)(char*, int)){
	num_buckets = num;
	num_compares = 0;
	hash = h;
	itor_char = occur_char.begin();
	itor_num = occur_num.begin();
	bucket = new WordNode*[num_buckets];
	for(int i=0; i<num_buckets; i++)
		bucket[i] = NULL;
}

/* ~HashTable() is destructor that delete heap memory and clean parameters */
HashTable::~HashTable(){
	WordNode *p;
	for(int i=0; i<num_buckets; i++){
		while( bucket[i] != NULL ){
			p = bucket[i];
			bucket[i] = bucket[i]->next;
			delete []p->word;
			delete []p;
		}
	}
	delete []bucket;
	num_buckets = 0;
	num_compares = 0;
	hash = NULL;
}

/* find() is function that search position of key */
WordNode *HashTable::find(char *key){
	int hval;
	WordNode *p;
	hval = hash(key, num_buckets);
	num_compares++;
	for(p=bucket[hval]; p!=NULL; p=p->next){
		if(!strcmp(p->word,key)) return p;
		num_compares++;
	}
	return NULL;
}

/* insert() is function that insert key in hash table.
At this function we check occurrence. */
WordNode *HashTable::insert(char *key){
	int hval;
	WordNode *p;
	p=find(key);

	if( p!=NULL ) {
		p->count++;

		for(itor_num=occur_num.begin(), itor_char=occur_char.begin() ;
		itor_num!=occur_num.end(), itor_char!=occur_char.end();
		itor_num++, itor_char++){
			char* word_buffer = new char[(*itor_char).size()+1];
			strcpy(word_buffer, (*itor_char).c_str());

			if(!strcmp(word_buffer,p->word)){
				occur_num.erase(itor_num);
				occur_char.erase(itor_char);
				delete []word_buffer;
				break;
			}
			delete []word_buffer;
		}

		for(itor_num=occur_num.begin(), itor_char=occur_char.begin() ;
		itor_num!=occur_num.end(), itor_char!=occur_char.end();
		itor_num++, itor_char++){
			if(*itor_num <= p->count){
				occur_num.insert(itor_num, p->count);
				occur_char.insert(itor_char, p->word);
				break;
			}
		}
		return NULL;
	}

	hval = hash(key, num_buckets);
	p = new WordNode;
	p->count = 1;
	p->word = new char[strlen(key)+1];
	strcpy(p->word, key);
	p->next = bucket[hval];
	bucket[hval] = p;

	occur_char.push_back(p->word);
	occur_num.push_back(p->count);

	return p;
}

/* get_statistics is function that calculate mean loading density and standard eviation */
void HashTable::get_statistics(double *mean, double *stdev){
	int slots;
	double sum_slots=0.0;
	double sum_slots_2=0.0;
	WordNode *p;

	for(int i=0; i<num_buckets; i++){
		slots=0;
		for(p=bucket[i]; p!=NULL; p=p->next) slots++;
		sum_slots += slots;
	}
	*mean = (double)sum_slots/num_buckets;

	for(int i=0; i<num_buckets; i++){
		slots=0;
		for(p=bucket[i]; p!=NULL; p=p->next) slots++;
		sum_slots_2 += (slots-*mean)*(slots-*mean);
	}
	*stdev = (double)sqrt(sum_slots_2/num_buckets);

}

/* get_chain_lengths is function that calculate minimum chain length and maximum chain length */
void HashTable::get_chain_lengths(int *min, int *max){
	int slots;
	WordNode *p;

	*min = INT_MAX;
	*max = INT_MIN;

	for(int i=0; i<num_buckets; i++){
		slots=0;
		for(p=bucket[i]; p!=NULL; p=p->next) slots++;
		if(slots < *min) *min = slots;
		if(slots > *max) *max = slots;
	}

}

/* number_of_comparisons is function that return compare number */
void HashTable::number_of_comparisons(int *compare){
	*compare = num_compares;
}

/* Hash_print is function that print current hash table status */
void HashTable::Hash_print(){
	cout << num_buckets << endl;
	for(int i=1; i<num_buckets; i++){
		cout<<"----- hash["<<i<<"] -----" <<endl;
		WordNode *e;
		for(e=bucket[i]; e!=NULL; e=e->next){
			cout<< e->count <<" "<< e->word<<endl;
		}
		cout << endl;
	}
}

/* Occur_print is function that print top 20 most frequent words in decreasing order */
void HashTable::Occur_print(){
	int i;
	for(itor_num=occur_num.begin(), itor_char=occur_char.begin(), i=0 ;
        i<20;
        itor_num++, itor_char++, i++){
		cout<<"Rank "<<i+1<<"=>"<< " Occurence : " << *itor_num <<" / Word : "<<*itor_char<<endl;
	}
}
