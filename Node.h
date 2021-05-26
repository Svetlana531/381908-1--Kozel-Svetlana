#pragma once
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

static map<char, int> priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

class Node
{
private:
	int val;
	char operation = '\0';
	Node* left = nullptr;
	Node* right = nullptr;
public:
	Node(const string& str);
	int calculate(Node* n);
	void free_tree(Node* n);
	void print_tree(Node* n, string& res);
private:
	int find_pos_of_min_priority(string str)const;
	bool is_operator(const char& ch)const;
	string divide_str(int left_pos, int right_pos, const string& str)const;
};

Node::Node(const string& str)
{
	if (str.size() == 1)
	{
		val = stoi(str);
		return;
	}
	int operat_pos = find_pos_of_min_priority(str);
	operation = str[operat_pos];
	string str_left = divide_str(0, operat_pos, str);
	string str_right = divide_str(operat_pos + 1, str.size(), str);
	left = new Node(str_left);
	right = new Node(str_right);
}

int Node::calculate(Node* n)
{
	if (n->operation == '\0')
	{
		return n->val;
	}
	int res = 0;
	switch (n->operation)
	{
	case'+':
		res = calculate(n->left) + calculate(n->right);
		break;
	case'-':
		res = calculate(n->left) - calculate(n->right);
		break;
	case'*':
		res = calculate(n->left) * calculate(n->right);
		break;
	case'/':
		res = calculate(n->left) / calculate(n->right);
		break;
	}
	return res;
}

bool Node::is_operator(const char& ch)const
{
	string operators = "+-*/";
	for (int i = 0; i < operators.size(); i++)
	{
		if (operators[i] == ch)
		{
			return true;
		}
	}
	return false;
}
string Node::divide_str(int left_pos, int right_pos, const string& str)const
{
 	string res = "";
	for (int i = left_pos; i < right_pos; i++)
	{
		res += str[i];
	}
	return res;
}
void Node::free_tree(Node* n)
{
	if (n->left)
	{
		free_tree(n->left);
	}
	if (n->right)
	{
		free_tree(n->right);
	}
	delete n;
}

inline void Node::print_tree(Node* n, string& res)
{
	if (n->left)
	{
		print_tree(n->left, res);
	}

	if (n->val == 0)
	{
		cout << n->operation;
		res += n->operation;
	}
	else
	{
		cout << n->val;
		res += to_string(n->val);
	}
	if (n->right)
	{
		print_tree(n->right, res);
	}
}

int Node::find_pos_of_min_priority(string str)const
{
	int pos = -1;
	int min_priority = 5;
	for (int i = 0; i < str.size(); i++)
	{
		if (is_operator(str[i]))
		{
			if (priority[str[i]] < min_priority)
			{
				pos = i;
				min_priority = priority[str[i]];
			}
		}
	}
	if (pos == -1)
	{
		throw logic_error("Str doesn't have operator");
	}
	return pos;
}