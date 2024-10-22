#include <iostream>
#include <chrono>
using namespace std;

int Khanoyskaya_bashnya(int N, int i, int k, int help) {
    if (N == 1) {
        cout << "\nПереместим диск " << N << " с стержня " << i << " на стержень " << k << endl;
        return 1;
    }
    int step = 0;
    step += Khanoyskaya_bashnya(N - 1, i, help, k);
    cout << "\nПереместим диск " << N << " с стержня " << i << " на стержень " << k << endl;
    step += 1;
    step += Khanoyskaya_bashnya(N - 1, help, k, i);

    return step;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int N, k, i, help, Steps;
    
    cout << "Введите количество дисков N: ";
    cin >> N;
    while (N < 1) {
        cout << "Необходимо наличие минимум одного диска! Повторите попытку: ";
        cin >> N;
    }
    
    cout << "Введите конечный стержень k: ";
    cin >> k;
    while (k < 1) {
        cout << "Некорректный ввод! Повторите попытку: ";
        cin >> k;
    }

    cout << "Введите начальныцй стержень i: ";
    cin >> i;
    while (i < 1 || i == k) {
        cout << "Неверный ввод! Повторите попытку: ";
        cin >> i;
    }

    if (i != 2 && k != 2) {
        help = 2;
        cout << "Вспомогательный стержень: " << help << endl;
    }
    else if (i != 1 && k != 1) {
        help = 1;
        cout << "Вспомогательный стержень: " << help << endl;
    }
    else {
        help = 3;
        cout << "Вспомогательный стержень: " << help << endl;
    }
    
    auto start = chrono::high_resolution_clock::now();

    Steps = Khanoyskaya_bashnya(N, i, k, help);
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "\nХанойская башня собрана за " << duration.count() << " милисекунд" << endl;
    cout << "\nХанойская башня собрана за " << Steps << " шагов" << endl;

    return 0;
}