#include<iostream>
#include"DAlgoritm.h"
#include <fstream>
#include"input_data_function.h"
using namespace std;


int main() {
	try {
		setlocale(LC_ALL, "RUS");
		ifstream vvod("input.txt");
		int* path = NULL;
		int* d = NULL;
		List<string>* list_fly = new List<string>();
		string city_Start;
		string city_End;
		InputInFile(list_fly, vvod);
		cout << "Flights: " << endl;
		for (int i = 0; i < list_fly->get_size(); i++)
			cout << list_fly->at(i) << endl;
		cout <<  endl;
		cout << "Enter the start point" << endl;
		getline(cin, city_Start);
		cout << "Enter the finish point" << endl;
		getline(cin, city_End);
		AdjList* adj = new AdjList(list_fly);
		cout << adj->DAlgorithm(city_Start, city_End);
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
	}
	system("pause");
}
