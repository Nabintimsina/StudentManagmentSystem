// Student Management System
// Written by : Nabin Timsina


#include<iostream>
#include<fstream>
using namespace std;

class Student {
	
	char name[30], address[50];
	int rollNo;
	
	public : 
		void readData();
		void showData();
		
		void writeData();
		void readOneRecord();
		void readAllRecord();
		void editRecord();
		void deleteRecord();
	
};

void Student::readData(){
	
	cout<<endl<<"---------------------"<<endl;
	cout<<"Enter the student Details : "<<endl;
	cout<<"Roll No : ";
	cin>>rollNo;
	
	cin.ignore();
	cout<<"Name : ";
	cin.get(name, 30);
	
	cin.ignore();
	cout<<"Address : ";
	cin.get(address, 50);
}

void Student::showData(){
	cout<<endl<<"---------------------"<<endl;
	
	cout<<"Student Information : "<<endl;
	cout<<"Roll No : "<<rollNo<<endl;
	cout<<"Name : "<<name<<endl;
	cout<<"Address : "<<address<<endl;
	
}

void Student::writeData(){
	
	readData();
	ofstream file("studentSystem.bat", ios::binary| ios::app);
	
	if(!file)
		cout<<"Error opening file.";
	
	file.write(reinterpret_cast<char*>(this), sizeof(*this));	
	
}


void Student::readAllRecord(){
	
	ifstream file("studentSystem.bat", ios::binary| ios::in);
	
	if(!file)
		cout<<"Error opening file.";
	
	while(!file.eof()){

		file.read(reinterpret_cast<char*>(this), sizeof(*this));
		this->showData();
		
	}
	
}

void Student::readOneRecord(){
	
	int n, choice;
	bool found = false;
	
	ifstream file("studentSystem.bat", ios::binary| ios::in);
	
	if(!file)
		cout<<"Error opening file.";
	
	file.seekg(0, ios::end);
	int count = file.tellg()/sizeof(*this);
	file.seekg(0, ios::beg);
	
	cout<<endl<<"There are "<<count<<" records. "<<endl;
	cout<<"Enter 1 - to search by record number \nEnter 2 - to search by roll no ."<<endl;
	cin>>choice;
	
	
	if(choice == 1){
	
	cout<<"Enter the record Number: ";
	cin>>n;
	
	file.seekg((n-1)* sizeof(*this));
	file.read(reinterpret_cast<char*>(this), sizeof(*this));
	this->showData();
	}
	
	else if(choice == 2){
		cout<<"Enter the roll Number: ";
		cin>>n;
		
		while(!found){
			file.read(reinterpret_cast<char*>(this), sizeof(*this));
			 
			 if(this->rollNo == n){
			 	this->showData();
			 	found = true;
			 }
		}
		
		
	}
	
	
}

void Student::editRecord(){
	
	int n;
	fstream file("studentSystem.bat", ios::binary| ios::in| ios::out);  //cant used app here.All writes go to
//	 the end of the file, no matter where you move the file pointer with seekp().

	
	if(!file)
		cout<<"Error opening file.";
	
	file.seekg(0, ios::end);
	int count = file.tellg()/sizeof(*this);
	
	cout<<endl<<"There are "<<count<<" records. "<<endl;
	cout<<"Enter the record to be edited : ";
	cin>>n;
	file.seekg((n-1)*sizeof(*this));
	cout<<"This record has following data : ";
	file.read(reinterpret_cast<char*>(this), sizeof(*this));
	this->showData();

	
	cout<<"Enter the data to be modified : ";
	this->readData();
	file.seekp((n-1)*sizeof(*this), ios::beg);
	file.write(reinterpret_cast<char*>(this), sizeof(*this));
	
	
}

void Student::deleteRecord(){
	
	int n;
	
	ifstream file("studentSystem.bat", ios::binary);

	
	if(!file)
		cout<<"Error opening file.";
	
	ofstream tempfile("temp.bat", ios::binary);
	
	file.seekg(0, ios::end);
	int count = file.tellg()/sizeof(*this);
	
	cout<<endl<<"There are "<<count<<" records. "<<endl;
	cout<<"Enter the record to be deleted : ";
	cin>>n;
	
	file.seekg(0, ios::beg);
	
	for(int i= 0; i<count; i++){
	
	
		file.read(reinterpret_cast<char*>(this), sizeof(*this));
		if(i == (n-1))
			continue;
			
		tempfile.write(reinterpret_cast<char*>(this), sizeof(*this));
		
	}
	
	tempfile.close(); //must be closed for removing and renaming files.
	file.close();
	
	remove("studentSystem.bat");
	rename("temp.bat","studentSystem.bat" );
	cout<<"Record deleted. "<<endl;
		
}

	



int main(){
	
	cout<<endl<<"Welcome to Student Management System"<<endl;
	Student s;
	int choice;

	do {
		cout<<endl<<"-----------------------------"<<endl;
		cout<<"Select one option below: "<<endl;
		cout<<"1 : Write a record to file"<<endl;
		cout<<"2 : Show all records from file"<<endl;
		cout<<"3 : Show One Record"<<endl;
		cout<<"4 : Edit a record "<<endl;
		cout<<"5 : Delete a record "<<endl;
		cout<<"6 : Exit"<<endl;
		cout<<"Enter your Choice : ";
		cin>>choice;

		switch(choice)
		{
			case 1:
				s.writeData();
				break;
			case 2:
				s.readAllRecord();
				break;
			case 3:
				s.readOneRecord();
				break;
			case 4:
				s.editRecord();
				break;
			case 5:
				s.deleteRecord();
				break;
			case 6:
				cout<<"Exiting Program. Thank you!"<<endl;
				break;
			default:
				cout<<"Invalid Choice. Please select again."<<endl;
		}

	} while(choice != 6);

	return 0;
}

	



