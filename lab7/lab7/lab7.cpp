#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	int n;
	cout << "Введите кол-во элементов: ";
	cin >> n;
	while (n <= 0) {
		cout << "Неверный ввод. Повторите попытку: ";
		cin >> n;
	}

	int sequence[100];

	cout << "Введите последовательность: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> sequence[i];
	}

	int dp[100];
	int previous[100];


	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		previous[i] = -1;
	}

	int maxLength = 1, lastIndex = 0;


	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (sequence[i] > sequence[j] && dp[i] < dp[j] + 1) { 
				dp[i] = dp[j] + 1;
				previous[i] = j;
			}
			if (sequence[i] > sequence[j] && dp[i] == dp[j] + 1) {
				
				previous[i] = j;
			}
			
		}

		if (dp[i] > maxLength) {
			maxLength = dp[i];
			lastIndex = i;
		}
	}

	
	/*for (int i = 0; i < n; i++) {
		if (dp[i] == maxLength && sequence[i] < sequence[lastIndex]) {
			lastIndex = i;
			
		}
	}*/

	
	cout << "Максимальная длина: " << maxLength << endl;


	int lis[100];
	int k = 0;
	while (lastIndex != -1) {
		lis[k++] = sequence[lastIndex];
		lastIndex = previous[lastIndex];

	}

	cout << "Последовательность: " << endl;
	for (int i = k - 1; i >= 0; i--) {
		cout << lis[i] << (i > 0 ? ", " : "\n");
	}


	return 0;
}