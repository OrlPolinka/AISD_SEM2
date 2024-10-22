#include <iostream>
#include <array>
#include <vector>
#include <climits>
using namespace std;

int graph[9][9] = {
	{0, 7, 10, 0, 0, 0, 0, 0, 0},
	{7, 0, 0, 0, 0, 9, 27, 0, 0},
	{10, 0, 0, 0, 31, 8, 0, 0, 0},
	{0, 0, 0, 0, 32, 0, 0, 17, 21},
	{0, 0, 31, 32, 0, 0, 0, 0, 0},
	{0, 9, 8, 0, 0, 0, 0, 11, 0},
	{0, 27, 0, 0, 0, 0, 0, 0, 15},
	{0, 0, 0, 17, 0, 11, 0, 0, 15},
	{0, 0, 0, 21, 0, 0, 15, 15, 0},
};

int main() {
	setlocale(LC_ALL, "ru");
	vector<int> dist(9, INT_MAX);//расстояние до вершин
	vector<bool> visited(9, false);
	int start;
	char startPoint;
	bool flag = false;
	char symbols[9] = { 'A','B','C','D','E','F','G','H','I' };

	while (!flag) {
		cout << "Введите стартовую вершину: ";
		cin >> startPoint;
		for (int i = 0; i < 9; i++) {
			if ( symbols[i] == startPoint ) {
				start = i;
				flag = true;
				break;
			}
		}	
	}
	cout << "\nАлгоритм Дэйкстры:" << endl;
	dist[start] = 0;

	for (int i = 0; i < 9; i++) {
		int min = INT_MAX;//минимальное расстояние
		int minIndex = -1;

		for (int j = 0; j < 9; j++) {
			if (!visited[j] && dist[j] < min) {
				min = dist[j];
				minIndex = j;
			}
		}
		if (minIndex == -1) break;

		visited[minIndex] = true;

		for (int j = 0; j < 9; j++) {
			if (!visited[j] && graph[minIndex][j] != 0 && dist[minIndex] != INT_MAX && dist[minIndex] + graph[minIndex][j] < dist[j]) {
				dist[j] = dist[minIndex] + graph[minIndex][j];
			}
		}
	}

	cout << "Вершина \t Расстояние от стартовой вершины" << endl;
	for (int i = 0; i < 9; i++) {
		cout << symbols[i] << "\t->\t" << (dist[i] == INT_MAX ? -1 : dist[i]) << endl;
	}
	
	return 0;
}