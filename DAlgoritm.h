#pragma once
#include<string>
#include "list.h"
#include "map.h"

class AdjList {
	class Vertex {
	public:
		Vertex(int index_City = 0, double price = 0) :index_City(index_City), price(price) {}
		int index_City;
		double price;
	};
private:
	List<Vertex>* graph;
	Map<string, int>* map_City_name_to_index;
	Map<int, string>* map_index_to_name_City;
	int size;
	const int INF = INT_MAX;
public:
	AdjList(List<string>* data) {
		graph = new List<Vertex>();
		map_index_to_name_City = new Map<int, string>();
		map_City_name_to_index = new Map<string, int>();
		int N = data->get_size();
		int index_city = 0;
		for (int i = 0; i < N; i++) {
			string CurString = data->at(i);
			int cur = CurString.find(';');
			int cur1 = CurString.find(';', cur + 1);
			string str_name_city1 = CurString.substr(0, cur);//get the first city
			string str_name_city2 = CurString.substr(cur + 1, cur1 - cur - 1);//get the second city
			str_name_city2.erase(0, 1);//deleting the space 
			if (!map_City_name_to_index->is_in_map(str_name_city1)) {
				map_City_name_to_index->insert(str_name_city1, index_city);
				map_index_to_name_City->insert(index_city, str_name_city1);
				index_city++;
			}
			if (!map_City_name_to_index->is_in_map(str_name_city2)) {
				map_City_name_to_index->insert(str_name_city2, index_city);
				map_index_to_name_City->insert(index_city, str_name_city2);
				index_city++;
			}
		}
		size = index_city;
		graph = new List<Vertex>[size];
		//fill in the list of prices(adjacencies)
		for (int i = 0; i < N; i++) {
			int price_1_to_2 = INF;
			int price_2_to_1 = INF;
			string CurString = data->at(i);
			int cur = CurString.find(';');//first entry ;
			int cur1 = CurString.find(';', cur + 1);//second entry ;
			int cur2 = CurString.find(';', cur1 + 1);//third entry ;
			int cur3 = CurString.find(';', cur2 + 1);//fourth entry ;
			string str_name_city1 = CurString.substr(0, cur);// get the first city
			string str_name_city2 = CurString.substr(cur + 1, cur1 - cur - 1);//get the second city
			str_name_city2.erase(0, 1);// delete the space

			if (CurString.substr(cur1 + 2, cur2 - 2 - cur1) != "N/A")
				price_1_to_2 = stof(CurString.substr(cur1 + 2, cur2 - 2 - cur1));
			if (CurString.substr(cur2 + 2, cur3 - 1) != "N/A")
				price_2_to_1 = stoi(CurString.substr(cur2 + 2, cur3 - 2 - cur2));
			if (price_1_to_2 != INF) {
				Vertex v1(map_City_name_to_index->find(str_name_city2), price_1_to_2);//temporary vertex to add
				graph[map_City_name_to_index->find(str_name_city1)].push_back(v1);
			}
			if (price_2_to_1 != INF) {
				Vertex v2(map_City_name_to_index->find(str_name_city1), price_2_to_1);//temporary vertex to add
				graph[map_City_name_to_index->find(str_name_city2)].push_back(v2);
			}
		}
	}
	string DAlgoritm(string city_Start, string city_End) {
		if (city_Start != city_End) {
			string answer;
			while (!map_City_name_to_index->is_in_map(city_Start)) {
				cout << "The departure city is missing, enter it again" << endl;
				cin >> city_Start;
			}
			while (!map_City_name_to_index->is_in_map(city_End)) {
				cout << "The arrival city is missing, enter it again" << endl;
				cin >> city_End;
			}
			int index_city = 0;
			int index_start_vertex = map_City_name_to_index->find(city_Start); //find the index of the city of departure
			bool* visited = new bool[size];
			int* distance = new int[size];  //distances from the starting vertex
			for (int i = 0; i < size; i++) {
				distance[i] = INF;
				visited[i] = false;
			}
			distance[index_start_vertex] = 0;
			int* path = new int[size];

			for (int i = 0; i < size; ++i) {
				int vertex = -1;
				for (int j = 0; j < size; ++j)
					if (!visited[j] && (vertex == -1 || distance[j] < distance[vertex]))
						vertex = j;
				if (distance[vertex] == INF)
					break;
				visited[vertex] = true;
				for (size_t j = 0; j < graph[vertex].get_size(); ++j) {
					int to = graph[vertex].at(j).index_City,
						len = graph[vertex].at(j).price;
					if (distance[vertex] + len < distance[to]) {
						distance[to] = distance[vertex] + len;
						path[to] = vertex;
					}
				}
			}
			int End_index = map_City_name_to_index->find(city_End);  //search for the arrival city index
			int Start_index = map_City_name_to_index->find(city_Start);
			if (distance[End_index] != INF) {
				List<int>* path_cur = new List<int>();
				for (int v = End_index; v != Start_index; v = path[v])
					path_cur->push_back(v);
				path_cur->push_back(Start_index);
				path_cur->reverse();
				answer += "Route:\n";
				string cur;
				for (int i = 0; i < path_cur->get_size(); i++) {
					cur += "->";
					cur += map_index_to_name_City->find(path_cur->at(i)) + ' ';
				}
				cur.erase(0, 2);
				answer += cur + "\nThe best route for the price:" + to_string(distance[End_index]) + '\n';
			}
			else {
				answer = "This route can't be built";
			}
			return answer;
		}
		else throw exception("End city can't be equal to start city");
	}
};