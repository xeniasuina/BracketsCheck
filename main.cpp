#include "stack.h"
#include <iostream>
#include "cgi.h"
#include <string.h>
#include "page3.h"
using namespace std;



void show_form1() {
	cout << "<div class='page3-form'><form action='page4.cgi' method='post'>"
			<< "<input type='text' required name='equation' placeholder='Enter the equation'>"
			<< "<button class='page3-button'><h3>Check!<h3></button>"
		<< "</form></div>"
		;
}

void check_equation(char*& equation, elem*& bracket) {
	int i = 0;
	size_t sz = strlen(equation) + 1;
	while (i < sz) {
		switch (equation[i]) {
			case('{'):
				push(bracket, equation[i], i);
				i += 1;		
				continue;
			case('('):
				push(bracket, equation[i], i);
				i += 1;
				continue;
			case('['):
				push(bracket, equation[i], i);
				i += 1;
				continue;
			case('&'):
				if (equation[i + 1] == 'l' && equation[i + 2] == 't') {
					push(bracket, '<', i);
					i += 2;
					continue;
				}
				else if (equation[i + 1] == 'g' && equation[i + 2] == 't') {
					int pos4;
					char br4;
					peek(bracket, pos4, br4);
					if (br4 == '<') {
						pop(bracket);
						i += 2;
						continue;
					}
					else {
						push(bracket, '>', i);
						i += 2;
						continue;
					}
				}
			case('}'):
				int pos1;
				char br1;
				peek(bracket, pos1, br1);
				if (br1 == '{') {
					pop(bracket);
					i += 1;
					continue;
				}
				else {
					push(bracket, equation[i], i);
					i += 1;
					continue;
				}
			case(')'):
				int pos2;
				char br2;
				peek(bracket, pos2, br2);
				if (br2 == '(') {
					pop(bracket);
					i += 1;
					continue;
				}
				else {
					push(bracket, equation[i], i);
					i += 1;
					continue;
				}
			case(']'):
				int pos3;
				char br3;
				peek(bracket, pos3, br3);
				if (br3 == '[') {
					pop(bracket);
					i += 1;
					continue;
				}
				else {
					push(bracket, equation[i], i);
					i += 1;
					continue;
				}
			default:
				i += 1;
				continue;
		}
	}
}


void show_res(const char* equation, elem*& bracket) {
	cout << "<div class='result'>"
		<< "<div class='sous-eq'>" 
		<< "<h2> Source equation </h2> <h3>" 
		<< equation 
		<< "</h3>" 
		<< "</div><div class='res-eq'><h2>";
	auto sz = strlen(equation) - 1;
	char* positions = new char[sz+1];
	for (int i = sz; i >= 0; i -= 1) {
		char ch;
		int pos;
		peek(bracket, pos, ch);
		if (i == pos) {
			if (ch == '<') {
				positions[i] = '2';
				pop(bracket);
				continue;
			}
			else if (ch == '>') {
				positions[i] = '3';
				pop(bracket);
				continue;
			}
			else {
				positions[i] = '1';
				pop(bracket);
			}
		}
		else {
			positions[i] = '0';
		}
	}
	for (int i = 0; i <= sz; i += 1) {
		if (positions[i] == '1' || positions[i] == '2' || positions[i] == '3') {
			if (positions[i] == '2') {
				cout << "<mark> &lt; </mark>";
				i += 2;
			}
			else if (positions[i] == '3') {
				cout << "<mark> &gt; </mark>";
				i += 2;
			}

			else {
				cout << "<mark>" << equation[i] << "</mark>";
			}
		}
		else {
			cout << equation[i];
		}

	}
	cout << "</h2></div></div>";
	delete[] positions;
}

void equation() {
	char* data = new char[65535];
	show_form1();
	get_form_data(data);
	char* equation = new char[strlen(data) + 1];
	get_param_value(equation, "equation", data);
	elem* bracket = nullptr;
	check_equation(equation, bracket);
	show_res(equation, bracket);
	delete[] data;
	delete[] equation;
}


