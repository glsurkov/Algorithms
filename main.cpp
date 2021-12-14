#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

// Узел связного списка
struct node {
    vector<int> arr;
    struct node* nxt[10];
};

// Функция, создающая новый узел связного списка
struct node* new_node(void)
{
    struct node* tempNode = new node;

    for (int i = 0; i < 10; i++) {
        tempNode->nxt[i] = NULL;
    }

    return tempNode;
}
//Функция сортирующая данный массив,
//используя MSD-поразрядную сортировку
void msd_sort(struct node* root, int exp,
              vector<int>& sorted_arr)
{
    if (exp <= 0) {
        return;
    }

    int j;

    //Распределяем числа в разные корзины,
    //полагаясь на их старший разряд
    for (int i = 0;
         i < root->arr.size();
         i++) {

        // Получаем старший разряд
        j = (root->arr[i] / exp) % 10;

        //Если j-ый индекс в массиве узлов пустой,
        //то создаем новый для j-го индекса
        if (root->nxt[j] == NULL) {
            root->nxt[j] = new_node();
        }

        //Сохрянем число в j-ый узел
        root->nxt[j]->arr.push_back(
                root->arr[i]);
    }
    //Снова проводим сортровку для всех
    //дочерних узлов, которые хранят более одного числа
    for (int i = 0; i < 10; i++) {

        //Проверяем пустой узел или нет
        if (root->nxt[i] != NULL) {

            //Проверяем сколько чисел в узле
            if (root->nxt[i]->arr.size()
                > 1) {

                // Рекурсивно сортируем
                msd_sort(root->nxt[i],
                         exp / 10,
                         sorted_arr);
            }
                //Если в каком-то узле имеется только одно число,
                //то это будет означать, что число отсортировано
            else {
                sorted_arr.push_back(
                        root->nxt[i]->arr[0]);
            }
        }
    }
}


//Функция, определяющая старший разряд
//наибольшего числа в массиве
int get_max_exp(vector<int> arr)
{
    int mx = arr[0];

//Определение максимального числа в массиве
    for (int i = 1; i < arr.size(); i++) {

        if (arr[i] > mx) {
            mx = arr[i];
        }
    }

    int exp = 1;

//Определение страшего разряда у наибольшего числа
    while (mx > 10) {
        mx /= 10;
        exp *= 10;
    }

    return exp;
}


//Функция генерирующая входные данные
list<int> randomList(int n)
{
    list<int> rList;
    for(int i = 0; i < n; i++) {
        rList.push_back(round(rand() % 1000 + 0));
    }

    for (auto v : rList)
        cout << v << " ";
    cout << endl;
    return rList;
}

//Функция выводящая результат в консоль
void print(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";

    cout << endl;
}


int main()
{
    srand(time(NULL));
    //Создаем корневой узел
    int n = 10;
    float result = 0;
    float relation = 0;
    int time;
    ofstream out("Result5.txt");
    clock_t start_time,end_time;
    while (n <= 1000) {
        for(int i = 0; i < 10; i++) {
            start_time = clock();
            struct node *root = new_node();
            list<int> random = randomList(n);
            //Сохраняем неотсортированный массив в корневой узел
            root->arr.insert(root->arr.end(), random.begin(), random.end());
            cout << "Unsorted array : ";
            print(root->arr);
            // Определяем старший разряд наибольшего элемента,
            //вызывая соответствующую функцию
            int exp = get_max_exp(root->arr);
            vector<int> sorted_arr;
            // Вызываем функцию сортировки
            msd_sort(root, exp, sorted_arr);
            cout << "Sorted array : ";
            print(sorted_arr);
            //Время выполнения программы
            end_time = clock();
            time = end_time - start_time;
            result = result + time;
        }
        relation = relation + result/(10*n*log10(n));
        out << n << " " << result/10 << endl;
        n = n + 10;
        result = 0;
    }
    out << relation/99;

    return 0;
}
