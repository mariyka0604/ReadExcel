// ReadExcel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;



int main()
{
	string input_path;
	string output_path;

	cout << "Input file: ";
	getline(cin, input_path);
	cout << "Output file: ";
	getline(cin, output_path);

	//cout << "Input file:" + input_path + "\n";
	//cout << "Output file:" + output_path + "\n";

	ofstream out_file(output_path);
	out_file.open(output_path);
	out_file << "Hello World!";
	out_file.close();	

	cin.get();


	return 0;
}

