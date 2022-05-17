#include "pch.h"
#include "CppUnitTest.h"
#include"../../3sem_aisd_lab3/DAlgoritm.h"
#include <fstream>
#include"../../3sem_aisd_lab3/input_data_function.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestDijkstra
{
	TEST_CLASS(UnitTestDijkstra)
	{
	public:

		TEST_METHOD(TestAvailablePath)
		{
			ifstream vvod("C:\\Users\\Анна Рудницкая\\source\\repos\\3sem_aisd_lab3\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Moscow";
			string city_End = "Saint-Peterburg";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "Route:\nMoscow ->Saint-Peterburg \nThe best route for the price:20\n";
			Assert::AreEqual(adj->DAlgoritm(city_Start, city_End), cur);
		}
		TEST_METHOD(TestUnavailablePath)
		{
			ifstream vvod("C:\\Users\\Анна Рудницкая\\source\\repos\\3sem_aisd_lab3\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Vladivostok";
			string city_End = "Moscow";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "This route can't be built";
			Assert::AreEqual(adj->DAlgoritm(city_Start, city_End), cur);
		}
		TEST_METHOD(TestPathExeption)
		{
			try {
				ifstream vvod("C:\\Users\\Анна Рудницкая\\source\\repos\\3sem_aisd_lab3\\input.txt");
				List<string>* list_fly = new List<string>();
				string city_Start = "Vladivostok";
				string city_End = "Vladivostok";
				InputInFile(list_fly, vvod);
				AdjList* adj = new AdjList(list_fly);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "End city can't be equal to start city");
			}
		}
		TEST_METHOD(TestePath)
		{
			ifstream vvod("C:\\Users\\Анна Рудницкая\\source\\repos\\3sem_aisd_lab3\\input.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Moscow";
			string city_End = "Khabarovsk";
			InputInFile(list_fly, vvod);
			AdjList* adj = new AdjList(list_fly);
			string cur = "Route:\nMoscow ->Saint-Peterburg ->Khabarovsk \nThe best route for the price:34\n";
			Assert::AreEqual(adj->DAlgoritm(city_Start, city_End), cur);
		}
	};
}