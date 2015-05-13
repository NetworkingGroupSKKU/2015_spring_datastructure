/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment2 */
/* by Ji Min Kim */


#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <climits>
#include <math.h>

using namespace std;

/* Declare Class RandomGenerator */
class RandomGenerator{
/* PRIVATE */
private:
	/* Parameter that represents enabled option
	and entered data, generated random number */
	int FileOUT_En;

	int *Basic_Rand_addr;

	int Uniform_Int_En;
	int Uniform_Int_Min;
	int Uniform_Int_Max;
	int *Uniform_Int_Rand_addr;

	int Uniform_Double_En;
	double Uniform_Double_Min;
	double Uniform_Double_Max;
	double *Uniform_Double_Rand_addr;

	int Normal_En;
	double Normal_Avg;
	double Normal_Devi;
	double *Normal_Rand_addr;

	int Exponential_En;
	double Exponential_Mean;
	double *Exponential_Rand_addr;

	string FileOUT_Name;


	/* Function that be called when -f option enter*/
        void FileOUT(char *array){
		int i;
		int length = strlen(array);
		char buffer[length-3];
		FileOUT_En = 1;

		for( i=3; i<=length ; i++){
			buffer[i-3]=array[i];
		}
		FileOUT_Name = buffer;
        }

	/* Function that be called when -u option enter*/
        void Uniform_Int(char *array){
		int i;
		int j;
		int length = strlen(array);
		char buffer_min[length-3];
		char buffer_max[length-3];
		char *pch;
		int pos;
		Uniform_Int_En = 1;

		/* Check ':' position */
		pch=strrchr(array,':');
		pos=pch-array;

		/* Assert execution when invalid format */
		if(pos == 2){
		cout << "You must insert ':' between number" << endl;
		assert(pos != 2);
		}

		for(i=3; i<pos; i++){
			buffer_min[i-3] = array[i];
		}

		Uniform_Int_Min = atoi(buffer_min);

		j=0;

		for(i=i+1; i<length; i++){
			buffer_max[j] = array[i];
			j++;
			buffer_max[j] = '\0';
		}
		Uniform_Int_Max = atoi(buffer_max);
        }

	/* Function that be called when -d option enter */
        void Uniform_Double(char *array){
		int i;
                int j;
                int length = strlen(array);
                char buffer_min[length-3];
                char buffer_max[length-3];
                char *pch;
                int pos;

		Uniform_Double_En = 1;

		/* Check ':' position */
                pch=strrchr(array,':');
                pos=pch-array;

		/* Assert execution when invalid format */
                if(pos == 2){
                cout << "You must insert ':' between number" << endl;
                assert(pos != 2);
                }

                for(i=3; i<pos; i++){
                        buffer_min[i-3] = array[i];
                }

                Uniform_Double_Min = atof(buffer_min);

                j=0;
		for(i=i+1; i<length; i++){
                        buffer_max[j] = array[i];
                        j++;
			buffer_max[j] = '\0';
                }
                Uniform_Double_Max = atof(buffer_max);
        }

	/* Functon that be called When -n option enter */
        void Normal(char *array){
		int i;
                int j;
                int length = strlen(array);
                char buffer_avg[length-3];
                char buffer_devi[length-3];
                char *pch;
                int pos;

		Normal_En = 1;

		/* Check ':' position*/
                pch=strrchr(array,':');
                pos=pch-array;

		/* Assert execution when invalid format */
                if(pos == 2){
                cout << "You must insert ':' between number" << endl;
                assert(pos != 2);
                }

                for(i=3; i<pos; i++){
                        buffer_avg[i-3] = array[i];
                }

                Normal_Avg = atof(buffer_avg);

                j=0;
                for(i=i+1; i<length; i++){
                        buffer_devi[j] = array[i];
                        j++;
			buffer_devi[j] = '\0';
                }
                Normal_Devi = atof(buffer_devi);

        }

	/* Function that be called when -e option enter */
        void Exponential(char *array){
		int i;
                int length = strlen(array);
                char buffer_mean[length-3];

	        Exponential_En = 1;

                for(i=3; i<length; i++){
                        buffer_mean[i-3] = array[i];
                }

                Exponential_Mean = atof(buffer_mean);
        }


/*PUBLIC*/
public:
	/* Constructor */
	RandomGenerator(){
		FileOUT_En = 0;

		Uniform_Int_En = 0;
		Uniform_Int_Min = 0;
		Uniform_Int_Max = 0;

        	Uniform_Double_En = 0;
        	Uniform_Double_Min = 0;
        	Uniform_Double_Max = 0;

        	Normal_En = 0;
        	Normal_Avg = 0;
        	Normal_Devi = 0;

        	Exponential_En = 0;
        	Exponential_Mean = 0;
	}

	/* Function that check option and call proper function in PRIVATE */
	void Option_check(char *OptionMask, char *array){
		if(strcmp(OptionMask, "-f:")==0 ) FileOUT(array);
		else if(strcmp(OptionMask,"-u:")==0 ) Uniform_Int(array);
		else if(strcmp(OptionMask,"-d:")==0 ) Uniform_Double(array);
		else if(strcmp(OptionMask,"-n:")==0 ) Normal(array);
		else if(strcmp(OptionMask,"-e:")==0 ) Exponential(array);
		else cout << "ERROR" << endl;
	}


	/* Function that check Option_En in PRIVATE
	and generate proper random number */
	void Random_number(char *array){
		int i,m;
		double n,d,a,b;
		int number;
		int length=0;
		number = atoi(array);

		int *Basic_Rand = new int[number];
		int *Uniform_Int_Rand = new int[number];
		double *Uniform_Double_Rand = new double[number];
		double *Normal_Rand = new double[number];
		double *Exponential_Rand = new double[number];

		Basic_Rand_addr = Basic_Rand;
		Uniform_Int_Rand_addr = Uniform_Int_Rand;
		Uniform_Double_Rand_addr = Uniform_Double_Rand;
		Normal_Rand_addr = Normal_Rand;
		Exponential_Rand_addr = Exponential_Rand;

		/* Assert execution when number is 0 or invalid format */
		if(number == 0){
			cout << " You must write valid number that larger than 0 "<< endl;
			assert( number != 0 );
	 	}

		srand(time(NULL));

		/* Generate random number according to option and store each option array */
		for(i=0; i<number; i++){
			if(Uniform_Int_En){
				n = (double) rand()/RAND_MAX ;
				m = n*(Uniform_Int_Max - Uniform_Int_Min) + Uniform_Int_Min;
				Uniform_Int_Rand_addr[i] = m;
			}

			if(Uniform_Double_En){
				n = (double) rand() / RAND_MAX ;
				d = n*(Uniform_Double_Max - Uniform_Double_Min) + Uniform_Double_Min;
				Uniform_Double_Rand_addr[i] = d;
			}
			if(Normal_En){
				do{
					n = 2*((double) rand() / RAND_MAX) -1;
					d = 2*((double) rand() / RAND_MAX) -1;
					a = n*n + d*d;
				} while (a>=1 || a==0);
				a = sqrt((-2*log(a))/a);
				b = n * a;
				b = (Normal_Devi * b) + Normal_Avg;
				Normal_Rand_addr[i] = b;
			}
			if(Exponential_En){
				n = (double) rand()/RAND_MAX;
				d = -Exponential_Mean*log(n);
				Exponential_Rand_addr[i] = d;
			}
			if( (Uniform_Int_En==0) && (Uniform_Double_En==0) && (Normal_En==0) && (Exponential_En==0)){
				n = (double) rand()/RAND_MAX;
				m = n * INT_MAX;
				Basic_Rand_addr[i] = m;
			}
		}


	}

	/* Function that print random nuber.
	This function is divided two part according to whether -f option is enabled or inenabled */
	void Random_print(char *array){
		int number;
		int length=0;
		int i;

                length = FileOUT_Name.length();
		char name_buffer[length];
		number = atoi(array);

              if(FileOUT_En){
                      strcpy(name_buffer, FileOUT_Name.c_str());
                      ofstream outputfile (name_buffer);
			if(outputfile.is_open()){
				if(Uniform_Int_En){
//					outputfile << "Uniform random numbers of integer type no less than " << Uniform_Int_Min << " but less than " << Uniform_Int_Max << endl;
					for(i=0; i<number; i++)  outputfile << Uniform_Int_Rand_addr[i]  << endl;
       		                }

	                        if(Uniform_Double_En){
//					outputfile << "Uniform random numbers of double type no less than " << Uniform_Double_Min << " but less than " << Uniform_Double_Max << endl;
                                        for(i=0; i<number; i++)  outputfile << Uniform_Double_Rand_addr[i] << endl;
                	        }

	                        if(Normal_En){
//					outputfile << "Normal random numbers with average of " << Normal_Avg << " and standard deviation " << Normal_Devi << endl;
                                        for(i=0; i<number; i++)  outputfile << Normal_Rand_addr[i] << endl;
	                        }
        	                if(Exponential_En){
//					outputfile << "Exponential random number with mean " << Exponential_Mean << endl;
                                        for(i=0; i<number; i++)  outputfile << Exponential_Rand_addr[i] << endl;
	                        }
				if( (Uniform_Int_En==0) && (Uniform_Double_En==0) && (Normal_En==0) && (Exponential_En==0)){
//					outputfile << "Uniform random numbers of integer type " << endl;
                                        for(i=0; i<number; i++)  outputfile << Basic_Rand_addr[i] << endl;
	                        }
				outputfile.close();
			}
              }
             else {
			if(Uniform_Int_En){
                               cout << "Uniform random numbers of integer type no less than " << Uniform_Int_Min << " but less than " << Uniform_Int_Max << endl;
                               for(i=0; i<number; i++)  cout << Uniform_Int_Rand_addr[i]  << endl;
                        }

                        if(Uniform_Double_En){
                               cout << "Uniform random numbers of double type no less than " << Uniform_Double_Min << " but less than " << Uniform_Double_Max << endl;
	                       for(i=0; i<number; i++)  cout << Uniform_Double_Rand_addr[i] << endl;
                        }

                        if(Normal_En){
                               cout << "Normal random numbers with average of " << Normal_Avg << " and standard deviation " << Normal_Devi << endl;
                               for(i=0; i<number; i++)  cout << Normal_Rand_addr[i] << endl;
                        }

                        if(Exponential_En){
                               cout << "Exponential random number with mean " << Exponential_Mean << endl;
                               for(i=0; i<number; i++)  cout << Exponential_Rand_addr[i] << endl;
                        }

                        if( (Uniform_Int_En==0) && (Uniform_Double_En==0) && (Normal_En==0) && (Exponential_En==0)){
                               cout << "Uniform random numbers of integer type " << endl;
                               for(i=0; i<number; i++)  cout << Basic_Rand_addr[i] << endl;
                        }

	      }
		delete Basic_Rand_addr;
                delete Uniform_Int_Rand_addr;
                delete Uniform_Double_Rand_addr;
                delete Normal_Rand_addr;
                delete Exponential_Rand_addr;

	}

};


int main (int argc, char *argv[]){

	int i=0;
	int j=0;
	/* OptionMask is mask that filter option part only*/
	char * OptionMask = new char[3];
	RandomGenerator rg;

	for(i=1; i<(argc-1); i++){
		memcpy(OptionMask, argv[i], sizeof(char)*3);
		rg.Option_check(OptionMask,argv[i]);
	}

	rg.Random_number(argv[argc-1]);
	rg.Random_print(argv[argc-1]);

	delete []OptionMask;

	return 0;

}


