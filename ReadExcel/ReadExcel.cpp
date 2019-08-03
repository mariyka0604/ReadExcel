// ReadExcel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "zip_file.hpp"
using namespace std;

struct Cell 
{
	string c;
	char t;
	string val;
};


int main()
{
	//setlocale(LC_ALL, "RUS");

	string input_path;
	string output_path;

	/*cout << "Input file: ";
	cin >> input_path;
	cout << "Output file: ";
	cin >> output_path;*/

	input_path = "Book1.xlsx";
	output_path = "Output.txt";

	//Определение имени входного файла
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

	//int sheets_count = 0;
	vector <string> arr_sheets;

	size_t pos_start = workbook.find("<sheets>", 0) + 8;
	size_t pos_end = workbook.find("</sheets>", 0);
	workbook = workbook.substr(pos_start, pos_end - pos_start);


	//Чтение имен листов и подсчет их количества
	pos_start = 0;
	pos_end = 0;
	while (1) 
	{
		pos_start = workbook.find("<sheet name=\"", pos_start);
		if (pos_start == workbook.npos) {
			break;
		}
		pos_end = workbook.find("\" ", pos_start + 13);
		arr_sheets.push_back(workbook.substr(pos_start + 13, pos_end - pos_start - 13));
		//sheets_count++;
		pos_start = pos_end;
	}

	//Чтение строк
	pos_start = 0;
	pos_end = 0;
	string shared_strings = file.read("xl/sharedStrings.xml");
	vector <string> arr_strings;
	while (1) {
		pos_start = shared_strings.find("<t>", pos_start);
		if (pos_start == shared_strings.npos) {
			break;
		}
		pos_end = shared_strings.find("</t>", pos_start + 3);
		arr_strings.push_back(shared_strings.substr(pos_start + 3, pos_end - (pos_start + 3)));
		pos_start = pos_end;
	}

	//чтение листов
	pos_start = 0;
	pos_end = 0;
	size_t cell_start = 0;
	size_t cell_end = 0;
	string c;
	char t;
	string v;
	string cell;
	string sheet;
	string sheet_name;
	vector <string> cells;
	vector <Cell> arr_cells;
	//Для каждого листа
	for (int i = 1; i < arr_sheets.size() + 1; i++) {
		sheet_name = "xl/worksheets/sheet";
		sheet_name += to_string(i);
		sheet_name += ".xml";
		cout << sheet_name << "\n";
		sheet = file.read(sheet_name);
		//Собираем строки ячеек в вектор cells
		while (1) {
			//Нашли ячейку
			cell_start = sheet.find("<c ", cell_start);
			if (cell_start == sheet.npos) {
				break;
			};
			cell_end = sheet.find("</c>", cell_start + 3);
			cells.push_back(sheet.substr(cell_start, cell_end + 4 - (cell_start)));
			cell_start = cell_end;
		}

		//Теперь разбираем каждую ячейку
		for (int j = 0; j < cells.size(); j++) {
			cell = cells.at(j);
			pos_start = 0;
			pos_end = 0;
			// Ищем r, t, v
			while (1) {
				pos_start = cell.find(" r=\"", pos_start);
				if (pos_start == cells.at(j).npos) {
					break;
				}
				pos_end = cell.find("\" ", pos_start + 6);
				c = sheet.substr(pos_start + 6, pos_end - (pos_start + 6));
				pos_start = pos_end;
				pos_start = sheet.find("t=\"", pos_start);
			}

		}


	}
	
	//Вывод в файл
	ofstream out_file(output_path);
	out_file << "Input: " + input_filename + "\n";
	out_file << workbook + "\n";
	for (int i = 0; i < arr_sheets.size(); i++) {
		out_file << "Sheet: " + arr_sheets.at(i) + "\n";
	}
	for (int i = 0; i < cells.size(); i++) {
		out_file << cells.at(i) + "\n";
	}
	out_file.close();

	return 0;
}
