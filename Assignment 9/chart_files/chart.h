/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment3 */
/* chart.h */
/* by Ji Min Kim */


#ifndef __CHART_H_
#define __CHART_H_

#include <fstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class Chart{
private:
	/* Private parameter that contains what option is entered
	and data for counting, column, logscale and so on. */
	string Filename;
	int File_En;

	vector<float> number;
	int size;

	int min_En;
	float min;

	int Max_En;
	float Max;

	float Avg;
	float Stdev;

	int col_En;
	int column;

	int period_En;
	float period;
	float period_min;
	float period_Max;
	int periodNum;

	int *count_addr;
	float scalingFactor;

	int fraction;

	int xlog_En;
	int ylog_En;

	/* Private function 'minimum()','Maximum()' store minimum, maximum value
	of entering numbers at min, Max */
	void minimum(){
		min = number[0];
		if(min_En) cout << "minimum value is " << min << endl;
	}

	void Maximum(){
		Max = number[number.size()-1];
		if(Max_En) cout << "Maximum value is " << Max << endl;
	}

	void average(){
		int sum_degree=0;
		for(int i=0; i<number.size(); i++){
			sum_degree += number[i];
		}
		Avg = (float)sum_degree/number.size();
		cout << "Average of degree is " << Avg << endl;	
	}	

	void standard_deviation(){
		int sum_degree_2=0;
		for(int i=0; i<number.size(); i++){
			sum_degree_2 += (number[i]-Avg)*(number[i]-Avg);
		}
		Stdev = (float)sqrt(sum_degree_2/number.size());
		cout << "Standard deviation of degree is " << Stdev << endl;
	}


	/* Private function 'formatcheck' assert execution 
	when wrong format is entered*/
	void formatcheck(char *array, int i){
		if( i == strlen(array)){
			printf("Wrong format : %s \n", array);
			assert( 1 == 0);
		}
	}

	/* Private function 'columnFix' is called when '-c' option
	is entered, and store column number at column */
	void columnFix(char *array){
		char buffer_col[strlen(array)-3];
		int i = 3;
		formatcheck(array,i);
		for(i = 3 ; i<strlen(array); i++){
			buffer_col[i-3] = array[i];
		}
		column = atoi(buffer_col);
	}

	/* Private function 'periodFix' is called when '-r' option
	is entered, and store minimum, maximum, interval of period */
	void periodFix(char *array){
		char buffer_min[strlen(array)-3];
		char buffer_Max[strlen(array)-3];
		char buffer_period[strlen(array)-3];

		int i = 3;
		int j = 0;

		formatcheck(array,i);

		while ( array[i] != ':' ){
			formatcheck(array,i);
			buffer_min[j] = array[i];
			i++;
			j++;
		}

		formatcheck(array,i);

		period_min = atof(buffer_min);
		i++;
		j=0;


		while ( array[i] != ':' ){
			formatcheck(array,i);
			buffer_Max[j] = array[i];
			i++;
			j++;
		}

		period_Max = atof(buffer_Max);
		i++;
		j=0;
		int fin = strlen(array) - i;
		fraction = fin-2;

		formatcheck(array,i);


		for(j=0; j<fin; j++){
			buffer_period[j] = array[i];
			i++;
		}
		period = atof(buffer_period);

		/* Assert execution if wrong range is entered */
		if( period_min >= period_Max ) assert( period_min < period_Max);
		else if( period > (period_Max - period_min) ) assert( period <= (period_Max - period_min) );
		else if( period == 0 ) assert( period != 0 );
	}

	/* Private function 'countingNum' calculate number of entered number
	according to minimum, maximum, interval of period */
	void countingNum(){
		float lower_bound = period_min;
		float upper_bound = lower_bound + period;
		int i=0;
		int j=0;

		float Num = (period_Max - period_min) / period;
		periodNum = ceil(Num);

		int *count = new int[periodNum];
		count_addr = count;

		for(i=0 ; i<periodNum ; i++){
			count_addr[i] = 0;
		}

		i=0;

		/* For floating point calculation, add 0.000001 for fixing error */
		while(i<size){
			if( (upper_bound) <= period_Max){
				if( ((number[i]+(1e-6)) < upper_bound)  && (number[i]+(1e-6) >= lower_bound) ){
					count_addr[j]++;
					i++;
				}
				else if (((number[i]+(1e-6)) >= upper_bound)){
					lower_bound = upper_bound;
					upper_bound = lower_bound + period;
					j++;
				}
				else i++;
			}
			else{
				upper_bound = period_Max;

				if( ((number[i]+(1e-6)) < upper_bound) && ((number[i]+(1e-6)) >= lower_bound) ){
                                        count_addr[periodNum-1]++;
                                        i++;
                                }
				else i++;
			}
		}

	}
	/* Private function 'scale()' scale numbers when number is over fixed column*/
	void scale(){

		float max;

		if( ylog_En){
			for(int i=0; i <periodNum; i++) count_addr[i] = log(count_addr[i]);
		}
		vector <int> buffer(count_addr, count_addr + periodNum);
		sort(buffer.begin(), buffer.end()) ;

		max=buffer[periodNum-1];

		if(max > column) scalingFactor = column / max;
		else scalingFactor = 1;


		for(int i=0; i<periodNum ; i++){
			count_addr[i] = count_addr[i]*scalingFactor;
		}
	}

	/* Private function 'draw()' make text-based chart in proper bound.*/
	void draw(){
		float lower_bound = period_min;
		float upper_bound = lower_bound + period;
		int j=0;

		cout<<fixed;
		cout.precision(fraction);

		if(xlog_En) cout << "x axis is <log scale>" << endl;
		else cout << "x axis is <standard scale>" << endl;

		if(ylog_En) cout << "y axis is <log scale>" << endl;
		else cout << "y axis is <standard scale>" << endl;

		do{
			cout << lower_bound << " - " << upper_bound << " :  ";

			for(int i=0; i<count_addr[j]; i++){
				cout<< "*" ;
			}
			cout << endl;
			lower_bound = upper_bound;
			upper_bound = lower_bound + period;
			if( (upper_bound+(1e-6)) > period_Max) upper_bound = period_Max;
			j++;
		} while( j < periodNum );

	}

	/* Private function 'setAuto()' set period automatically
	when '-r' option isn't enterd */
	void setAuto(){
		period_min = floor(min);
		period_Max = ceil(Max);

		period = (period_Max-period_min) / 20;

		fraction = 3;
	}

	/* Private function 'xlogScale()' change x-axis to log scale
	from standard scale. if period includes negative region, use
	absolute value. '*/
	void xlogScale(){
		float *buffer = &number[0];

		if( period_En ){
			if( period_min == 0 ) period_min = 0;
			else if( period_min <0 ) period_min = floor(-log(fabs(period_min)));
			else period_min = floor(log(period_min));

			if( period_Max == 0 ) period_Max = 0;
                        else if( period_Max <0 ) period_Max = ceil(-log(fabs(period_Max)));
                        else period_Max = ceil(log(period_Max));
		}
		else{
			if( min == 0) min ==0;
			else if(min < 0) min = -log(fabs(min));
			else min = log(min);

			if( Max == 0) Max == 0;
			else if(Max <0) Max = -log(fabs(Max));
			else Max = log(Max);
		}

		for(int i=0; i<size; i++){
			if( number[i] == 0 ) buffer[i] = 0;
			else if (number[i] < 0)	buffer[i]= -log(fabs(number[i]));
			else buffer[i] = log(number[i]);
		}


		number.clear();
		for(int i=0 ; i<size; i++){
			number.push_back(buffer[i]);
		}
	}


public:
	/* Public function desctiption is in 'chartFunc.cpp'*/
	Chart();
	void OptionCheck (char *array);
	bool OptionValid (char *array);
	void getFileName (char *array);
	void getInput (char *array);
	void drawChart(void);

};



#endif
