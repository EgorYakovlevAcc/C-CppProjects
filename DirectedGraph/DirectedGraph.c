#include <stdafx.h>

#define N 12; // Количество вершин графа.

typedef struct zveno *svqz;
typedef struct zveno {
	int Key; //Вершина графа.
	svqz Sled; // Указатель на следующую смежную вершину
} Leader;

svqz beg[N]; // Описание типа списков смежности

void MakeGraph(svqz beg[N])
// Построение списков смежности beg графа.
{
	int x, y;
	svqz ukzv, uzel; //Рабочие указатели.

	cout << "Вводите начало дуги: ";
	cin >> x;
	while (x != 0)
	{
		cout << "Вводите конец дуги: ";
		cin >> y;
		AddGraph(x, y, beg);
		cout << "Вводите начало дуги: "; cin >> x;
	}
}

void PrintGraph(svqz beg[N])
{
	int i;
	svqz ukzv; //Рабочий указатель.
	for (i = 1; i<N; i++)
	{
		cout << i << " ...";
		ukzv = beg[i];
		if (ukzv == NULL) cout << "Пустой список!\n";
		else {
			while (ukzv != NULL)
			{
				cout << (*ukzv).Key; ukzv = (*ukzv).Sled;
			}
			cout << endl;
		}
	}
}

void AddGraph(int x, int y, svqz beg[N])
{
	svqz ukzv, uzel; //Рабочие указатели.
	if (beg[x] != NULL)
	{
		Poisk(beg[x], y, &ukzv);
		if (ukzv == NULL)
		{ // Добавление элемента в конец списка, 
		  // заданного указателем beg[x]. 
			uzel = new (Leader);
			(*uzel).Key = y; (*uzel).Sled = NULL; ukzv = beg[x];
			while ((*ukzv).Sled != NULL)
				ukzv = (*ukzv).Sled;
			(*ukzv).Sled = uzel;
		}
	}
	else
	{
		beg[x] = new (zveno);
		(*beg[x]).Key = y; (*beg[x]).Sled = NULL;
	}
}

void Poisk(svqz uksp, int ment, svqz *res)
// Поиск звена с информационным полем ment в 
// однонаправленном списке uksp. *res - указатель 
// на найденное звено или NULL.
{
	svqz q;

	*res = NULL; q = uksp;
	while ((q != NULL) && (*res == NULL))
	{
		if ((*q).Key == ment) *res = q;
		q = (*q).Sled;
	}
}

void Udalenie(svqz *ukstr, svqz *zv)
// Удаление звена, на которое ссылается указатель *zv, 
// из однонаправленного списка, заданного указателем *ukstr.
{
	svqz ukzv, z;

	if (((**ukstr).Sled == NULL) && (*zv == *ukstr))
		// В списке - один элемент! 
	{
		*ukstr = NULL; delete zv;
	}
	else
		if (*zv == *ukstr) // Удаляемый элемент - первый.
		{
			*ukstr = (**ukstr).Sled; delete zv;
		}
		else {
			z = *ukstr; ukzv = (**ukstr).Sled;
			while (ukzv != *zv)
			{
				z = ukzv; ukzv = (*ukzv).Sled;
			}
			(*z).Sled = (*(*zv)).Sled; delete zv;
		}
}

int main()
{

	return 0;
}
