#pragma once
#include"Node.h"
#include<iostream>
#include<string>
#include<vector>
struct T_I {
	Token *token;
	int sm;
	int p;
};
class Generate
{
public:

	Generate(Node * r);
	void move_tree(Node *tree,int level);
	void move_tree_procedure(Node * tree);
	void move_tree_program(Node * tree);
	void declaration_list(Node * tree);
	void declaration(Node * tree);
	void identifier_list(Node * tree);
	void atribute_list(Node* tree);
	void statements_list(Node * tree);
	void statements(Node * tree);
	void atr(std::string str);
	void if_stmt(Node * tree);
	std::string expression(Node * tree);
	std::string compare_operator(Node * tree);
	
private:
	int iden_attrib=8;//зм≥щенн€ у стек
	int int_atr = 0;//к≥льк≥сть атрибут≥в
	int int_iden = 0;//к≥льк≥сть ≥дентиф≥катор≥в
	int i = 1;//дл€ власних л≥ч≥льник≥в
	Node *root;
	std::vector<T_I> identifier;//таблиц€ ≥дентиф≥катор≥в 
};