#include <iostream>
#include <cstdlib>
#include "class_genetic.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");
    srand((unsigned)time(NULL));

    int INITIAL_POP = 10;
    int likelihood_mutation = 20, likelihood_cross = 70;
    int KOLVO = 50;

    cout << "     ГЕНЕТИЧЕСКИЙ АЛГОРИТМ " << endl;
    cout << "     НАХОЖДЕНИЯ МАКСИМУМА ФУНКЦИИ: " << endl;
    cout << "     f(x) = 3х^3 - 2х + 5   на интервале [1 - 10]" << endl << endl;
    cout << " ПАРАМЕТРЫ АЛГОРИТМА:" << endl;
    cout << " Размер нач. популяции: 10, вероятность мутации: 20%, вероятность кроссинговера: 70%, число генераций: 50" << endl;
    cout << endl << " Оставить значения по умолчанию? 0 - нет, 1 - да" << endl;
    int f1;
    cin >> f1;

    if (f1 == 0)
    {
        cout << " Размер начальной популяции:" << endl;
        cin >> INITIAL_POP;
        if (INITIAL_POP < 2)
        {
            cout << endl << " ОШИБКА! Некорректный ввод." << endl;
            system("pause");
            return -1;
        }
        cout << " Вероятность мутации в процентах:" << endl;
        cin >> likelihood_mutation;
        cout << " Вероятность кроссинговера в процентах:" << endl;
        cin >> likelihood_cross;
        if (likelihood_mutation < 0 || likelihood_cross < 0 || likelihood_mutation > 100 || likelihood_cross > 100)
        {
            cout << endl << " ОШИБКА! Некорректный ввод." << endl;
            system("pause");
            return -1;
        }
        cout << " Число генераций (не менее 50):" << endl;
        cin >> KOLVO;
        if (KOLVO < 50)
        {
            cout << endl << "ОШИБКА! Некорректный ввод." << endl;
            system("pause");
            return -1;
        }
    }

    int strategia;
    cout << " Выберите стратегию создания начальной популяции:" << endl;
    cout << " 0 - стратегия дробовика, 1 - стратегия одеяла" << endl;
    cin >> strategia;
    if (strategia < 0 || strategia > 1)
    {
        cout << endl << "ОШИБКА! Некорректный ввод." << endl;
        system("pause");
        return -1;
    }
    int type_cross;
    cout << " Выберите вид кроссинговера: " << endl;
    cout << " 1 - стандартный одноточечный, 2 - стандартный двухточечный" << endl;
    cin >> type_cross;
    if (type_cross < 1 || type_cross > 2)
    {
        cout << endl << "ОШИБКА! Некорректный ввод." << endl;
        system("pause");
        return -1;
    }

    double l = (double)likelihood_cross / 100;
    int SIZE_POP = round(INITIAL_POP * l);
    if (SIZE_POP % 2 != 0)
        SIZE_POP--;

    Class_Genetic GA(INITIAL_POP, SIZE_POP, likelihood_mutation, likelihood_cross);

    if (strategia == 0)
        GA.InintPopShotgun();
    else
        GA.InintPopCovering();
    for (int i = 0; i < KOLVO; i++)
    {
        cout << endl << " -----------------------" << endl << "     ГЕНЕРАЦИЯ № " << i + 1 << endl;
        GA.EliteSelection();
        if (type_cross == 1)
            GA.OnePointCross();
        if (type_cross == 2)
            GA.TwoPointCross();
        GA.Inversion();
        GA.Otbor();
        cout << endl;
    }
    GA.Answer();

    system("pause");
    return 0;
}