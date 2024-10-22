#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;

int graph[8][8] = {
	{0, 2, INT_MAX, 8, 2, INT_MAX, INT_MAX, INT_MAX},
	{2, 0, 3, 10, 5, INT_MAX, INT_MAX, INT_MAX},
	{INT_MAX, 3, 0, INT_MAX, 12, INT_MAX, INT_MAX, 7},
	{8, 10, INT_MAX, 0, 14, 3, 1, INT_MAX},
	{2, 5, 12, 14, 0, 11, 4, 8},
	{INT_MAX, INT_MAX, INT_MAX, 3, 11, 0, 6, INT_MAX},
	{INT_MAX, INT_MAX, INT_MAX, 1, 4, 6, 0, 9},
	{INT_MAX, INT_MAX, 7, INT_MAX, 8, INT_MAX, 9, 0}
};

void algPrima(int start) {
	int arr[7];
	int current = 0;
	vector<bool> visited(8, false);
	vector<pair<int, int>> edg;
	int weight = 0;
	
	auto start1 = chrono::steady_clock::now();

	visited[start] = true;
	while (current < 7) {

		int x = -1, y = -1;
		int min = INT_MAX;

		for (int i = 0; i < 8; i++) {
			if (visited[i]) {
				for (int j = 0; j < 8; j++) {
					if (!visited[j]) {
						if (graph[i][j] < min && graph != 0) {
							min = graph[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}

		if (x != -1 && y != -1) {
			visited[y] = true;

			edg.push_back({ x, y });
			arr[current] = min;
			weight += min;

			//cout << "Текущий вес графа: " << weight << endl;
		}
		current++;
	}

	for (int i = 0; i < edg.size(); i++) {
		cout << "(" << edg[i].first + 1 << ", " << edg[i].second + 1 << ")     Вес ребра: " << arr[i] << endl;
	}
	cout << "\nВес остовного дерева: " << weight << endl;

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start1).count();
	cout << "Алгоритм Прима выполнен за " << duration << " микросекунд" << endl;

	cout << "О-большое: " << pow(8, 2) << endl;
	int V = 8;
	int E = 16;
	int y = E - V + 1;
	cout << "Цикломатическое число: " << y << endl;
}

void algKraskala() {
	int current = 0;
	int arr[7];
	vector<bool> visited(8, false);
	vector<pair<int, int>> edg;
	int weight = 0;

	auto start1 = chrono::steady_clock::now();

	visited[0] = true;

	while (current < 7) {
		int min = INT_MAX;
		int x = -1, y = -1;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!visited[j] && graph[i][j] != 0 && graph[i][j] != INT_MAX) {
					if (graph[i][j] < min) {
						min = graph[i][j];
						x = i;
						y = j;
					}
				}
			}
		}
		if (x != -1 && y != -1) {
			
			visited[y] = true;
			visited[x] = true;
			edg.push_back({ x, y });
			arr[current] = min;
			weight += min;
			
		}
		current++;
	}

	for (int i = 0; i < edg.size(); i++) {
		cout << "(" << edg[i].first + 1 << ", " << edg[i].second + 1 << ")     Вес ребра: " << arr[i] << endl;
	}
	cout << "\nВес остовного дерева: " << weight << endl;

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(end - start1).count();
	cout << "Алгоритм Краскала выполнен за " << duration << " микросекунд" << endl;

	cout << "О-большое: " << current * log(current) << endl;
	int V = 8;
	int E = 16;
	int y = E - V + 1;
	cout << "Цикломатическое число: " << y << endl;
}

int main() {
	setlocale(LC_ALL, "ru");
	int start;
	cout << "Введите стартовую вершину: ";
	cin >> start;
	while (start > 8 || start < 1) {
		cout << "Ошибка! Неверный ввод! Повторите попытку: ";
		cin >> start;
	}
	cout << "\nАлгоритм Прима\nСписок ребер:" << endl;
	algPrima(start - 1);
	cout << "\n\nАлгоритм Краскала\nСписок ребер:" << endl;
	algKraskala();

	return 0;
}