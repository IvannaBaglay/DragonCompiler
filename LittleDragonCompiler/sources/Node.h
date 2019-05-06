 #pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include "Token.h"
class Node
{
public:
	Node(void);
	virtual ~Node(void);
	std::vector<Node*> son_tree;
	void error(std::string str);
	int newLabel();
	void emitLabel(int i);
	void emit(std::string str);
	Node* addNode(std::string name, Node *tree, int num_son_tree, int l, int c,Token* x=NULL);
	void treeprint(Node *tree,int level);
	int lexerLine;
	int column;
	static int label;
	Token* token;
	std::string name_node;
};


