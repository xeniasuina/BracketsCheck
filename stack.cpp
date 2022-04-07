#include "stack.h"

void push(elem*& top, char x, const int pos)
{
	//Создаем элемент стека (размещаем в памяти)
	elem* new_el = new elem;
	new_el->c = x;
	new_el->pos = pos;
	//Изменяем указатель на следующий элемент стека
	new_el->next = top;
	//Корректируем указатель на вершину стека
	top = new_el;
}

bool pop(elem*& top, char& x)
{
	//Проверка стека на пустоту
	if (!top) return false;
	//Сохранение значения элемента стека
	x = top->c;
	//Сохранение указателя на текущую вершину во временной переменной
	elem* old_el = top;
	//Изменение вершины стека
	top = top->next;
	//Очищаем память из-под удаляемого элемента
	delete old_el;
	return true;
}

bool peek(const elem* top, int& pos, char& br)
{
	//Проверка стека на пустоту
	if (!top) return false;
	//Сохранение значения элемента стека
	pos = top->pos;
	br = top->c;
	return true;
}

void clear(elem*& top)
{	
	char x;
	while (top) pop(top, x);
}