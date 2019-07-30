// ReadExcel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;



int main()
{
	//setlocale(LC_ALL, "RUS");

	string input_path;
	string output_path;

	cout << "Input file: ";
	cin >> input_path;
	cout << "Output file: ";
	cin >> output_path;

	string input_filename;
	size_t sl = input_path.find_last_of("/\\", input_path.npos);
	if (sl == input_path.npos) {
		input_filename = input_path;
	}
	else {
		input_filename = input_path.substr(sl + 1, input_path.length() - sl);
	}


	ofstream out_file(output_path);
	out_file << "Input: " + input_filename + "\n";
	out_file.close();

	system("pause");
	return 0;
}

