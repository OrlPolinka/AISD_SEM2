#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <array>
//#include <chrono>
using namespace std;

queue <int> q;
stack <int> st;
vector<int> adj[10];
vector<pair<int, int>> edg;

bool graph[10][10] = {
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
	{0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

void printGraph() {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

void adjList(){
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (graph[i][j]) {
				adj[i].push_back(j);
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		cout << i + 1 << ": ";
		for (int j = 0; j < adj[i].size(); j++) {
			cout << adj[i][j] + 1 << " ";
		}
		cout << endl;
	}
}

void edgList() {
	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (graph[i][j]) {
				edg.push_back({ i, j });
			}
		}
	}


	for (int i = 0; i < edg.size(); i++) {
		cout << "(" << edg[i].first + 1 << ", " << edg[i].second + 1 << ")" << endl;
	}
}

void bfs(int start) {
	bool visited[10];
	//auto start1 = chrono::steady_clock::now();
	
	for (int i = 0; i < 10; i++) visited[i] = false;
	
	q.push(start);
	visited[start] = true;

	while (!q.empty()) {
		int a = q.front();
		cout << a + 1 << ", ";
		q.pop();

		for (int i = 0; i < 10; i++) {
			if (!visited[i] && graph[a][i]) {
				q.push(i);
				visited[i] = true;
			}
		}
	}
	//auto end = chrono::steady_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end - start1).count();
	//cout << "BFS выполнена за " << duration << " микросекунд" << endl;
}

void dfs(int start) {
	bool visited[10];
	//auto start1 = chrono::steady_clock::now();

	for (int i = 0; i < 10; i++) visited[i] = false;

	st.push(start);
	visited[start] = true;

	while (!st.empty()) {
		int a = st.top();
		cout << a + 1 << ", ";
		st.pop();

		for (int i = 0; i < 10; i++) {
			if (!visited[i] && graph[a][i]) {
				st.push(i);
				visited[i] = true;
			}
		}
	}
	//auto end = chrono::steady_clock::now();
	//auto duration = chrono::duration_cast<chrono::microseconds>(end - start1).count();
	//cout << "DFS выполнена за " << duration << " микросекунд" << endl;
}

int main() {
	setlocale(LC_ALL, "ru");
	cout << "Поиск в ширину:" << endl;
	bfs(0);

	cout << "\n\nПоиск в глубину:" << endl;
	dfs(0);

	cout << "\n\nМатрица смежности:" << endl;
	printGraph();

	cout << "\n\nСписок смежности:" << endl;
	adjList();

	cout << "\n\nСписок ребер:" << endl;
	edgList();

	int v = 10;;
	int e = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (graph[i][j]) {
				e++;
			}
		}
	}
	cout << "\nДля списка смежности O(|V| + |E|): " << e + v << endl;
	cout << "Для списка смежности O(|V|^2): " << v * v << endl;

	return 0;
}