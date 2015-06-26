/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment8 */
/* BinTree.cpp */
/* by Ji Min Kim */

#include <iostream>
#include <cstring>

using namespace std;

/* Max is fixed total node number
MAXLEN is fixed char array length */
#define MAX 63
#define MAXLEN 4

/* class Bintree declare */
class BinTree;

/* b is pointer that indicate each node
root is pointer that indicate root node, b[0] */
BinTree *b[MAX];
BinTree *root ;

/* word is array that contains word list for making binary tree */
char word[MAX][MAXLEN]=
{"abc", "use", "std", "ext", "src", "fil", "red", "vec", "cpp", "bin", "vie",
"pro", "deb", "tem", "tst", "win", "hlp", "edt", "dat", "msw", "vis", "stu",
"exp", "for", "cat", "man", "dog", "sis", "bro", "tim", "tra", "res", "try",
"shf", "oth", "ver", "sam", "dav", "lib", "lan", "sin", "cos", "tag", "log",
"due", "des", "ice", "wat", "ins", "del", "out", "mal", "con", "mem", "dat",
"194", "set", "get", "put", "pul", "mot", "dow", "des"};

/* class BinTree define */
class BinTree{

private:

	/* m_word is array that represent current node's word
	m_lchild, m_rchild is pointer that indicate current node's left child, right child */
	char m_word[MAXLEN];
	BinTree *m_lchild, *m_rchild;

public:

	/* BinTree is constructor that insert word in node and set child */
	BinTree( char *name, BinTree *left_child=NULL, BinTree *right_child=NULL ){
		for(int i=0; i<MAXLEN; i++)
			m_word[i] = name[i];
		m_lchild = left_child;
		m_rchild = right_child;
	}

	/* lchid, rchild is function that return address of its child */
	BinTree *lchild(){
		return m_lchild;
	}
	BinTree *rchild(){
		return m_rchild;
	}

	/* get is function that return address of its word */
	const char *get() const{
		return &m_word[0];
	}
	/* pretty_print is function that print tree structure using 'sout' out stream method */
	void pretty_print ( ostream &sout, int tabcnt=0) const{

		for(int i=0; i<tabcnt; i++)
			sout << "\t";
		sout << m_word << endl;

		/* If current node is leaf, stop print and return */
		if(m_lchild != NULL) m_lchild->pretty_print( sout, tabcnt+1);
		if(m_rchild != NULL) m_rchild->pretty_print( sout, tabcnt+1);

		return;
	}
};


int main(){

	/* Construct binary tree and Set root */
	for(int i=31; i<MAX; i++)
		b[i] = new BinTree( word[i], NULL, NULL );
	for(int i=30; i>=0; i--)
		b[i] = new BinTree( word[i], b[2*i + 1], b[2*i + 2]);

	root = b[0];

	/* From root print out tree structure */

	root->pretty_print(cout);


	for(int i=0; i<MAX; i++)
		delete b[i];


	return 0;
}
