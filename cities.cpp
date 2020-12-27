
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;
#include <cstring>

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

//Prompts user for the cities they want to add
void GetCity_n_pop(const char* FileName,CityStruct);

//Search for city by name 
//Returns 0 if no city by that name was found
// else displays the city with the same name 
// and returns the number of cities found
void Searchbyname(const char* FileName);

/*char userAnswer();*/



int main() {
	char FileName[] ="cities.bin";
	CityStruct AddCity;
	char inp;
	
	clearfile(FileName);
	
    // Adding cities to the cit
	do {
	cout<<endl;
	cout<< "Do you want to add Cities to the file? (y for yes and n for no): ";
	cin>>inp;
	}while (inp != 'y' && inp != 'n' && inp != 'Y' && inp != 'N'); 

	if (inp == 'Y' || inp == 'y') {
	 	GetCity_n_pop( FileName,AddCity);
	}

	//searching by city name 
	do {
	cout<<endl;
	cout<<"Do you want to search for a specific city? (Enter yes and n for no): ";
    cin>>inp;
	}while (inp != 'y' && inp != 'n' && inp != 'Y' && inp != 'N');
	
	if (inp == 'Y' || inp == 'y') {
	  Searchbyname(FileName);
	}

    //display the file
	do {
	cout<<endl;
	cout<<"Do you want to display the file? (y for yes and n for no): ";
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

void GetCity_n_pop(const char* FileName, CityStruct AddCity) {
	char userInput;
	do {

		cout << "Please enter the city name: ";
		cin>>AddCity.cityname;
		cout<<"Now, enter the population of the city: ";
		cin>>AddCity.population;
		writeInputFIle(FileName, AddCity);
		

		cout<<endl;
		cout<< "Do you want to add another(y for yes and n for no): ";
		cin>>userInput;
	}while(userInput == 'y' || userInput == 'Y');
		
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

void Searchbyname(const char* FileName){
	char targetCity[30];
	char keepSearching;

	ifstream checkStream(FileName, ios::in| ios::binary);
	if(!checkStream ) {
		cout<<"Sorry couldn't open file for searching"<<endl;
		return;
	}

	// goes to the end of file 
	checkStream.seekg(0,ios::end);

	//returns the end of file then divides by the size of CityStruct
	int numberOfRecords = checkStream.tellg()/sizeof(CityStruct);

	// Creates an array of Structs
	CityStruct SearchbyCities[numberOfRecords];
	
	//returns to the beginning of file
	checkStream.seekg(0,ios::beg);
	checkStream.read((char*)SearchbyCities, sizeof(CityStruct)*numberOfRecords);
	checkStream.close();
   do 
   {
	 cout<<"Enter the name of the city you want to find: ";
	 cin>>targetCity;
	 int matches=0;
	 for (int i =0; i< numberOfRecords; i++) {
		if (strcmp(targetCity,SearchbyCities[i].cityname)==0) {
		  matches++;
		}
	 }
	 cout<<"There are "<< matches << " cities that matched the target:"<<endl;
	 if (matches>0)
	 {
	  cout<<"Matched city: "<<endl;
	  for (int i =0; i< numberOfRecords; i++) {
		if (strcmp(targetCity,SearchbyCities[i].cityname)==0) {
		  cout<< "City: " << SearchbyCities[i].cityname<<endl;
		  cout <<"Population "<< SearchbyCities[i].population<<endl<<endl;
		}
	  }
	}
	 cout<<endl;
	 cout<< "Do you want to search for another city? (y for yes and n for no): ";
	 cin>>keepSearching;
    }while (keepSearching == 'y' ||  keepSearching == 'Y'); 
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


