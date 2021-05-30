//На основі контейнера list побудувати двозв’язні кільцеві списки цілих чисел та символьних рядків.
//Виконати операції занесення елемента до списку, вилучення елемента зі списку, виведення елементів списку на екран, визначення кількості елементів списку
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<typename T>
class List
{
private:
	list<T> mylist;
public:
	List() {}
	~List() {}
	int AddElements(T elem)
	{
		int size = mylist.size();
		if (size == 0)
		{
			mylist.push_back(elem);
			return 0;
		}
		T prev = mylist.front();
		if (elem < prev)
		{
			mylist.push_front(elem);
			return 0;
		}
		int index = 0;
		for (T data : mylist)
		{
			if (elem > prev && elem < data)
			{
				auto iter = mylist.begin();
				advance(iter, index);
				mylist.insert(iter, elem);
				return index;
			}

			T prev = data;
			index++;
		}
		mylist.push_back(elem);
		return index + 1;
	}

	friend ifstream& operator>>(ifstream& in, List& ob) //перегрузка введення
	{
		while (!in.eof())
		{
			T el;
			in >> el;
			ob.AddElements(el);
		}
		return in;
	}

	friend ofstream& operator<<(ofstream& out, List& ob) //перегрузка виведення
	{
		for(T elem :  ob.mylist)
		out << elem<<" ";
		out << "\n";
		return out;
	}

	void PrintFile(string path)
	{
		ofstream of;
		of.open(path, ios::app);
			of<<*this;
			of.close();
	}

	void PrintConsole()
	{
		for (T elem : mylist)
			cout << elem << " ";
		
	}

	void GetFromFile(string path)
	{
		ifstream in;
		in.open(path);
		in >> *this;
		in.close();
	}

	int DeleteElem(int ind)
	{
		auto iter = mylist.begin();
		advance(iter, ind);
		mylist.erase(iter);
		return ind + 1;
	}

	int size()
	{
		return mylist.size();
	}

};

int main()
{
	system("chcp 1251");
	List <string> list_str;
	List <int> list_int;
	list_int.AddElements(5);
	list_int.AddElements(3);
	list_int.AddElements(28);
	list_int.AddElements(12);
	list_int.AddElements(1);
	list_int.AddElements(65);
	cout << "\n\tList of elements :\n";
	list_int.PrintConsole();
	list_int.DeleteElem(4);
	list_int.DeleteElem(2);
	cout << "\n\tList of elements : (shorted) \n";
	list_int.PrintConsole();
	list_str.GetFromFile("E:\\ООП7\\IN.txt");
	list_str.PrintFile("E:\\ООП7\\OUT.txt");
	list_int.PrintFile("E:\\ООП7\\OUT.txt");
	return 0;
}

