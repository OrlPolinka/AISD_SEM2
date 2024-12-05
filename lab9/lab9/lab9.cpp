#include <iostream> 
#include <algorithm> 
#include <limits.h> 
#include <ctime>   
#include <cstdlib> 
#include <unordered_set> 

using namespace std;

#define G 8 
#define START 0 

int children = 0;
int popSize = 0;
int evoCycles = 0;
float mutationRate = 0.0;

int distances[G][G] =
{
    {INT_MAX, 17, 28, 42, 9, 11, 34, 16 },
    {2, INT_MAX, 11, 30, 30, 15, 31, 4},
    {45, 6, INT_MAX, 32, 10, 8, 46, 52},
    {44, 13, 38, INT_MAX, 17, 36, 3, 12},
    {1, 65, 8, 21, INT_MAX, 22, 28, 16},
    {10, 49, 13, 7, 34, INT_MAX, 10, 54},
    {4, 61, 25, 7, 8, 15, INT_MAX, 7},
    {23, 5, 28, 47, 18, 11, 3, INT_MAX}
};

struct Person
{
    string genes; // Геном особи (маршрут), представлен в виде строки
    int fitness;  // Приспособленность особи (общая длина маршрута)
};

int randomNum(int start, int end)
{
    return start + rand() % (end - start); 
}

bool hasDuplicate(const string& s, char ch) 
{
    return s.find(ch) != string::npos; // Возвращает true, если символ найден в строке
}

string mutateGenes(const string& genome, float mutationRate)
{
    string mutatedGenome = genome; 

    if ((float)rand() / RAND_MAX < mutationRate) {
        while (true)
        {
            int r = randomNum(1, G);
            int r1 = randomNum(1, G);

            if (r1 != r)
            {
                swap(mutatedGenome[r], mutatedGenome[r1]);
                break;
            }
        }

    }
    
    return mutatedGenome; 
}

string createGenome() 
{
    string genome = "0"; 

    while (genome.size() < G)
    {
        int temp = randomNum(1, G); 
        if (!hasDuplicate(genome, (char)(temp + 48)))
            genome += (char)(temp + 48);
    }

    return genome + genome[0]; 
}

int calculateFitness(const string& genome) 
{
    int totalDistance = 0;

    for (int i = 0; i < genome.size() - 1; i++) 
    {
        int from = genome[i] - 48; 
        int to = genome[i + 1] - 48; 

        if (distances[from][to] == INT_MAX) 
            return INT_MAX; 

        totalDistance += distances[from][to]; 
    }

    return totalDistance; 
}

int coolDown(int temp) 
{
    return ((95 * temp) / 100); 
}

bool isLessFit(const Person& p1, const Person& p2) 
{
    return p1.fitness < p2.fitness; 
}

string crossover(const string& parent1, const string& parent2)
{
    string child(G + 1, '0'); 
    int start = randomNum(1, G / 2); 
    int end = randomNum(G / 2, G - 1); 

    for (int i = start; i <= end; i++) 
    {
        child[i] = parent1[i]; 
    }

    int childIndex = 1; // Индекс для заполнения оставшихся генов в ребенке
    for (int i = 1; i < G; i++) 
    {
        if (child.find(parent2[i]) == string::npos) // Если ген из второго родителя отсутствует в ребенке
        {
            while (child[childIndex] != '0') // Ищем следующую свободную позицию в ребенке
                childIndex++;
            child[childIndex] = parent2[i]; 
        }
    }

    child[G] = child[0]; 
    return child; 
}

bool isUniqueGenome(const string& genome, unordered_set<string>& existingGenomes)
{
    if (existingGenomes.find(genome) != existingGenomes.end()) // Если геном уже существует
        return false; 
    existingGenomes.insert(genome); 
    return true; 
}

void solveTSP(int distances[G][G]) 
{
    int generation = 1; // Счетчик поколений
    int genThreshold = evoCycles; // Максимальное количество поколений

    Person population[1000]; // Массив для хранения особей популяции
    Person tempPerson; // Временная переменная для особи
    unordered_set<string> existingGenomes; // Множество для хранения уникальных геномов

    for (int i = 0; i < popSize; i++) 
    {
        do {
            tempPerson.genes = createGenome(); 
        } while (!isUniqueGenome(tempPerson.genes, existingGenomes)); 

        tempPerson.fitness = calculateFitness(tempPerson.genes); 
        population[i] = tempPerson; 
    }

    sort(population, population + popSize, isLessFit);

    cout << "\nНачальная популяция: \n";
    cout << "Геном популяции \t\tВес маршрута\n";
    for (int i = 0; i < popSize; i++)
        cout << population[i].genes << "\t" << population[i].fitness << endl;
    cout << "\n";

    
    int temperature = 100000; 

    cout << "-------------------------------------------------------------" << endl;
    cout << "\nЛучший геном: " << population[0].genes;
    cout << "\tВес маршрута: " << population[0].fitness << "\n\n";

    while (temperature > 100 && generation <= genThreshold) 
    {

        Person newPopulation[1000]; // Массив для хранения новых особей (потомков)

        for (int i = 0; i < children; i++) 
        {
            int parent1Idx = randomNum(0, popSize / 2); 
            int parent2Idx = randomNum(1, popSize); 

            Person parent1 = population[parent1Idx];
            Person parent2 = population[parent2Idx]; 

            string newGenome;
            do {
                newGenome = crossover(parent1.genes, parent2.genes); 
                newGenome = mutateGenes(newGenome, mutationRate); 
            } while (!isUniqueGenome(newGenome, existingGenomes)); 

            Person newPerson;
            newPerson.genes = newGenome; 
            newPerson.fitness = calculateFitness(newPerson.genes); 
            newPopulation[i] = newPerson; 
        }

        temperature = coolDown(temperature); // Снижаем температуру

        for (int i = 0; i < children; i++) 
        {
            population[i + popSize] = newPopulation[i]; 
        }

        sort(population, population + popSize + children, isLessFit); 

        cout << "Текущее поколение: " << generation << "\n"; 
        cout << "Геном популяции \t Вес маршрута\n";
        for (int i = 0; i < popSize; i++)
            cout << population[i].genes << "\t\t    " << population[i].fitness << endl;

        cout << "-------------------------------------------------------------" << endl;
        cout << "\nЛучший геном: " << population[0].genes;
        cout << "\tВес маршрута: " << population[0].fitness << "\n\n";

        generation++; 
    }
}

int main()
{
    srand(time(0)); // Инициализируем генератор случайных чисел текущим временем
    setlocale(LC_ALL, "ru"); 
    cout << "Введите начальный размер популяции (количество маршрутов): ";
    cin >> popSize;
    cout << "Введите количество потомков (количество новых особей в поколении): ";
    cin >> children; 
    cout << "Введите количество эволюций (количество поколений): ";
    cin >> evoCycles; 
    cout << "Введите показатель мутации (в виде десятичной дроби): ";
    cin >> mutationRate;

    solveTSP(distances); 

    return 0; 
}
