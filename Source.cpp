#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;
enum Specialization
{
    COMPUTER_SCIENCE,
    IT,
    MATH,
    PHYSICS_AND_IT,
    HANDICRAFT,
};
string specializationArr[] = { "��������� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };
struct Student
{
    string surname;
    unsigned course;
    float averageRate;
    Specialization specialization;
    unsigned physicsRate;
    unsigned mathRate;
    unsigned thirdSubject;
    union
    {
        unsigned programmingRate;
        unsigned chMRate;
        unsigned pedagogicRate;
    };
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
int LineSearch(Student* p, const int N);
void Sort(Student* p, const int N);
int BinSearch(Student* p, const int N, const string surname, float averageRate, int thirdSubjectRate);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int main()
{ // ������������ ����������� ��������:
   SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
   SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������
    int N;
    cout << "������ �-�� ��������: ";
    cin >> N;
    Student* p = new Student[N];
    int amount;
    string surname;
    float averageRate;
    int thirdSubjectRate;
    int found;
    int menuItem;
    do
    {
        cout << endl
            << endl
            << endl;
        cout << "������� ��:" << endl
            << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ���� ������� ��������," << endl;
        cout << " ������� ��� ���� ����� �� 4,5" << endl;
        cout << " [4] - ������� ������������� �����" << endl;
        cout << " [5] - ������� ����� �������� �� ������� �� ��������" << endl;
        cout << " [6] - �������� ������������� �� ���� �����"
            << endl
            << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl
            << endl;
        cout << "������ ��������: ";
        cin >> menuItem;
        cout << endl
            << endl
            << endl;
        switch (menuItem)
        {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            amount = LineSearch(p, N);
            cout << "ʳ������ ��������, �� ��������  ����� 4.5:" << amount << endl;
            break;
        case 4:
            Sort(p, N);
            break;
        case 5:
            cout << "������ ������� ���" << endl;
            cin >> averageRate;
            cout << "������ ��� � �������� ��������" << endl;
            cin >> thirdSubjectRate;
            cin.get();  // ������� ����� ��������� � �� ����������� �������
            cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
            cout << " �������: ";
            getline(cin, surname);
            cout << endl;
            if ((found = BinSearch(p, N, surname, averageRate, thirdSubjectRate)) != -1)
                cout << "�������� �������� � ������� " << found + 1 << endl;
            else
                cout << "�������� �������� �� ��������" << endl;
            break;
        case 6:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����"
                << endl;
        }
    } while (menuItem != 0);
    return 0;
}
void Create(Student* p, const int N)
{
    int specialization;
    for (int i = 0; i < N; i++)
    {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();  // ������� ����� ��������� � �� ����������� �������
        cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
        cout << " �������: ";
        getline(cin, p[i].surname);
        cout << " ����: ";
        cin >> p[i].course;
        cout << " ������������ (0 - ��������� �����,  1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������)-> ";
        cin >> specialization;
        cout << " ������ � ������: ";
        cin >> p[i].physicsRate;
        cout << " ������ � ����������: ";

   
            cin >> p[i].mathRate;

        p[i].specialization = (Specialization)specialization;
        switch (p[i].specialization)
        {
        case COMPUTER_SCIENCE:
            cout << " ������ � �������������: ";
            cin >> p[i].programmingRate;
            p[i].averageRate = (p[i].physicsRate + p[i].mathRate + p[i].programmingRate) / 3;
            p[i].thirdSubject = p[i].programmingRate;
            break;
        case IT:
            cout << " ������ � ��������� ������: ";
            cin >> p[i].chMRate;
            p[i].averageRate = (p[i].physicsRate + p[i].mathRate + p[i].chMRate) / 3;
            p[i].thirdSubject = p[i].chMRate;
            break;
        case MATH:
        case PHYSICS_AND_IT:
        case HANDICRAFT:
            cout << " ������ � ��������� : ";
            cin >> p[i].pedagogicRate;
            p[i].averageRate = (p[i].physicsRate + p[i].mathRate + p[i].pedagogicRate) / 3;
            p[i].thirdSubject = p[i].pedagogicRate;
            break;
        default:
            cout << " Wrong input";
            cout << endl;
        }
    }
}
void Print(Student* p, const int N)
{
    cout << "=============================================================="
        << endl;
    cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ������������� | ������� ������ | ���������"
        << endl;
    cout << "--------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(10) << left << p[i].surname
            << "| " << setw(4) << right << p[i].course << " "
            << "| " << setw(5) << left << specializationArr[p[i].specialization] << " "
            << "| " << setw(5) << right << p[i].physicsRate << " "
            << "| " << setw(5) << left << p[i].mathRate;

        switch (p[i].specialization)
        {
        case COMPUTER_SCIENCE:
            cout << "| " << setw(9) << setprecision(2) << fixed << right
                << p[i].programmingRate << " |" << setw(13) << right << "|" << endl;
            break;
        case IT:
            cout << "| " << setw(9) << setprecision(2) << fixed << right
                << p[i].chMRate << " |" << setw(13) << right << "|" << endl;
            break;
        case MATH:
        case PHYSICS_AND_IT:
        case HANDICRAFT:
            cout << "| " << setw(11) << right << "|"
                << " " << setw(8) << right
                << p[i].pedagogicRate << " |" << endl;
            break;
        }
    }
    cout << "========================================================================="
        << endl;
    cout << endl;
}
int LineSearch(Student* p, const int N)
{
    int amountOfStudent = 0; // ��������� ������� ��������, �� ��������  ����� 4.5
    for (int i = 0; i < N; i++)
    {
        if (p[i].averageRate > 4.5)
        {
            ++amountOfStudent;
        }
    }
    return amountOfStudent;
}
void Sort(Student* p, const int N)
{
    Student tmp;
    for (int i = 0; i < N - 1; i++) // ����� "���������"
        for (int j = 0; j < N - i - 1; j++)
            if ((p[j].averageRate < p[j + 1].averageRate) ||
                (p[j].averageRate == p[j + 1].averageRate &&
                    p[j].thirdSubject < p[j + 1].thirdSubject)||
                ((p[j].averageRate == p[j + 1].averageRate &&
                    p[j].thirdSubject == p[j + 1].thirdSubject &&
                    p[j].surname < p[j + 1].surname)))
            {
                tmp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = tmp;
            }
}
int BinSearch(Student* p, const int N, const string surname, float averageRate, int thirdSubjectRate)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
    int L = 0, R = N - 1, m;
    do
    {
        m = (L + R) / 2;
        if (p[m].surname == surname && p[m].averageRate == averageRate && p[m].thirdSubject == thirdSubjectRate)
            return m;
        if ((p[m].surname < surname) ||
            (p[m].surname == surname &&
                p[m].averageRate < averageRate) ||
            (p[m].surname == surname &&
                p[m].averageRate == averageRate &&
                p[m].thirdSubject < thirdSubjectRate))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}
int* IndexSort(Student* p, const int N)
{ // ������������� ����� ������� ��� ���������� ���������� ������
  //

        // int i, j, value;
          // for (i = 1; i < length; i++) {
          // value = a[i];
          // for (j = i - 1; j >= 0 && a[j] > value; j--) {
          // a[j + 1] = a[j];
          // }
          // a[j + 1] = value;
          // }
        int* I = new int[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        I[i] = i;      // ��������� ���� ����������� ������
    int i, j, value; // �������� ��������� ����� �������
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1; j >= 0; j--)
             if ((p[I[j]].averageRate > p[value].averageRate) ||
                (p[I[j]].averageRate == p[value].averageRate &&
                    p[I[j]].thirdSubject > p[value].thirdSubject)||
                (p[I[j]].averageRate == p[value].averageRate &&
                    p[I[j]].thirdSubject == p[value].thirdSubject &&
                    p[I[j]].surname > p[value].surname
                    ))
            
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{ // ��������� ������� Print(), ��� ������ ��������� p[i]...
  // ������������� ������ �� ��������� ���������� ������ �: p[I[i]]...71
    cout << "=============================================================="
        << endl;
    cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ������������� | ������� ������ | ���������"
        << endl;
    cout << "--------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(3) << right << i + 1 << " ";
        cout << "| " << setw(10) << left << p[I[i]].surname
            << "| " << setw(4) << right << p[I[i]].course << " "
            << "| " << setw(5) << left << specializationArr[p[I[i]].specialization] << " "
            << "| " << setw(5) << right << p[I[i]].physicsRate << " "
            << "| " << setw(5) << left << p[I[i]].mathRate;

        switch (p[I[i]].specialization)
        {
        case COMPUTER_SCIENCE:
            cout << "| " << setw(9) << setprecision(2) << fixed << right
                << p[I[i]].programmingRate << " |" << setw(13) << right << "|" << endl;
            break;
        case IT:
            cout << "| " << setw(9) << setprecision(2) << fixed << right
                << p[I[i]].chMRate << " |" << setw(13) << right << "|" << endl;
            break;
        case MATH:
        case PHYSICS_AND_IT:
        case HANDICRAFT:
            cout << "| " << setw(11) << right << "|"
                << " " << setw(8) << right
                << p[I[i]].pedagogicRate << " |" << endl;
            break;
        }
    }
    cout << "========================================================================="
        << endl;
    cout << endl;
}