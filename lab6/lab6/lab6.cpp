#include <iostream>
#include <map>
//#include <unordered_map>
#include <string>
#include <Windows.h>
#include <queue>
using namespace std;

int global_id = 0;

struct Node {
    char ch;
    int mp;
    int id;
    Node* left, *right;
};

Node* GetNode(char ch, int mp, Node* left, Node* right) {
    Node* node = new Node();
    node->ch = ch;
    node->mp = mp;
    node->id = global_id++;
    node->left = left;
    node->right = right;
    return node;
}

//для сравнения узлов в очереди, чтоб выстроить их в определенном приоритете
struct priority {
    bool operator()(Node* l, Node* r) {
        if (l->mp == r->mp) {
            return l->id > r->id;
        }
        return l->mp > r->mp;
    }
};

void encode(Node* root, string str, map<char, string>& code) {
    if (root == NULL)
        return;

    if (!root->left && !root->right)
        code[root->ch] = str;

    encode(root->left, str + "1", code);
    encode(root->right, str + "0", code);
}

void decode(Node* root, int& index, string str) {
    if (root == NULL)
        return;

    if (!root->left && !root->right){
        if (root->ch >= 'А' && root->ch <= 'Я' || root->ch >= 'A' && root->ch <= 'Z')
            cout << " " << root->ch;
        else
            cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0') 
        decode(root->right, index, str);
    else
        decode(root->left, index, str);

}




void algHafmana(string text) {

    SetConsoleOutputCP(1251);

    map<char, int> mp;  //для хранения частоты для каждого символа

    for (char ch : text) {
        mp[ch]++;
    }

    priority_queue<Node*, vector <Node*>, priority> q;  //приоритетная очередь

    for (auto k : mp) {
        q.push(GetNode(k.first, k.second, NULL, NULL));
    }

    cout << "Частота символов:" << endl;
    for (auto k : mp) {
        cout << k.first << " : " << k.second << endl;
    }

    while (q.size() != 1) {
        Node* left = q.top();
        q.pop();

        Node* right = q.top();
        q.pop();

        int sum = left->mp + right->mp;
        q.push(GetNode('\0', sum, left, right));
    }

    Node* root = q.top(); //корень дерева

    map<char, string> code; //для хранения кодов символов

    encode(root, "", code);
    cout << "Коды символов:" << endl;
    cout << "Символ:   " << "Код:" << endl;
    for (auto k : code) {
        cout << k.first << " : " << k.second << endl;
    }

    string str;
    for (char ch : text) {
        str += code[ch];
        //str += " ";
    }

    cout << "Закодированная строка: " << str << endl;

    int index = -1;

    cout << "Декодированная строка: " << endl;
    while (index < (int)str.size() - 2) {
        decode(root, index, str);
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string text;
    cout << "Введите текст: ";
    getline(cin, text);

    string filteredText;
    for (char ch : text) {
        if (ch != ' ') {
            filteredText += ch;
        }

    }

    algHafmana(filteredText);

    return 0;
}