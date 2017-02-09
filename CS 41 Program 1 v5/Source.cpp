/*
	Dylan Tey
	dylantey@gmail.com
	Reverse Polish Notation Calculator
*/

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class node
{
public:
	node();
	void push(float x);
	float pop();
	void print();
	bool isEmpty()
	{
		return top == 0;
	}
	
private:
	float data;
	node* top;
	node* link;
};

node::node()
{
	link = NULL;
	top = NULL;
}

void node::push(float x)
{
	node* temp = new node;
	temp->data = x;
	temp->link = top;
	top = temp;
}

float node::pop()
{
	if (isEmpty())
	{}
	else
	{
		node *temp = top->link;

		float element = top->data;
		delete top;
		top = temp;

		return element;
	}
}

void node::print()
{
	//cout << "Solution is " << top->data << endl;
	cout << "= " << top->data << endl;
}

bool isOperator(const string& input)
{
	if (input == "+" || input == "-" || input == "*" || input == "/")
	{
		return true;
	}
	else
	{
		return false;
	}
}

//This function tells the operators what to do with the values.
void calc(const string& input, node& stack)
{
	float n1, n2;
	bool errorZero = false;

	if (stack.isEmpty())
	{
		cout << "Error: Too many operators" << endl;
		n2 = stack.pop(); //FILO
	}
	else
	{
		n2 = stack.pop(); //FILO 
	}

	if (stack.isEmpty())
	{
		cout << "Error: Too many operators" << endl;
		n1 = stack.pop();
	}
	else
	{
		n1 = stack.pop();
	}


	
	if (input == "+")
	{
		stack.push(n1 + n2);
	}
	else if (input == "-")
	{
		stack.push(n1 - n2);
	}
	else if (input == "*")
	{
		stack.push(n1 * n2);
	}
	else if (input == "/")
	{
		if (n2 == 0)
		{
			errorZero = true;
		}
		else
		{
			stack.push(n1 / n2);
		}
	}

	if (errorZero)
	{
		cout << "Error: Division by zero" << endl;
	}
	else
	{
		stack.print();
	}
}

int main()
{
	node stack;
	string token;
	
	cout << "Calculator: (Enter 0 to end)" << endl;

	while (true)
	{
		string line;
		int num = 0;

		getline(cin, line);
		string temp = "", word[100];
		
		// store input into array
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ')
			{
				word[num] = "";
				word[num] = word[num] + temp;

				temp = "";

				num += 1;
			}
			else if (i == line.length() - 1)
			{
				temp = temp + line[i];
				word[num] = "";
				word[num] += temp;

				temp = "";

				num += 1;
			}
			else
			{
				temp += line[i];
			}
		}
		
		// reset number and operator counter
		int numberCounter = 0;
		int operatorCounter = 0;

		// analyze whether it is a number or not
		for (int k = 0; k < num; k++)
		{
			istringstream iss(word[k]);

			float num1 = 0;

			if (!(iss >> num1).fail())
			{
				++numberCounter;
				stack.push(num1);	// if it's a number, push to stack
			}
			else if (word[k] == "+" || word[k] == "-" || word[k] == "*" ||
				word[k] == "/")
			{
				++operatorCounter;

				if (operatorCounter > (numberCounter - 1))
				{
					cout << "Error: Too many operators" << endl;
				}
				else
				{
					calc(word[k], stack);	// if it's a operator with NO ERROR,
											// push to stack
				}
			}
			else if (word[k] == "=")
			{
				// (num of operator == num of counter) for calc to work
				if (operatorCounter < (numberCounter - 1))
				{
					cout << "Error: Too many operands" << endl;
				}
			}
		}

		if (line == "0") // if 0 is entered, stop program
		{
			cout << "Program ended" << endl;
			system("PAUSE");
			return 0;
		}
	}
	system("PAUSE");
}

/*
	Calculator: (Enter 0 to end)
	10 15 + =
	= 25
	10 15 - =
	= -5
	2.5 3.5 + =
	= 6
	10 0 / =
	Error: Division by zero
	10 20 * / =
	= 200
	Error: Too many operators
	12 20 30 / =
	= 0.666667
	Error: Too many operands
	-10 -30 - =
	= 20
	100 10 50 25 / * - -2 / =
	= 2
	= 20
	= 80
	= -40
*/