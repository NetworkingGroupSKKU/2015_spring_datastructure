/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment3 */
/* chartFunc.cpp */
/* by Ji Min Kim */

////* This file descript function that included in 'chart.h' */////

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include "chart.h"
using namespace std;

/* 'Chart()' is constructor.*/
Chart::Chart(){
	File_En=0;
        size=0;
        min_En=0;
        min=0;
	Max_En=0;
	Max=0;
	col_En=0;
	column=80;
	period_En=0;
	period=0;
	period_min=0;
	period_Max=0;
	periodNum=0;
	scalingFactor=0;
	fraction=0;
	xlog_En=0;
	ylog_En=0;
}

/* 'OptionCheck' is function that check argument and 
,if it is valid option, store possiblity at proper prameter.*/
void Chart::OptionCheck (char *array){

	char* buffer= new char[3];

	if(strcmp(array,"-m")==0 ) min_En = 1;
	else if(strcmp(array,"-M")==0) Max_En = 1;
	else if(strcmp(array,"-xlog")==0) xlog_En = 1;
	else if(strcmp(array,"-ylog")==0) ylog_En = 1;
	else{
		memcpy(buffer, array, sizeof(char)*3);

		if( strcmp(buffer,"-c:")==0 ){
			col_En = 1;
			columnFix(array);
		}
		else if( strcmp(buffer,"-r:")==0 ){
			period_En = 1;
			periodFix(array);
                }
		else{
                        cout << "Wrong format : " << array << endl;
                        assert(1 == 0);
		}

	}


	delete []buffer;
}


/* 'OptionValid' is function that check validation of argument */
bool Chart::OptionValid (char *array){
	char* buffer = new char[3];

	if( !strcmp(array,"-m") || !strcmp(array,"-M") || !strcmp(array,"-xlog") || !strcmp(array,"-ylog") ){
 	         delete []buffer;
		 return true;
	}
	else{
		memcpy(buffer, array, sizeof(char)*3);
		if( !strcmp(buffer,"-c:") || !strcmp(buffer,"-r:") ){
			 delete []buffer;
			 return true;
		}
		else{
			delete []buffer;
			return false;
		}
	}
}

/* 'getFileName' is function that receive 'filename' and
fetch numbers from 'filename' file. */
void Chart::getFileName (char *array){
	int i = 0;
	float buffer;
	File_En = 1;
	Filename = array;

	ifstream inputfile(array);
	if(inputfile.is_open()){
		while(inputfile >> buffer){
			number.push_back(buffer);
			i ++ ;
			number.resize(i);
			inputfile.get();
		}
		inputfile.close();
	}
	size = number.size();
	sort(number.begin(), number.end());
}

/* 'getInput' is function that fetch numbers from 
command line. */
void Chart::getInput (char *array){
	int i=0;
	float buffer;

	OptionCheck(array);

	while( cin>>buffer ){
		number.push_back(buffer);
		i++;
		number.resize(i);
	}
	size = number.size();
	sort(number.begin(), number.end());
}

/* 'drawChart' is function that print and draw
proper information. */
void Chart::drawChart(void){
	minimum();
	Maximum();
	if(xlog_En) xlogScale();
	if(!period_En) setAuto();
	countingNum();
	scale();
	draw();

	delete count_addr;
}
