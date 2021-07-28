#include <stdlib.h>
#include <iostream>
#include <time.h>
using namespace std;

static const int FIRST = 1;
static const int LAST = 10;

struct chromosome 
{
	bool binary[4];
	int fitness;
	double completeness;

	bool operator== (chromosome c) {
		for (int i = 0; i < 4; i++) {
			if (c.binary[i] != binary[i])
				return false;
		}
		return true;
	}
};

class Class_Genetic
{
public:
	Class_Genetic(int, int, int, int);
	int INITIAL_POP;
	chromosome* initial_population = new chromosome[INITIAL_POP];
	int SIZE_POP;
	chromosome* population = new chromosome[(SIZE_POP / 2) + INITIAL_POP];
	int likelihood_mutation;
	int likelihood_cross;

	int Fitness(chromosome& c); 
	int Decimal(chromosome& c);
	void InintPopCovering(); 
	void InintPopShotgun(); 
	void EliteSelection(); 
	void OnePointCross();
	void TwoPointCross();
	void Inversion();
	void Otbor();
	void Answer();
};

Class_Genetic::Class_Genetic(int pop, int size, int v1, int v2) :
	INITIAL_POP(pop), SIZE_POP(size), likelihood_mutation(v1), likelihood_cross(v2) {}

int Class_Genetic::Fitness(chromosome& c)
{
	int dec = c.binary[0] * pow(2, 3) + c.binary[1] * pow(2, 2) + c.binary[2] * pow(2, 1) + c.binary[3] * pow(2, 0);
	int f = 3 * pow(dec, 3) - 2 * dec + 5;
	return c.fitness = f;
}

int Class_Genetic::Decimal(chromosome& c)
{
	int dec = c.binary[0] * pow(2, 3) + c.binary[1] * pow(2, 2) + c.binary[2] * pow(2, 1) + c.binary[3] * pow(2, 0);
	return dec;
}

void Class_Genetic::InintPopCovering()
{
	setlocale(LC_ALL, "Russian");

	if (INITIAL_POP > 10)
	{
		for (int i = 0; i < 10; i++)
		{
			int dec = i + 1;
			for (int j = 3; j >= 0; j--)
			{
				initial_population[i].binary[j] = dec % 2;
				dec /= 2;
			}
		}
		for (int i = 10; i < INITIAL_POP; i++)
		{
			int dec = trunc((LAST - FIRST + 1) / (2 * INITIAL_POP) + ((LAST - FIRST + 1) / INITIAL_POP) * i) + 1;
			for (int j = 3; j >= 0; j--)
			{
				initial_population[i].binary[j] = dec % 2;
				dec /= 2;
			}
		}
	}
	else
		for (int i = 0; i < INITIAL_POP; i++)
		{
			int dec = trunc((LAST - FIRST + 1) / (2 * INITIAL_POP) + ((LAST - FIRST + 1) / INITIAL_POP) * i) + 1;
			for (int j = 3; j >= 0; j--)
			{
				initial_population[INITIAL_POP - i - 1].binary[j] = dec % 2;
				dec /= 2;
			}
		}

	cout << "---------------" << endl;
	cout << "Начальная популяция, стратегия одеяла:" << endl;
	for (int i = 0; i < INITIAL_POP; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << initial_population[i].binary[j];
		cout << endl;
	}
	cout << endl;
}

void Class_Genetic::InintPopShotgun()
{
	for (int i = 0; i < INITIAL_POP; i++)
	{
		int dec = rand() % (LAST - FIRST + 1) + FIRST;
		for (int j = 3; j >= 0; j--)
		{
			initial_population[i].binary[j] = dec % 2;
			dec /= 2;
		}
	}

	cout << "---------------" << endl;
	cout << "Начальная популяция, стратегия дробовика:" << endl;
	for (int i = 0; i < INITIAL_POP; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << initial_population[i].binary[j];
		cout << endl;
	}
	cout << endl;
}

void Class_Genetic::EliteSelection()
{
	for (int i = 0; i < INITIAL_POP; i++)
		for (int j = i + 1; j < INITIAL_POP; j++)
			if (Fitness(initial_population[i]) < Fitness(initial_population[j]))
				swap(initial_population[i], initial_population[j]);
	for (int i = 0; i < INITIAL_POP; i++)
		population[i] = initial_population[i];
	for (int i = INITIAL_POP; i < INITIAL_POP + (SIZE_POP / 2); i++)
		for (int j = 0; j < 4; j++)
			population[i].binary[j] = 0;

	cout << endl << "---------------" << endl;
	cout << "Элитная селекция:" << endl;
	for (int i = 0; i < SIZE_POP; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << population[i].binary[j];
		cout << endl;
	}
	cout << endl;
}

void Class_Genetic::OnePointCross()
{
	cout << "---------------" << endl;
	cout << "Одноточечный кроссинговер:" << endl;
	for (int q = INITIAL_POP; q < INITIAL_POP + (SIZE_POP / 2); q++)
	{
		int r = rand() % 100 + 1;
		if (r <= likelihood_cross)
		{
		    int num1, num2;
			int size = SIZE_POP - 1;
			num1 = rand() % (size + 1) + 0;
			if (num1 == 0)
				num2 = 1;
			else
				if (num1 == size)
					num2 = size - 1;
				else
				{
					int d1 = abs(Fitness(population[num1]) - Fitness(population[num1 - 1]));
					int d2 = abs(Fitness(population[num1]) - Fitness(population[num1 + 1]));
					if (d1 > d2)
						num2 = num1 + 1;
					else
						num2 = num1 - 1;
				}
			chromosome a1 = population[num1];
			chromosome a2 = population[num2];
			chromosome a3;
			chromosome a4;
			int point = rand() % 4 + 0;
			for (int i = 0; i < 4; i++)
			{
				if (i < point)
				{
					a3.binary[i] = population[num1].binary[i];
					a4.binary[i] = population[num2].binary[i];
				}
				if (i >= point)
				{
					a3.binary[i] = population[num2].binary[i];
					a4.binary[i] = population[num1].binary[i];
				}
			}
			int prob0 = Decimal(a3);
			int prob1 = Decimal(a4);
			if (prob0 > LAST || prob0 < FIRST || prob1 > LAST || prob1 < FIRST)
			{
				q--;
				continue;
			}
			else
			{
				if (Fitness(a3) > Fitness(a4))
					population[q] = a3;
				else
					population[q] = a4;

				cout << "Родители: ";
				for (int i = 0; i < 4; i++)
					cout << population[num1].binary[i];
				cout << "    ";
				for (int i = 0; i < 4; i++)
					cout << population[num2].binary[i];
				cout << endl;
				cout << "Потомок: ";
				for (int i = 0; i < 4; i++)
					cout << population[q].binary[i];
				cout << endl;
			}
		}
	}
}

void Class_Genetic::TwoPointCross()
{
	cout << "---------------" << endl;
	cout << "Двухточечный кроссинговер: " << endl;
	for (int q = INITIAL_POP; q < INITIAL_POP + (SIZE_POP / 2); q++)
	{
		int r = rand() % 100 + 1;
		if (r <= likelihood_cross)
		{
		    int num1, num2;
			int size = SIZE_POP - 1;
			num1 = rand() % (size + 1);
			if (num1 == 0)
				num2 = 1;
			else
				if (num1 == size)
					num2 = size - 1;
				else
				{
					int d1 = abs(Fitness(population[num1]) - Fitness(population[num1 - 1]));
					int d2 = abs(Fitness(population[num1]) - Fitness(population[num1 + 1]));
					if (d1 > d2)
						num2 = num1 + 1;
					else
						num2 = num1 - 1;
				}
			chromosome a1 = population[num1]; 
			chromosome a2 = population[num2];
			chromosome a3;
			chromosome a4;
			int point1, point2;
			do
			{
				point1 = rand() % 4;
				point2 = rand() % 4;
			} while (point1 == point2);
			if (point1 > point2)
			{
				int tmp = point1;
				point1 = point2;
				point2 = tmp;
			}
			for (int i = 0; i < 4; i++)
			{
				if (i < point1) 
				{
					a3.binary[i] = a1.binary[i];
					a4.binary[i] = a2.binary[i];
				}
				if (i >= point1 && i < point2) 
				{
					a3.binary[i] = a2.binary[i];
					a4.binary[i] = a1.binary[i];
				}
				if (i >= point2)
				{
					a3.binary[i] = a1.binary[i];
					a4.binary[i] = a2.binary[i];
				}
			}
			int prob0 = Decimal(a3);
			int prob1 = Decimal(a4);
			if (prob0 > LAST || prob0 < FIRST || prob1 > LAST || prob1 < FIRST)
			{
				q--;
				continue;
			}
			else
			{
				if (Fitness(a3) > Fitness(a4))
					population[q] = a3;
				else
					population[q] = a4;

				cout << "Родители: ";
				for (int i = 0; i < 4; i++)
					cout << population[num1].binary[i];
				cout << "    ";
				for (int i = 0; i < 4; i++)
					cout << population[num2].binary[i];
				cout << endl;
				cout << "Потомок: ";
				for (int i = 0; i < 4; i++)
					cout << population[q].binary[i];
				cout << endl;
			}
		}
	}
}

void Class_Genetic::Inversion()
{
	int r = rand() % 100 + 1;
	if (r <= likelihood_mutation)
	{
		int size = (SIZE_POP / 2) + INITIAL_POP;
		int num = rand() % size + 0; 
		chromosome a = population[num];

		int point1, point2;
		do
		{
			point1 = rand() % 4;
			point2 = rand() % 4;
		} while (point1 == point2);
		if (point1 > point2)
		{
			int tmp = point1;
			point1 = point2;
			point2 = tmp;
		}
		for (int i = point1; i <= point2; i++)
			for (int j = point2; j >= point1; j--)
			{
				swap(population[num].binary[i], population[num].binary[j]);
				if (i == j || abs(i - j) == 1)
					break;
			}

		int prob = Decimal(population[num]);
		if (prob > LAST || prob < FIRST)
		{
			population[num] = a;
			Inversion();
		}
		else
		{
			cout << "--------------" << endl;
			cout << "Инверсия " << endl;
			cout << "Выбрана хромосома: ";
			for (int i = 0; i < 4; i++)
				cout << a.binary[i];
			cout << endl;
			cout << "После инверсии: ";
			for (int i = 0; i < 4; i++)
				cout << population[num].binary[i];
			cout << endl;
		}
	}
}

void Class_Genetic::Otbor()
{
	cout << "---------------" << endl;
	cout << "Популяция после кроссинговера и инверсии:" << endl;
	for (int i = 0; i < INITIAL_POP + (SIZE_POP / 2); i++)
	{
		if (Decimal(population[i]) != 0) 
		{
			for (int j = 0; j < 4; j++)
				cout << population[i].binary[j];
			cout << endl;
		}
	}
	cout << endl;
	cout << "---------------" << endl;
	cout << "Значения ЦФ от хромосом:" << endl;
	for (int i = 0; i < INITIAL_POP + (SIZE_POP / 2); i++)
	{
		if (Decimal(population[i]) != 0) 
		{
			population[i].fitness = Fitness(population[i]);
			cout << population[i].fitness << endl;
		}
	}
	cout << endl;
	int count = 0;
	double all_completeness = 0;
	for (int i = 0; i < INITIAL_POP + (SIZE_POP / 2); i++)
	{
		if (Decimal(population[i]) != 0)
		{
			all_completeness += population[i].fitness;
			count++;
		}
	}
	all_completeness = all_completeness / count;
	cout << "---------------" << endl;
	cout << "Cредняя приспособленность:  " << all_completeness << endl;
	cout << "---------------" << endl;
	cout << "Приспособленность каждой хромосомы: " << endl;
	for (int i = 0; i < INITIAL_POP + (SIZE_POP / 2); i++)
	{
		if (Decimal(population[i]) != 0)
		{
			population[i].completeness = population[i].fitness / all_completeness;
			cout << population[i].completeness << endl;
		}
		else
			population[i].completeness = 0;
	}

	for (int i = 0; i < INITIAL_POP + (SIZE_POP / 2); i++)
		for (int j = i + 1; j < INITIAL_POP + (SIZE_POP / 2); j++)
			if (population[i].completeness < population[j].completeness)
				swap(population[i], population[j]);
	for (int i = 0; i < INITIAL_POP; i++)
		initial_population[i] = population[i];
	cout << "---------------" << endl;
	cout << "Пропорциональный отбор:" << endl;
	for (int i = 0; i < INITIAL_POP; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << initial_population[i].binary[j];
		cout << endl;
	}
	cout << endl;
}

void Class_Genetic::Answer()
{
	chromosome c = population[0];
	int x = Decimal(c);
	cout << "  ------------------------" << endl << "     ОТВЕТ:" << endl;
	cout << "     x  =  " << x << endl;
	cout << "     f (x)  =  " << Fitness(c) << endl;
	cout << "     КОНЕЦ РАБОТЫ ГА" << endl;
	cout << "  ------------------------" << endl << endl << endl;
}
