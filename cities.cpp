
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

struct  CityStruct {
	double population;
	char cityname[30];
};
void clearfile(const char* FileName);
// prompts the user if they want to clear out the file before proceeding

void writeInputFIle(const char* FileName, CityStruct);
//Promises to write the city and population into the binary file

void DisplayInputFile(const char* FileName);
//display what is currently written on file 

char userAnswer();

int main() {
	char FileName[] ="cities.bin";
	CityStruct AddCity;
	char inp;
	
	clearfile(FileName);
	
	do {
	cout<<endl;
	cout<< "Do you want to add Cities to the file (y for yes and n for no): ";
	cin>>inp;
	}while (inp != 'y' && inp != 'n' && inp != 'Y' && inp != 'N'); 
	
	while(inp == 'y' || inp == 'Y') {
		cout << "Please enter the city name: ";
		cin>>AddCity.cityname;
		cout<<"Now, enter the population of the city: ";
		cin>>AddCity.population;
		writeInputFIle(FileName, AddCity);
		
		do {
		cout<<endl;
		cout<< "Do you want to add another(y for yes and n for no): ";
		cin>>inp;
		}while (inp != 'y' && inp != 'n' && inp != 'Y' && inp != 'N'); 
		
	}
	
	do {
	cout<<endl;
	cout<<"Do you want to read the current file y for yes and n for no): ";
    cin>>inp;
	}while (inp != 'y' && inp != 'n' && inp != 'Y' && inp != 'N');
	
	if (inp == 'Y' || inp == 'y') {
	  DisplayInputFile(FileName);
	}
	return 0;
}

void clearfile (const char* FileName) {
	char cle;
	do {
	cout<<endl;
	cout << "Do you want to clearout previous input writtten to file(y for yes  and n for no): ";
	cin>>cle;
    }while (cle != 'y' && cle != 'n' && cle != 'Y' && cle != 'N');
	if (cle == 'n'|| cle == 'N') {
		return;
	}
	ofstream out (FileName, ios::out | ios::binary);
	if (out.fail()){
		cout<< "Couldn't properly open file"<<endl;
		exit(1);
	} 
	out.clear();
	out.close();
	cout <<endl;
	cout<< "File cleared"<<endl;
	

}
void writeInputFIle(const char* FileName, const CityStruct InputCity) {
	ofstream outfile (FileName, ios::out | ios::binary| ios::app);
	if (outfile.fail()){
		cout<< "Couldn't properly open file"<<endl;
		exit(1);
	}
    outfile.write((char*)&InputCity,sizeof(CityStruct));
    outfile.close();	
}

void DisplayInputFile(const char* FileName){
	
		ifstream Infile(FileName, ios::in|ios::binary);
	 if(!Infile) {
		 cout<<"Error, couldn't open"<<endl;
		 exit(1);
	 }
	// goes to the end of file 
	Infile.seekg(0,ios::end);
	//returns the end of file then divides by the size of CityStruct
	int numberOfRecords = Infile.tellg()/sizeof(CityStruct);
	// Creates an array of Structs
	CityStruct ReadingCities[numberOfRecords];
	//returns to the beginning of file
	Infile.seekg(0,ios::beg);
	Infile.read((char*)ReadingCities, sizeof(CityStruct)*numberOfRecords);
	Infile.close();
	
	for (int i =0; i< numberOfRecords; i++) {
		cout<< "City: " << ReadingCities[i].cityname<<endl;
        cout <<"Population "<< ReadingCities[i].population<<endl<<endl;
	}
}

