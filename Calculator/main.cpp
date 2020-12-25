#include "Calculator.h"

int main()
{
	Calculator calc;
	Calculator postfix;
	string infix;
	bool error=false;
	double result;
	cout << "Enter expression without spaces: ";
	cin >> infix;
	cout << "Introdused: "; 
	error = calc.check_for_error(calc.processing_string(infix, error));
	if (error== false)
	{
		cout << endl << "Postfix form: ";
		calc.infix_to_postfix(&postfix);
		postfix.print_posfix();
		cout << endl << "Calculated value: ";
		result = postfix.count_postfix();
		cout << result;
	}
}