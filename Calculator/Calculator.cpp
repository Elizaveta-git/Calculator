#include "Calculator.h"

Calculator::Calculator()
{
	head = NULL;
	tail = NULL;
	size = 0;
}

Calculator::~Calculator()
{
	while (size != 0)
	{
		pop_back();
	}
}

//////METHODS//FOR//LIST//////

void Calculator::push_back(string data)
{
	if (size == 0)//insert first element if list is empty
	{
		head = new Element(data);//element creation
		tail = head;
	}
	else//insert element in the end of the list
	{
		tail->next = new Element(data);
		tail->next->prev = tail;
		tail = tail->next;
	}
	size++;//increasing list size
}

void Calculator::pop_back()
{
	if (size == 0)
	{
		throw out_of_range("The list is empty");
	}
	else if (size == 1)
	{
		delete head;
		head = NULL;
		tail = NULL;
	}
	else
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = NULL;
	}
	size--;
}

string Calculator::at(size_t index)
{
	if (index >= size)
	{
		throw out_of_range("Index is greater than list size");
	}
	Element* current = head;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	return current->symbol;
}

size_t Calculator::get_size()
{
	return size;
}

void Calculator::print_to_console()
{
	Element* current = this->head;//go to the beginning of the list
	while (current != NULL)//while new element exist
	{
		cout << current->symbol << " ";//display the value of the element
		current = current->next;//move on to the next element
	}
}

//////METHODS//FOR//CALCULATOR//////

bool Calculator::is_digit_char(char symbol)
{
	string numbers("0123456789");
	for (char this_symbol : numbers)
	{
		if (symbol == this_symbol)
			return true;
	}
	return false;
}

bool Calculator::is_digit_string(string element)
{
	string numbers("0123456789");
	char sign;
	bool error=false;
	for (int i = 0; i < element.length(); i++)
	{
		if (is_digit_char(element[i])==true) {
			error = true;
		}
	}
	if (error == true) return true;
	else return false;
}

bool Calculator::is_character_char(char symbol)
{
	string character("abcdefghijklmnopqrstuvwxyz");
	for (char this_symbol : character)
	{
		if (symbol == this_symbol)
			return true;
	}
	return false;
}

bool Calculator::is_character_string(string element)
{
	char sign;
	bool error = false;
	for (int i = 0; i < element.length(); i++)
	{
		if (is_character_char(element[i]) == true) {
			error = true;
		}
	}
	if (error == true) return true;
	else return false;
}

bool Calculator::is_operation_string(string symbol)
{
	if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/" || symbol == "^" || symbol=="&")
	{
		return true;
	}
	return false;
}

bool Calculator::is_operation_char(char symbol)
{
	switch (symbol)
	{
	case '^': case '/': case '*': case '+': case '-': case '(': case ')': return true;
	}
	return false;
}

int Calculator::prior(string symbol)
{
	if (symbol == "&") return 4;
	else if (symbol=="^") return 3;
	else if (symbol == "*" || symbol=="/") return 2;
	else if (symbol == "+" || symbol == "-") return 1;
	else if (symbol == ")" || symbol == "(") return 0;
	else return 6;
}

int Calculator::functions(string func)
{
	if (func == "cos")
	{
		return COS;
	}
	else if (func == "sin")
	{
		return SIN;
	}
	else if (func == "tg")
	{
		return TG;
	}
	else if (func == "ctg")
	{
		return CTG;
	}
	else if (func == "log")
	{
		return LOG;
	}
	else if (func == "ln")
	{
		return LN;
	}
	else if (func == "sqrt")
	{
		return SQRT;
	}
	else if (func == "pi")
	{
		return PI;
	}
	else if (func == "exp")
	{
		return EXP;
	}
	else if (func == "abs")
	{
		return ABS;
	}
	else if (func == "e")
	{
		return E;
	}
	else return no_func;
}

double Calculator::unary_minus(double oper)
{
	double result;
	result = oper * (-1);
	return result;
}

double Calculator::CountFuncions(int func, double number)
{
	double result = 0;
	switch (func)
	{
	case COS:
		result = cos(number);
		break;
	case SIN:
		result = sin(number);
		break;
	case TG:
		result = tan(number);
		break;
	case CTG:
		result = (cos(number) / sin(number));
		break;
	case LN:
		result = log(number);
		break;
	case LOG:
		result = log10(number);
		break;
	case SQRT:
		if (number>0) result = sqrt(number);
		else
		{
			cout << endl << "negative root!";
		}
		break;
	case EXP:
		result = exp(number);
		break;
	case ABS:
		result = abs(number);
		break;
	}
	return result;
}

void Calculator::CountOperations(string sign, double oper1, double oper2)
{
	if (sign == "+")
	{
		count.push(oper1 + oper2);
	}
	else if (sign == "-")
	{
		count.push(oper2 - oper1);
	}
	else if (sign == "*")
	{
		count.push(oper1 * oper2);
	}
	else if (sign == "/")
	{
		count.push(oper2 / oper1);
	}
	else if (sign == "^")
	{
		count.push(pow(oper2, oper1));
	}
}

bool Calculator::processing_string(string infix, bool error)
{
	char sign, sign_last = '#', sign_last_last = '#';
	string element, digit, symbol;
	
	for (int i = 0; i<infix.length(); i++)
	{
		sign = infix[i];
		if (is_digit_char(sign))//if gigit
		{
			if (is_digit_char(sign_last) || sign_last == ',' || sign_last=='.')//if the number is real, then we collect it into one element											   
			{
				digit.push_back(sign);
			}
			else
			{
				digit=sign;
			}
		}
		else if (is_character_char(sign))//if symbol
		{
			if (is_character_char(sign_last))//if the penultimate character is a letter, then we collect the word
			{
				symbol.push_back(sign);
			}
			else
			{
				symbol=sign;
			}
		}
		else if ((sign == '-' && sign_last == '(') || (sign=='-' && i==0))//unary minus
		{
			element = '&';
			push_back(element);
		}
		else if (sign == ',' || sign=='.')//charge period to comma
		{
			digit.push_back(',');
			if (sign==sign_last)
			{
				cout << endl << "Uncorrected input: ..." << sign_last << sign;
				error = true;
				break;
			}
		}
		else if (sign == '(')//if the left parenthesis, then push it onto the stack
		{
			if (!digit.empty())
			{
				push_back(digit);
				digit.clear();
			}
			if (!symbol.empty())
			{
				push_back(symbol);
				symbol.clear();
			}
			element = '(';
			push_back(element);
			
		}
		else if (sign == ')')//if the right parenthesis, then pop all characters from the stack until the left parenthesis appears and add them to the output stream
		{
			if (!digit.empty())
			{
				push_back(digit);
				digit.clear();
			}
			if (!symbol.empty())
			{
				push_back(symbol);
				symbol.clear();
			}
			element = ')';
			push_back(element);
		}
		else if (is_operation_char(sign))//if operation
		{
			if (!digit.empty())
			{
				push_back(digit);
				digit.clear();
			}
			if (!symbol.empty())
			{
				push_back(symbol);
				symbol.clear();
			}
			element = sign;
			push_back(element);
		}
		else//if unknown symbol
		{
			cout << endl << "Uncorrected symbol: ..." << sign;
			error = true;
			break;
		}
		sign_last_last = sign_last;
		sign_last = sign;
	}
	if (error != true)
	{
		if (!symbol.empty())
		{
			push_back(symbol);
			symbol.clear();
		}
		if (!digit.empty())
		{
			push_back(digit);
			digit.clear();
		}
		print_to_console();
		error = false;
	}
	return error;
}

bool Calculator::check_for_error(bool error)
{
	string sign, sign_last=sign, sign_last_last=sign;
	int left_bracket=0, right_bracket=0;
		for (int i = 0; i < get_size(); i++)
		{
			sign = at(i);
			if (is_digit_string(sign))
			{
				if (functions(sign_last) != no_func)//error ...cos30...
				{
					cout << endl << "Enter the argument in parentheses: ..." << sign_last << sign;
					cout << " The argument must be in parentheses.";
					error = true;
					break;
				}
				else if (is_character_string(sign_last) && functions(sign_last) != no_func)//error ...a1...
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (sign_last == ")")//error ...)1...
				{
					cout << endl << "Uncorrected input: ...)" << sign;
					error = true;
					break;
				}
				else if (sign_last == ",")
				{
					if (functions(sign_last_last) != no_func || is_character_string(sign_last_last))//error...a,1 or cos,1
					{
						cout << endl << "Uncorrected input: ..." << sign_last_last << sign_last << sign;
						error = true;
						break;
					}
				}
			}
			else if (functions(sign)!=no_func )
			{
				if (sign_last == ")")//error ...)à...
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (is_digit_string(sign_last) || is_character_string(sign_last))//error...1cos or xcos
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (sign_last == ",")//error...,cos
				{
					cout << endl << "Uncorrected input: ..." << sign_last_last << sign_last << sign;
					error = true;
					break;
				}
			}
			else if (is_character_string(sign))//error...x
			{
				cout << endl << "Error. Unknown symbol: ..." << sign << endl;
				error = true;
				break;
			}
			else if (is_operation_string(sign))
			{
				if (is_operation_string(sign_last))//error...+-
				{
					cout << endl << "Error. Unknown symbol: ..." << sign_last << sign << endl;
					error = true;
					break;
				}
				if (sign !="&" && sign_last=="(")//error...(+
				{
					cout << endl << "Error. Unknown symbol: ..." << sign_last << sign << endl;
					error = true;
					break;
				}
			}
			else if (sign == "(")
			{
				left_bracket++;
				if (sign_last == ")")
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (is_digit_string(sign_last))//error...1(
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (is_character_string(sign_last) && functions(sign_last)==no_func)//error...x(
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
			}
			else if (sign == ")")
			{
				right_bracket++;
				if (right_bracket > left_bracket)//error...())
				{
					cout << endl << "There are more right parentheses than left parentheses";
					error = true;
					break;
				}
				else if (sign_last == "(")//error...()
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
				else if (is_operation_string(sign_last))//error...+)
				{
					cout << endl << "Uncorrected input: ..." << sign_last << sign;
					error = true;
					break;
				}
			}
			sign_last_last = sign_last;
			sign_last = sign;
		}
		if ((left_bracket > right_bracket) && error==false)//error...(()
		{
			cout << endl << "There are more left parentheses than right parentheses";
			error = true;
		}
	return error;
}

void Calculator::infix_to_postfix(Calculator* postfix)
{
	string sign, temp;
	for (int i = 0; i < get_size(); i++)
	{
		sign = at(i);
		if (sign == "(")
		{
			stack.push("(");
		}
		else if (sign == ")")
		{
			while ((temp = stack.pop()) != "(")
			{
				postfix->push_back(temp);
			}
		}
		else if (is_operation_string(sign))
		{
			while (stack.isEmpty() == 0 && prior(sign) <= prior(stack.top()))
			{
				temp = stack.pop();
				postfix->push_back(temp);
			}
			stack.push(sign);
		}
		else if (functions(sign) != no_func)
		{
			if (functions(sign) == PI)
			{
				postfix->push_back("3,14159");
			}
			else if (functions(sign) == E)
			{
				postfix->push_back("2,71828");
			}
			else
			{
				while (stack.isEmpty() == 0 && 5 <= prior(stack.top()))
				{
					temp = stack.pop();
					postfix->push_back(temp);
				}
				stack.push(sign);
			}
		}
		else
		{
			while (stack.isEmpty() == 0 && prior(sign) <= prior(stack.top()))
			{
				temp = stack.pop();
				postfix->push_back(temp);
			}
			postfix->push_back(sign);
		}
	}
	while (stack.isEmpty() != 1)
	{
		temp = stack.pop();
		postfix->push_back(temp);
	}
}

void Calculator::print_posfix()
{
	for (int i = 0; i < get_size(); i++)
	{
		cout << at(i) << " ";
	}
}

double Calculator::count_postfix()
{
	string sign, temp, sign_last;
	double result, oper1, oper2, digit;
	bool zero=false;
	for (int i=0; i<get_size(); i++)
	{
		sign = at(i);
		if (is_operation_string(sign) )
		{
			if (sign == "&")
			{
				digit = count.pop();
				digit = unary_minus(digit);
				count.push(digit);
			}
			else
			{
				oper1 = count.pop();
				oper2 = count.pop();
				if (sign == "/" && oper1 == 0)
				{
					cout << endl << "Can not be divided by zero!";
					zero = true;
				}
				else CountOperations(sign, oper1, oper2);
			}
		}
		else if (functions(sign) != no_func)
		{
			digit = CountFuncions(functions(sign), count.pop());
			count.push(digit);
		}
		else
		{
			digit = atof(sign.c_str());
			count.push(digit);
			
		}
		sign_last = sign;
	}
	if (zero!=true)
	{
		result = count.pop();
		return result;
	}
	return 0;
}



