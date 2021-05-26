#pragma once
#include "Node.h"
#include <fstream>

class Tree
{
private:
	Node* head = nullptr;
public:
	Tree(string str);
	Tree();
	~Tree();

	int calculate();
	bool checkInit() {
		if (head == nullptr) return false;
		else return true;
	}

	void print();
	void input(string str);
	bool checkInput(string in);
	bool checkInputSym(char sym);

	bool ReadFile(string _path);
	bool WriteFile(string _path);
}; 

Tree::Tree(string str)
{
	head = new Node(str);
}

inline Tree::Tree()
{
	head = nullptr;
}

Tree::~Tree()
{
	if (head)
	{
		head->free_tree(head);
	}
}

int Tree::calculate()
{
	if (!head)
	{
		throw logic_error("Tree is empty");
	}
	return head->calculate(head);
}

inline void Tree::print()
{
	string res;
	if (!head)
	{
		throw logic_error("Tree is empty");
	}
	head->print_tree(head, res);
}

inline void Tree::input(string str)
{
	if(head == nullptr)
		head = new Node(str);
	else
	{
		head->free_tree(head);
		head = new Node(str);
	}
}

inline bool Tree::checkInput(string in)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (!checkInputSym(in[i]))
			return false;
	}
	return true;
}

inline bool Tree::checkInputSym(char sym)
{
	if (sym > 46 && sym < 58) return true;
	if (sym == 42 || sym == 43 || sym == 45) return true;

	return false;
}

inline bool Tree::ReadFile(string _path)
{
	std::ifstream file(_path, std::ios::in);
	if (file.is_open())
	{
		std::string buf;
		std::getline(file, buf);
		if (buf.size() > 0)
		{
			if (checkInput(buf))
			{
				input(buf);
			}
			else
			{
				cout << "File is contains invalid character!\n"; 
				return false;
			}
		}
		else
		{ 
			cout << "File is empty!\n";
			file.close();
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

inline bool Tree::WriteFile(string _path)
{
	string res = "";
	ofstream file(_path, std::ios::trunc);
	if (file.is_open())
	{
		head->print_tree(head, res);
		file << res;
	}
	else
	{
		return false;
	}
	file.close();
	return true;
}

