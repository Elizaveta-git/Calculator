#pragma once
#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"

using namespace std;

enum functions { COS, SIN, TG, CTG, LN, LOG, SQRT, PI, EXP, ABS, E, no_func };

class Calculator
{
private:
	struct Element
	{
		Element* next;
		Element* prev;
		string symbol;
		Element(string symbol)
		{
			this->next = NULL;
			this->prev = NULL;
			this->symbol = symbol;
		}
	};
	Element* head;
	Element* tail;
	size_t size;
	Queue <string> queue;
	Stack <string> stack;
	Stack <double> count;

public:

	Calculator();
	~Calculator();

	//////METHODS//FOR//LIST//////

	void push_back(string);
	void pop_back();
	string at(size_t);
	size_t get_size();
	void print_to_console();

	//////METHODS//FOR//CALCULATOR//////

	bool is_digit_char(char);
	bool is_digit_string(string);
	bool is_character_char(char);
	bool is_character_string(string);
	bool is_operation_char(char);
	bool is_operation_string(string);
	int prior(string);
	int functions(string);
	double unary_minus(double);
	double CountFuncions(int, double);
	void CountOperations(string, double, double);
	bool processing_string(string, bool);
	bool check_for_error(bool);
	void infix_to_postfix(Calculator*);
	void print_posfix();
	double count_postfix();
};