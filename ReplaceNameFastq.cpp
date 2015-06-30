//This script merge result file
// usage:  g++ ReplaceNameFastq.cpp -o ReplaceNameFastq
// ./ReplaceNameFastq input.fastq ListName.txt output.fastq
// grep ^"@G" *.fastq > fileID.txt
// cat *.fastq > test.fastq
//eg.: ./ReplaceNameFastq test.fastq fileID.txt newID.fastq
// you can run on OSX or Linux
// You need GCC to compile
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include <vector>
#include <sstream>

using namespace std;

int main(int argc, char *argv[])
{
int checkFile(ifstream &input); 
int fileToDataSpace (string filenameDIR,vector <vector <string> > &data);
void printMatrix(vector <vector <string> > &dad);

//check if the command correct
if (argc!=4){
	cout<<"usage: ./ReplaceNameFastq inputFastqfile.fastq ListofName.txt OuputFastq.Fastq"<< endl <<flush;
	return 1;
}

//read fileID file
string filename = argv[2];
vector <vector <string> > data4;
fileToDataSpace(filename,data4);

//open file: your fastq file
ifstream inputTable;
inputTable.open(argv[1]);
checkFile(inputTable);
string table;


//file for result
ofstream myfile;
myfile.open (argv[3]);
int num=0;

// Main loop to write file
while(getline(inputTable,table))
{
	// if you see ID which start from @G
	if(table.substr(0,2)=="@G"){
		cout<<num<<endl<<flush;
		// fine your filename from fileID file by matching ID
		for (int i=0;i<data4.size();i++){
			if(table==data4[i][2]){
				//Write ID name + : " fileName = result ex. @G4242423:1.fastq
				myfile << data4[i][2]+":"+data4[i][1]+"\n";
			}
		}		
	}else{
		//write to the file other things which is not ID
		myfile << table +"\n";
	}	
num++;
}//while

inputTable.close();




return 0;
}
//this is end of main

// check openfile
int checkFile(ifstream &input)
{
	if(input.fail()){                           //    Check open
       cerr << "Can't open file\n";
       exit(EXIT_FAILURE);
       //return 1;
	}else{return 0;}
}

//file contents to data-vector
int fileToDataSpace (string filenameDIR,vector <vector <string> > &data){
	char const* fin = filenameDIR.c_str();
	ifstream input;
	string s;
	input.open(fin);
	checkFile(input);
	while(getline(input,s))
	{
		istringstream ss (s);
		//this add data into the column (second number)
		vector <string> record;
		record.push_back(s);
		while (ss)
		{
			string s1;
			if(!getline(ss,s1,':')) break;
			if(s1!=""){
				record.push_back(s1);
			}
		}
		//this add data into the row (first number)
		data.push_back(record);
	}//while
	input.close();
	return 0;
}

void printMatrix(vector <vector <string> > &dad){
	for (int i=0;i<dad.size();i++){
		for (int j=0;j<dad[i].size();j++){
			cout<<dad[i][j]+" "<<flush;
		}
	cout<<endl<<flush;
	}
}