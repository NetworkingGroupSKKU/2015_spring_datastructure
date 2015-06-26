/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment3 */
/* chart.cpp */
/* by Ji Min Kim */

#include <iostream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>


using namespace std;


string word[20]= { "the", "internet", "of", "is",
	"to", "a", "in", "and",
	"datagram", "protocol", "be", "for",
	"this", "address", "header", "data",
	"fragment", "an", "length", "field" };

int number[20]= { 901, 302, 295, 281, 
	279, 221, 193, 176, 
	175, 141, 120, 115,
	113, 101, 94, 88,
	86, 84, 77, 68 };

class Chart{
public:
	/* Private function 'scale()' scale numbers when number is over fixed column*/
	void scale(){

		float max=901;
		float scalingFactor;

		scalingFactor = 80 / max;

//		cout << scalingFactor << endl;

		for(int i=0; i<20 ; i++){
			number[i] = number[i]*scalingFactor;
		}
	}

	/* Private function 'draw()' make text-based chart in proper bound.*/
	void draw(){
		int j=0;

		cout << "x axis is <standard scale>" << endl;
		cout << "y axis is <standard scale>" << endl;

		do{
			cout << setw(10) << setfill(' ')<< word[j] << " : ";

			for(int i=0; i<number[j]; i++){
				cout<< "*" ;
			}
			cout << endl;
			j++;
		} while( j < 20 );

	}
	



	/* Public function desctiption is in 'chartFunc.cpp'*/
	void drawChart(void){	
	scale();
	draw();
	}

};


int main ( ){

	Chart chart;

	/* Check last argument. If that is filename, call function 'getFilename' 
	for fetching number in file. Else, call function 'getInput' for fetching 
	number through command line. After finishing option check, draw proper chart*/
/*	for(int i=1 ; i<argc; i++){
		if(i==argc-1){
			if( !chart.OptionValid(argv[i]) ) chart.getFileName(argv[i]);
			else chart.getInput(argv[i]);
			break;
		}
		chart.OptionCheck(argv[i]);
	}*/


	chart.drawChart();


	return 0;
}
