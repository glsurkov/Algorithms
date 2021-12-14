#include <iostream>
#include <vector>
#include <list>
#include <random>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

// ���� �������� ������
struct node {
    vector<int> arr;
    struct node* nxt[10];
};

// �������, ��������� ����� ���� �������� ������
struct node* new_node(void)
{
    struct node* tempNode = new node;

    for (int i = 0; i < 10; i++) {
        tempNode->nxt[i] = NULL;
    }

    return tempNode;
}
//������� ����������� ������ ������,
//��������� MSD-����������� ����������
void msd_sort(struct node* root, int exp,
              vector<int>& sorted_arr)
{
    if (exp <= 0) {
        return;
    }

    int j;

    //������������ ����� � ������ �������,
    //��������� �� �� ������� ������
    for (int i = 0;
         i < root->arr.size();
         i++) {

        // �������� ������� ������
        j = (root->arr[i] / exp) % 10;

        //���� j-�� ������ � ������� ����� ������,
        //�� ������� ����� ��� j-�� �������
        if (root->nxt[j] == NULL) {
            root->nxt[j] = new_node();
        }

        //�������� ����� � j-�� ����
        root->nxt[j]->arr.push_back(
                root->arr[i]);
    }
    //����� �������� ��������� ��� ����
    //�������� �����, ������� ������ ����� ������ �����
    for (int i = 0; i < 10; i++) {

        //��������� ������ ���� ��� ���
        if (root->nxt[i] != NULL) {

            //��������� ������� ����� � ����
            if (root->nxt[i]->arr.size()
                > 1) {

                // ���������� ���������
                msd_sort(root->nxt[i],
                         exp / 10,
                         sorted_arr);
            }
                //���� � �����-�� ���� ������� ������ ���� �����,
                //�� ��� ����� ��������, ��� ����� �������������
            else {
                sorted_arr.push_back(
                        root->nxt[i]->arr[0]);
            }
        }
    }
}


//�������, ������������ ������� ������
//����������� ����� � �������
int get_max_exp(vector<int> arr)
{
    int mx = arr[0];

//����������� ������������� ����� � �������
    for (int i = 1; i < arr.size(); i++) {

        if (arr[i] > mx) {
            mx = arr[i];
        }
    }

    int exp = 1;

//����������� �������� ������� � ����������� �����
    while (mx > 10) {
        mx /= 10;
        exp *= 10;
    }

    return exp;
}


//������� ������������ ������� ������
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

//������� ��������� ��������� � �������
void print(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";

    cout << endl;
}


int main()
{
    srand(time(NULL));
    //������� �������� ����
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
            //��������� ����������������� ������ � �������� ����
            root->arr.insert(root->arr.end(), random.begin(), random.end());
            cout << "Unsorted array : ";
            print(root->arr);
            // ���������� ������� ������ ����������� ��������,
            //������� ��������������� �������
            int exp = get_max_exp(root->arr);
            vector<int> sorted_arr;
            // �������� ������� ����������
            msd_sort(root, exp, sorted_arr);
            cout << "Sorted array : ";
            print(sorted_arr);
            //����� ���������� ���������
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
