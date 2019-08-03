// ReadExcel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zip_file.hpp"
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

	miniz_cpp::zip_file file(input_filename);

	string workbook = file.read("xl/workbook.xml");

	int sheets_count = 0;
	vector <string> arr_sheets;

	size_t sheets_start = workbook.find("<sheets>", 0) + 8;
	size_t sheets_end = workbook.find("</sheets>", 0);
	workbook = workbook.substr(sheets_start, sheets_end - sheets_start);

	sheets_start = 0;
	while (1) 
	{
		sheets_start = workbook.find("<sheet name=\"", sheets_start);
		if (sheets_start == workbook.npos) {
			break;
		}
		sheets_end = workbook.find("\" ", sheets_start + 13);
		arr_sheets.push_back(workbook.substr(sheets_start + 13, sheets_end - sheets_start - 13));
		cout << sheets_start << "\n";
		cout << workbook.substr(sheets_start + 13, sheets_end - sheets_start - 13) << "\n";
		sheets_count++;
		sheets_start = sheets_end;
	}


	ofstream out_file(output_path);
	out_file << "Input: " + input_filename + "\n";
	out_file << workbook + "\n";
	for (int i = 0; i < arr_sheets.size(); i++) {
		out_file << "Sheet: " + arr_sheets.at(i) + "\n";
	}
	out_file.close();

	return 0;
}

