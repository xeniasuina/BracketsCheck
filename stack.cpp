#include "stack.h"

void push(elem*& top, char x, const int pos)
{
	//������� ������� ����� (��������� � ������)
	elem* new_el = new elem;
	new_el->c = x;
	new_el->pos = pos;
	//�������� ��������� �� ��������� ������� �����
	new_el->next = top;
	//������������ ��������� �� ������� �����
	top = new_el;
}

bool pop(elem*& top, char& x)
{
	//�������� ����� �� �������
	if (!top) return false;
	//���������� �������� �������� �����
	x = top->c;
	//���������� ��������� �� ������� ������� �� ��������� ����������
	elem* old_el = top;
	//��������� ������� �����
	top = top->next;
	//������� ������ ��-��� ���������� ��������
	delete old_el;
	return true;
}

bool peek(const elem* top, int& pos, char& br)
{
	//�������� ����� �� �������
	if (!top) return false;
	//���������� �������� �������� �����
	pos = top->pos;
	br = top->c;
	return true;
}

void clear(elem*& top)
{	
	char x;
	while (top) pop(top, x);
}