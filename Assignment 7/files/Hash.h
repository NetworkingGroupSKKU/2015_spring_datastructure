/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment7 */
/* Hash.h */
/* by Ji Min Kim */
#ifndef __HASH_H_
#define __HASH_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <list>
#include <cassert>
#include <algorithm>

using namespace std;

/* WordNode is structure that contain word string and occurence. */
struct WordNode{
	char *word;
	int count;
	WordNode *next;
};

class HashTable{
private:
	/* Private parameter */
	int num_buckets;
	int num_compares;
	WordNode **bucket;
	int (*hash)(char *key, int num_buckets);

	/* Below list is used for occurence check. */
	list<string> occur_char;
	list<string>::iterator itor_char;
	list<int> occur_num;
	list<int>::iterator itor_num;

public:
	/* Public function description is in 'Hash.cpp' */
	HashTable(int num, int (*h)(char*, int));
	~HashTable();
	WordNode *find(char *key);
	WordNode *insert(char *key);
	void get_statistics(double *mean, double *stdev);
	void get_chain_lengths(int *min, int *max);
	void number_of_comparisons(int *compare);
	void Hash_print();
	void Occur_print();
};

#endif
