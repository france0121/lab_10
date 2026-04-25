#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>

using namespace std;

// Функция вывода списка
void printList(const list<int>& lst, const string& name) {
    cout << name << ": ";
    for (int x : lst) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    
    int N;
    cout << "Введите количество элементов N: ";
    cin >> N;
    
    // 1. Создаём список и заполняем случайными числами
    list<int> L;
    for (int i = 0; i < N; i++) {
        L.push_back(rand() % 81 - 40); // числа от -40 до 40
    }
    printList(L, "Исходный список");
    
    // 2. Поиск подсписка с максимальной суммой (простой перебор)
    list<int> bestSubList;
    int bestSum = -1000000;
    
    // Перебираем все возможные подсписки
    auto start = L.begin();
    for (auto i = L.begin(); i != L.end(); ++i) {
        int currentSum = 0;
        list<int> currentSubList;
        
        for (auto j = i; j != L.end(); ++j) {
            currentSum += *j;
            currentSubList.push_back(*j);
            
            if (currentSum > bestSum) {
                bestSum = currentSum;
                bestSubList = currentSubList;
            }
        }
    }
    
    // 3. Выводим результат
    cout << "\nПодсписок с максимальной суммой:\n";
    printList(bestSubList, "Подсписок");
    cout << "Сумма = " << bestSum << endl;
    
    return 0;
}
