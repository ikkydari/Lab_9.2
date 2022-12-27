#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Specialization
{
    COMPUTER_SCIENCE,
    IT,
    MATH,
    PHYSICS_AND_IT,
    HANDICRAFT,
};
string specializationArr[] = { "Комп’ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };
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
{ // забезпечення відображення кирилиці:
   SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
   SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
    int N;
    cout << "Введіть к-ть студентів: ";
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
        cout << "Виберіть дію:" << endl
            << endl;
        cout << " [1] - введення даних з клавіатури" << endl;
        cout << " [2] - вивід даних на екран" << endl;
        cout << " [3] - вивід кількості студентів," << endl;
        cout << " середній бал яких вищий за 4,5" << endl;
        cout << " [4] - фізичне впорядкування даних" << endl;
        cout << " [5] - бінарний пошук студента за посадою та прізвищем" << endl;
        cout << " [6] - індексне впорядкування та вивід даних"
            << endl
            << endl;
        cout << " [0] - вихід та завершення роботи програми" << endl
            << endl;
        cout << "Введіть значення: ";
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
            cout << "Кількість студентів, що отримали  більше 4.5:" << amount << endl;
            break;
        case 4:
            Sort(p, N);
            break;
        case 5:
            cout << "Введіть середній бал" << endl;
            cin >> averageRate;
            cout << "Введіть бал з третього предмету" << endl;
            cin >> thirdSubjectRate;
            cin.get();  // очищуємо буфер клавіатури – бо залишаються символи
            cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
            cout << " прізвище: ";
            getline(cin, surname);
            cout << endl;
            if ((found = BinSearch(p, N, surname, averageRate, thirdSubjectRate)) != -1)
                cout << "Знайдено студента в позиції " << found + 1 << endl;
            else
                cout << "Шуканого студента не знайдено" << endl;
            break;
        case 6:
            PrintIndexSorted(p, IndexSort(p, N), N);
            break;
        case 0:
            break;
        default:
            cout << "Ви ввели помилкове значення! "
                "Слід ввести число - номер вибраного пункту меню"
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
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.get();  // очищуємо буфер клавіатури – бо залишаються символи
        cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
        cout << " Прізвище: ";
        getline(cin, p[i].surname);
        cout << " Курс: ";
        cin >> p[i].course;
        cout << " Спеціальність (0 - Комп’ютерні науки,  1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання)-> ";
        cin >> specialization;
        cout << " Оцінка з фізики: ";
        cin >> p[i].physicsRate;
        cout << " Оцінка з математики: ";

   
            cin >> p[i].mathRate;

        p[i].specialization = (Specialization)specialization;
        switch (p[i].specialization)
        {
        case COMPUTER_SCIENCE:
            cout << " Оцінка з програмування: ";
            cin >> p[i].programmingRate;
            p[i].averageRate = (p[i].physicsRate + p[i].mathRate + p[i].programmingRate) / 3;
            p[i].thirdSubject = p[i].programmingRate;
            break;
        case IT:
            cout << " Оцінка з чисельних методів: ";
            cin >> p[i].chMRate;
            p[i].averageRate = (p[i].physicsRate + p[i].mathRate + p[i].chMRate) / 3;
            p[i].thirdSubject = p[i].chMRate;
            break;
        case MATH:
        case PHYSICS_AND_IT:
        case HANDICRAFT:
            cout << " Оцінка з педагогіки : ";
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
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка"
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
    int amountOfStudent = 0; // початкова кількість студентів, що отримали  більше 4.5
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
    for (int i = 0; i < N - 1; i++) // метод "бульбашки"
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
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
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
{ // використовуємо метод вставки для формування індексного масиву
  //

        // int i, j, value;
          // for (i = 1; i < length; i++) {
          // value = a[i];
          // for (j = i - 1; j >= 0 && a[j] > value; j--) {
          // a[j + 1] = a[j];
          // }
          // a[j + 1] = value;
          // }
        int* I = new int[N]; // створили індексний масив
    for (int i = 0; i < N; i++)
        I[i] = i;      // заповнили його початковими даними
    int i, j, value; // починаємо сортувати масив індексів
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
{ // аналогічно функції Print(), але замість звертання p[i]...
  // використовуємо доступ за допомогою індексного масиву І: p[I[i]]...71
    cout << "=============================================================="
        << endl;
    cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка"
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