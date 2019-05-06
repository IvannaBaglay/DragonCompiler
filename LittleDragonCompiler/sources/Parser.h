#pragma once
#include "Lexer.h"
#include "Token.h"
#include "DataType.h"
#include <string>
#include"Node.h"
class Parser
{
public:
	Parser(Lexer* l);
	virtual ~Parser(void);
	void error(std::string msg);
	void match(int t,int int_err);
	Node* signal_program(Node *tree);
private:
	void move();
	Node* program(Node *tree);
	Node* block(Node *tree);
	Node* parametrs_list(Node *tree);
	Node* procedure_identifier(Node *tree);
	Node* identifier(Node *tree);
	Node* identifier_list(Node *tree);
	Node* empty(Node *tree);
	Node* declaration_list(Node *tree);
	Node* declaration(Node *tree);
	Node* variable_identifier(Node *tree);
	Node * block_begin(Node* tree);
	Node * block_end(Node* tree);
	Node* attribute_list(Node *tree);
	Node* attribute(Node *tree);
	Node * program_t(Node *tree);
	Node * procedure_t(Node *tree);
	Node * if_stmt(Node *tree);
	//Node * stmt_list(Node *tree);
	Node * if_tail(Node *tree);
	Node * P_P(Node *tree);
	Node * P_S(Node *tree);
	Node * P_C(Node *tree);
	Node * P_sk1(Node *tree);
	Node * P_sk2(Node *tree);
	Node * P_PP(Node *tree);
	Node * GE_t(Node *tree);
	Node * IF_t(Node *tree);
	Node * THEN_t(Node *tree);
	Node * ELSE_t(Node *tree);
	Node * ENDIF_t(Node *tree);

	Node * LE_t(Node *tree);
	Node * ID_t(Node *tree);
	Node * BASIC_t(Node *tree);
	Node * L_t(Node *tree);
	Node * G_t(Node *tree);
	Node * statements_list(Node* tree);
	Node * statement(Node *tree);
	Node * while_t(Node * tree);
	Node * do_t(Node * tree);
	Node * endwhile_t(Node * tree);
	Node * conditional_expression(Node * tree);
	Node * logical(Node * tree);
	Node * logical_summand(Node * tree);
	Node * logical_multiplier(Node * tree);
	Node * logical_multiplier_list(Node * tree);
	Node * expression(Node * tree);
	Node * comparison_operator(Node * tree);
	Node * variable(Node *tree);
	Lexer* p_lex;
	Token* look;
	int used;
};

