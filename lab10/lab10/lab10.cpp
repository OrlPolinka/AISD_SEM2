#include <iostream>;
#include <vector>
#include <random>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX_DIST 100	// макс расстояние

typedef vector<vector<double>> Matrix;	// двумерный массив - матрица для расстояний и феромонов
typedef vector<int> Path;	// путь

void matrixOnDisplay(Matrix matrix, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

// Начальная инициализация феромонов
Matrix initializePheromones(int N, double initialPheromone) {
	return Matrix(N, vector<double>(N, initialPheromone));
}

// Вычисление следующего перехода
int chooseNextCity(int currentCity, const vector<bool>& visited, const Matrix& cities, const Matrix& pheromones, double alpha, double beta) {
	vector<double> probabilities(cities.size(), 0);	// вероятность перехода в другой город(по формуле)
	double total = 0;

	for (int i = 0; i < cities.size(); i++) {
		if (!visited[i]) {
			double pheromone = pow(pheromones[currentCity][i], alpha);
			double visibility = pow(1.0 / cities[currentCity][i], beta);
			probabilities[i] = pheromone * visibility;
			total += probabilities[i];
		}
	}

	// Нормализация вероятностей
	for (int i = 0; i < probabilities.size(); i++) {
		probabilities[i] /= total;
	}

	// Выбор следующего города с учетом вероятностей
	double random = (double)rand() / RAND_MAX;	// случ число от 0 до 1
	double cumulative = 0;

	for (int i = 0; i < probabilities.size(); i++) {
		cumulative += probabilities[i];
		if (random <= cumulative) {
			return i;
		}
	}

	return -1; // На случай ошибки
}

// Вычисление длины пути
double calculatePathLength(const Path& path, const Matrix& cities) {
	double length = 0;
	for (int i = 0; i < path.size() - 1; i++) {
		length += cities[path[i]][path[i + 1]];
	}
	length += cities[path.back()][path[0]]; // Возврат в начальный город
	return length;
}

// Обновление феромонов
void updatePheromones(Matrix& pheromones, const vector<Path>& paths, const vector<double>& lengths, double evaporationRate, double Q) {
	// испарение феромонов: уменьшение значений на всех ребрах
	for (int i = 0; i < pheromones.size(); i++) {
		for (int j = 0; j < pheromones.size(); j++) {
			pheromones[i][j] *= (1 - evaporationRate);	// умножаем на коэффициент испарения
		}
	}
	// добавление новых феромонов на основе пройденных маршрутов
	for (int k = 0; k < paths.size(); k++) {
		const Path& path = paths[k];
		double contribution = Q / lengths[k];
		for (int i = 0; i < path.size() - 1; i++) {
			pheromones[path[i]][path[i + 1]] += contribution;
			pheromones[path[i + 1]][path[i]] += contribution;
		}
		pheromones[path.back()][path[0]] += contribution;
		pheromones[path[0]][path.back()] += contribution;
	}
}

int main() {
	setlocale(LC_ALL, "ru");

	int N;
	cout << "Введите количество городов N = ";
	cin >> N;
	while (N < 2) {
		cout << "Неправильный ввод. Необходимо наличие хотя бы 2 городов. Повторите ввод: ";
		cin >> N;
	}

	double initialPheromone, alpha, beta, evaporationRate, Q;
	int iterations, ants;
	cout << "Введите начальное значение феромонов: ";
	cin >> initialPheromone;
	cout << "Введите альфа: ";	// α (вес феромонов): показывает, насколько сильное влияние оказывают феромоны
	cin >> alpha;
	cout << "Введите бета: ";	// β (вес расстояний): показывает, насколько важны расстояния при выборе пути
	cin >> beta;
	cout << "Введите коэффициент испарения феромонов: ";	// контролирует уменьшение феромонов на рёбрах после каждой итерации
	cin >> evaporationRate;
	cout << "Введите параметр Q: ";		// количество феромонов
	cin >> Q;	
	cout << "Введите количество итераций: ";
	cin >> iterations;
	cout << "Введите количество муравьёв: ";
	cin >> ants;

	Matrix cities;
	cities.resize(N);	// задаем количество строк матрицы
	// задаем N столбцов
	for (auto& i : cities) {
		i.resize(N);
	}

	for (int i = 0; i < N; i++) {
		cities[i][i] = 0;
		for (int j = 0; j < N; j++) {
			cities[i][j] = cities[j][i] = rand() % MAX_DIST + 1;
		}
	}
	cout << "Матрица расстояний между городами:" << endl;
	matrixOnDisplay(cities, N);
	
	Matrix pheromones = initializePheromones(N, initialPheromone);

	Path bestPath;
	double bestLength = numeric_limits<double>::max();

	for (int iter = 0; iter < iterations; iter++) {
		vector<Path> paths(ants);	// пути для всех муравьев
		vector<double> lengths(ants, 0);	// длины этих путей

		for (int k = 0; k < ants; k++) {
			vector<bool> visited(N, false);		// посещенные города
			Path path;
			int currentCity = rand() % N;	// случ нач город
			visited[currentCity] = true;
			path.push_back(currentCity);

			// строим путь муравья
			while (path.size() < N) {
				int nextCity = chooseNextCity(currentCity, visited, cities, pheromones, alpha, beta);
				path.push_back(nextCity);
				visited[nextCity] = true;
				currentCity = nextCity;
			}

			lengths[k] = calculatePathLength(path, cities);
			paths[k] = path;

			if (lengths[k] < bestLength) {
				bestLength = lengths[k];
				bestPath = path;
			}


			cout << "Муравей " << k << " : " << endl;
			cout << "Маршрут: ";
			for (int city : bestPath) {
				cout << city << " ";
			}
			cout << "Длина маршрута: " << lengths[k] << endl;

		}

		cout << "-------------------------------------------------------------" << endl;
		updatePheromones(pheromones, paths, lengths, evaporationRate, Q);

		cout << "Итерация " << iter + 1 << ":" << endl;
		cout << "Лучший маршрут: ";
		for (int city : bestPath) {
			cout << city << " ";
		}
		cout << endl;
		cout << "Длина маршрута: " << bestLength << endl;
	}


	return 0;
}