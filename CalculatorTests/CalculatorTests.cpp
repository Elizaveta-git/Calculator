#include "pch.h"
#include "CppUnitTest.h"
#include "..\Calculator\Calculator.h"
#include "..\Calculator\Calculator.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
	TEST_CLASS(CalculatorTests)
	{
	public:
		Calculator calc;
		Calculator postfix;
		string infix, sign;
		bool error= false;
		
		//////PROCESSING//STRING//////
		TEST_METHOD(processing_string_NOTerror)
		{
			infix = "3*(-2+7.1)-cos(pi)";
			error=calc.processing_string(infix, error);
			Assert::IsFalse(error);
		}

		TEST_METHOD(processing_string_ErrorDoublePoint)
		{
			infix = "3*(-2+7..1)-cos(pi)";
			error = calc.processing_string(infix, error);
			Assert::IsTrue(error);
		}

		TEST_METHOD(processing_string_UnknownSymbol)
		{
			infix = "3%(-2+7..1)-cos(pi)";
			error = calc.processing_string(infix, error);
			Assert::IsTrue(error);
		}

		TEST_METHOD(processing_string_CORRECTentry)
		{
			infix = "3*(-2+7.1)-cos(pi)";
			error = calc.processing_string(infix, error);
			Assert::IsFalse(error);
			Assert::AreEqual(calc.at(0), sign = "3"); //3
			Assert::AreEqual(calc.at(1), sign = "*"); //3 *
			Assert::AreEqual(calc.at(3), sign = "&"); //3 * ( &
			Assert::AreEqual(calc.at(6), sign = "7,1");
			Assert::AreEqual(calc.at(9), sign = "cos");
			Assert::AreEqual(calc.at(11), sign = "pi");
		}

		//////CHECK//FOR//ERROR//////
		TEST_METHOD(check_for_error_cos1)
		{
			infix = "3*(-2+7.1)-cos32";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsTrue(error);
		}
		TEST_METHOD(check_for_error_x1)
		{
			infix = "3*(-2+7.1)-x1";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsTrue(error);
		}
		TEST_METHOD(check_for_error_xcos)
		{
			infix = "3*(-2+7.1)-xcos(9)";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsTrue(error);
		}
		TEST_METHOD(check_for_error_doubleOperator)
		{
			infix = "3*(-2+7.1)-+1";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsTrue(error);
		}
		TEST_METHOD(check_for_error_unequal_brackets)
		{
			infix = "3*(-2+7.1)-x1)";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsTrue(error);
		}
		//////INFIX//TO//POSTFIX//////
		TEST_METHOD(infix_to_postfix)
		{
			infix = "3*(-2+7.1)-cos(pi)";
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(postfix.at(0), sign = "3"); //3
			Assert::AreEqual(postfix.at(1), sign = "2"); //3|2
			Assert::AreEqual(postfix.at(2), sign = "&"); //3|2|&
			Assert::AreEqual(postfix.at(3), sign = "7,1"); //3|2|&|7,1 
			Assert::AreEqual(postfix.at(4), sign = "+"); //3|2|&|7,1|+
			Assert::AreEqual(postfix.at(5), sign = "*"); //3|2|&|7,1|+|*
			Assert::AreEqual(postfix.at(6), sign = "3,14159"); //3|2|&|7,1|+|*|3,14159
			Assert::AreEqual(postfix.at(7), sign = "cos"); //3|2|&|7,1|+|*|3,14159|cos
			Assert::AreEqual(postfix.at(8), sign = "-"); //3|2|&|7,1|+|*|3,14159|cos|-
		}
		//////COUNT//POSTFIX//////
		TEST_METHOD(count_postfix_1)
		{
			infix = "3*4^2+(-2+6*7)";
			double result = 3.0 * pow(4,2) +(-2 + 6 * 7);
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(postfix.count_postfix(), result);
		}
		TEST_METHOD(count_postfix_2)
		{
			infix = "ln(exp(e))-tg(pi)";
			double result =log(exp(2.71828)) - tan(3.14159);
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(postfix.count_postfix(), result);
		}
		TEST_METHOD(count_postfix_3)
		{
			infix = "abs(-ln(7))";
			double result = abs(-log(7));
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(result, abs(postfix.count_postfix()));
		}
		TEST_METHOD(count_postfix_4)
		{
			infix = "3*(-2+7.1)-cos(pi)";
			double result = 3*(-2+7.1)-cos(3.14159);
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(postfix.count_postfix(), result);
		}
		TEST_METHOD(count_postfix_5)
		{
			infix = "(((40+ln(7.6))*34/9)-98*(-8))^sin(pi)";
			double result = pow(((40 + log(7.6)) * 34 / 9) - 98 * (-8), sin(3.14159));
			error = calc.check_for_error(calc.processing_string(infix, error));
			Assert::IsFalse(error);
			calc.infix_to_postfix(&postfix);
			Assert::AreEqual(postfix.count_postfix(), result);
		}
	};
}
