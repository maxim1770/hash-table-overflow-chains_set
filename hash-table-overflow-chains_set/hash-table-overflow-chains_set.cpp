#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
using namespace std;


class Hash_table_Chains
{
	int Size;
	int Capacity;
	struct Node
	{
		int Key;//ключ
		int Value;//значение 
		Node* next;//если несколько значений в ячейке, то уходим в глубину
	};
	Node** Mas; //массив значений

public:
	// хеш-функция для получения ключа
	int Hash(int X)
	{
		return X % Capacity;
	};
	Hash_table_Chains(int new_capacity = 1000)//конструктор 
	{
		Capacity = new_capacity;
		Size = 0;
		Mas = new Node * [Capacity];
		for (int i = 0; i < Capacity; i++)Mas[i] = nullptr;
	};
	~Hash_table_Chains()//деконструктор 
	{
		Clear();
		delete[] Mas;
	};
	Hash_table_Chains(const Hash_table_Chains& table)//конструктор копирования 
	{
		Capacity = table.Capacity;
		Size = table.Size;
		Mas = table.Mas;
		for (int i = 0; i < Capacity; i++)
		{
			Mas[i] = nullptr;
			if (table.Mas[i])
			{
				Node* p = table.Mas[i];
				Node* q = Mas[i];
				Mas[i] = new Node;
				while (p)
				{
					q->Value = p->Value;
					q->Key = p->Key;
					q->next = p->next;
					q = q->next;
					p = p->next;
				}
			}
		}
	};

	void Clear()
	{
		for (int i = 0; i < Capacity; i++)
		{
			Node* cur = Mas[i];
			while (cur) //вниз идем 
			{
				Node* prev = cur;
				cur = cur->next;
				delete prev;
			}
			Mas[i] = nullptr;
		}
		Size = 0;
		Capacity = 0;
	};

	void Print()
	{
		for (int i = 0; i < Capacity; i++)
		{
			Node* cur = Mas[i];
			if (cur) {
				cout << "Индекс " << i << endl;
				while (cur)
				{
					cout << "Значение " << cur->Value << endl;
					cout << "Ключ " << cur->Key << endl;
					cur = cur->next;
					if (cur)cout << endl;
				}
				cout << endl;
			}
		}
	};

	void Insert(int new_Key, int new_Value)//функция добавления в хэш таблицу
	{
		int index = Hash(new_Key);
		Node* cur = Mas[index];
		while (cur)
		{
			if (cur->Key == new_Key)
			{
				cur->Key = new_Key;
				cur->Value = new_Value;
				return;
			}
			cur = cur->next;
		}
		Node* cur1 = new Node;
		cur1->Key = new_Key;
		cur1->Value = new_Value;
		cur1->next = Mas[index];
		Mas[index] = cur1;
		Size++;
	};

	void mult(Hash_table_Chains* A, Hash_table_Chains* B)
	{
		for (int i = 0; i < A->return_Capacity(); i++)//проходим по всей 1 талбице
		{
			if (A->Mas[i])//если не пусто
			{
				Node* cur = A->Mas[i];
				while (cur)//спускаемся по ней вниз
				{
					if (B->Find(cur->Value))Insert(cur->Value, cur->Value);//если такой же ялемент есть во 2 таблице, то заносим его в новую таблицу
					cur = cur->next;
				}
			}
		}
	}

	bool Delete(int Key)//функция удаления
	{
		if (Find(Key))
		{
			int index = Hash(Key);
			Node* cur = Mas[index];//текущий
			Node* pre = nullptr;//предыдущий 
			while (cur->next)
			{
				if (cur->Key == Key)
				{
					if (pre == nullptr)Mas[index] = cur->next;
					else pre->next = cur->next;
					free(cur);//=0
					return 1;
				}
				pre = cur;
				cur = cur->next;
			}
		}
	};

	bool Find(int Key)
	{
		int index = Hash(Key);
		if (Mas[index])
		{
			Node* cur = Mas[index];
			while (cur)
			{
				if (Key == cur->Key) return 1;
				cur = cur->next;
			}
		}
		return 0;
	};

	bool isEmpty()//проверка на пустоту 
	{
		for (int i = 0; i < Capacity; i++)
			if (Mas[i])return 0;
		return 1;
	};

	int return_Size() { return Size; };
	int return_Capacity() { return Capacity; };
};


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int new_size;
	cout << "Введите размерность таблицы 1: "; cin >> new_size;
	Hash_table_Chains Table1(new_size);
	cout << "Заполните множество 1:" << endl;
	for (int i = 0; i < new_size; i++)
	{
		int new_var; cin >> new_var;
		Table1.Insert(new_var, new_var);
	}
	cout << "Данные заполнены:" << endl
		<< "Вывод на экран..." << endl;
	Table1.Print();
	cout << endl;
	system("pause");//нажмите люб кнопку для продолжения
	system("CLS");//очистка консоли
	cout << "Введите размерность таблицы 2: "; cin >> new_size;
	Hash_table_Chains Table2(new_size);
	cout << "Заполните множество 2:" << endl;
	for (int i = 0; i < new_size; i++)
	{
		int new_var; cin >> new_var;
		Table2.Insert(new_var, new_var);
	}
	cout << "Данные заполнены:" << endl
		<< "Вывод на экран..." << endl;
	Table2.Print();
	cout << endl;
	system("pause");
	system("CLS");
	Hash_table_Chains Table3(Table1.return_Capacity() + Table2.return_Capacity()); //создание новой табл (разм 1+2 табл)
	Table3.mult(&Table1, &Table2);//заполнение новой таблици
	cout << "Получено новое множество:" << endl;
	Table3.Print();


	Table1.Clear();
	Table2.Clear();
	Table3.Clear();
	cout << endl << endl;
	system("pause");
	return 1;
}