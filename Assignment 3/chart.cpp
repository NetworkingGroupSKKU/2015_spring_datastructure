/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment3 */
/* chart.cpp */
/* by Ji Min Kim */

#include <iostream>

/* Include 'chart.h' that include functions*/
#include "chart.h"

using namespace std;


int main (int argc, char *argv[]){

	Chart chart;

	/* Check last argument. If that is filename, call function 'getFilename' 
	for fetching number in file. Else, call function 'getInput' for fetching 
	number through command line. After finishing option check, draw proper chart*/
	for(int i=1 ; i<argc; i++){
		if(i==argc-1){
			if( !chart.OptionValid(argv[i]) ) chart.getFileName(argv[i]);
			else chart.getInput(argv[i]);
			break;
		}
		chart.OptionCheck(argv[i]);
	}

	chart.drawChart();


	return 0;
}
