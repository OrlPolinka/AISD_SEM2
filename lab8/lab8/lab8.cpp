#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;

struct Item
{
    string name;
    int weight;
    int price;
};

void findMaxPrice(int N, int numbOfItem, Item* item) {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int** dp = new int*[numbOfItem + 1];    
    for (int i = 0; i <= numbOfItem; i++) {
        dp[i] = new int[N + 1];
    }

    for (int i = 0; i <= numbOfItem; i++) {
        for (int w = 0; w <= N; w++) {
            if (i == 0 || w == 0) { 
                dp[i][w] = 0;
            }
            else if (item[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w - item[i - 1].weight] + item[i - 1].price, dp[i - 1][w]);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = N;
    cout << "Максимальная стоимость товаров: " << dp[numbOfItem][N] << endl;
    cout << "Предметы, помещенные в рюкзак: " << endl;
    for (int i = numbOfItem; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Название предмета: " << item[i - 1].name << ", вес: " << item[i - 1].weight << ", стоимость: " << item[i - 1].price << endl;
            w -= item[i - 1].weight;
        }
        
    }

    for (int i = 0; i <= numbOfItem; i++) {
        delete[] dp[i];
    }
    delete[] dp;
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N, numberOfItem;
    cout << "Введите максимальную вместимость рюкзака: ";
    cin >> N;
    while (N < 1) {
        cout << "Неправильный ввод. Вместимость рюкзака должна быть больше 0. Повторите попытку: ";
        cin >> N;
    }

    cout << "Введите количество товаров: ";
    cin >> numberOfItem;
    while (numberOfItem < 1)
    {
        cout << "Неправильный ввод. Количество товаров должно быть больше 0. Повторите попытку: ";
        cin >> numberOfItem;
    }

    Item* item = new Item[numberOfItem];
    cout << "Введите товары: " << endl;
    for (int i = 0; i < numberOfItem; i++) {
        cout << "Название товара: ";
        cin >> item[i].name;

        cout << "Вес товара: ";
        cin >> item[i].weight;
        while (item[i].weight < 1) {
            cout << "Неправильный ввод. Вес товара должен быть больше 0. Повторите попытку: ";
            cin >> item[i].weight;
        }

        cout << "Стоимость товара: ";
        cin >> item[i].price;
        while (item[i].price < 1) {
            cout << "Неправильный ввод. Стоимость товара должна быть больше 0. Повторите попытку: ";
            cin >> item[i].price;
        }
    }

    findMaxPrice(N, numberOfItem, item);

    delete[] item;

    return 0;
}