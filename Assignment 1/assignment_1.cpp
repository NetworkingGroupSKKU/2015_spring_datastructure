#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

struct Student
{
	char name[50];
};


void Shuffle_array(int*index, int nMax){
	int i, n;
	int nTmp;
	srand(time(NULL));
	for(i=nMax - 1; i >= 0; i--){
		n = rand()%nMax;
		nTmp = index[i];
		index[i] = index[n];
		index[n] = nTmp;
	}
}

int main()
{
	const int MAX_STUDENTS = 30;				// Total number of student
	Student students[MAX_STUDENTS];		// make struct of student
 	int ID[MAX_STUDENTS];

	int number_of_student = 0;
	ifstream read;
	read.open("student-names.txt");

	cout<<"before shuffle\n"<<endl;

	/*read txt file*/
	while(!read.eof()){
		read.getline(students[number_of_student].name, 50);	// read txt file and save name in struct
		ID[number_of_student]=number_of_student;
		cout<<students[number_of_student].name<<endl;
		number_of_student++;								// find number of student

	}
	
	cout<<"after shuffle\n"<<endl;

	Shuffle_array(ID, number_of_student);
	int j;
	for (j=0; j<number_of_student; j++){
		cout<<students[ID[j]].name<<endl;
	}

	read.close();
	return 0;
}
