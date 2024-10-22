#include <iostream>
using namespace std;

int V = 6;

int D[6][6] = {
	{0, 28, 21, 59, 12, 27},
	{7, 0, 24, -1, 21, 9},
	{9, 32, 0, 13, 11, -1},
	{8, -1, 5, 0, 16, -1},
	{14, 13, 15, 10, 0, 22},
	{15, 18, -1, -1, 6, 0}
	};

	int S[6][6] = {
	{0, 2, 3, 4, 5, 6},
	{1, 0, 3, 4, 5, 6},
	{1, 2, 0, 4, 5, 6},
	{1, 2, 3, 0, 5, 6},
	{1, 2, 3, 4, 0, 6},
	{1, 2, 3, 4, 5, 0}
	};

	void path(int start, int end) {
		if (start == end) {
			cout << (start + 1);
		}
		else if (S[start][end] == (end + 1)) {
			cout << (start + 1) << " -> " << (end + 1);
		}
		else {
			path(start, S[start][end] - 1);
			cout << " -> " << (end + 1);
		}
	}

	void printAllPath() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (i != j && D[i][j] != -1) {
					cout << "Путь из вершины " << i + 1 << " в вершину " << j + 1 << " : ";
					path(i, j);
					cout << " | Расстояние: " << D[i][j] << endl;
				}
				else if (i != j && D[i][j] == -1) {
					cout << "Путь из вершины " << i + 1 << " в вершину " << j + 1 << " : пути нет." << endl;

				}
			}
			cout << endl;
		}
	}

int main()
{
    setlocale(LC_ALL, "ru");
	
	cout << "Исходная матрица D:" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << D[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\nИсходная матрица S:" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << S[i][j] << " ";
		}
		cout << endl;
	}

	for (int m = 0; m < 6; m++) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				if (D[i][m] != -1 && D[m][j] != -1) {
					if (D[i][m] + D[m][j] < D[i][j] || D[i][j] == -1) {
						D[i][j] = D[i][m] + D[m][j];
						S[i][j] = S[i][m];
						}
					}
				}
		}
	}
	
	cout << "\nИзмененная матрица D:" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << D[i][j] << " ";
		}
		cout << endl;
	}

	cout << "\nИзмененная матрица S:" << endl;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			cout << S[i][j] << " ";
		}
		cout << endl;
	}

	int start, end;

	cout << "\nВведите начальный узел: ";
	cin >> start;
	while (start < 1 || start > 6) {
		cout << "Неправильный ввод. Попробуйте еще раз. Введите число от 1 до 6: ";
		cin >> start;
	}

	cout << "\nВведите конечный узел: ";
	cin >> end;
	while (end < 1 || end > 6) {
		cout << "Неправильный ввод. Попробуйте еще раз. Введите число от 1 до 6: ";
		cin >> end;
	}

	cout << "\nКратчайшее расстояние из вершины " << start << " в вершину " << end << " : " << D[start - 1][end - 1] << endl;
	cout << "Кратчайший путь из вершины " << start << " в вершину " << end << " : ";
	path(start - 1, end - 1);
	
	cout << "\nВывод всех путей: " << endl;
	printAllPath();

	cout << "O(V^3) : " << pow(V, 3) << " операций." << endl;
    
    return 0;
}