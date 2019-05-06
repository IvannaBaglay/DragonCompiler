#include "Parser.h"
#include "ExternGlobal.h"

std::vector<std::string> error_list = {
	"must be PROGRAM",//0
	"must be ;",//1
	"must be BEGIN",//2
	"must be END",//3
	"must be (",//4
	"must be )",//5
	"must be :",//6
	"must be ,",//7
	"must be .",	//8
	"must be BASIC",//9
	"must be ID",//10
	"must be PROCEDURE",//11
	"must be comparison_operator",//12
	"must be WHILE",//13
	"must be DO",//14
	"must be ENDWHILE"//15
};
bool flag_s = true;
Parser::Parser(Lexer* l): p_lex(l), look(NULL), used(0)
{
	move();
}
Parser::~Parser(void)
{
	
}
void Parser::move()
{
	look = p_lex->scan();
}/*
 void Parser::move()
//test
{
	std::cout << "move\n";
	look = p_lex->scan();
	while (look != NULL)
	{
		std::cout << look->t_tag << "\t" << *look << std::endl;
		look = p_lex->scan();	
	}
}*/
void Parser::error(std::string msg)
{
	std::cout<<"Parser:Error (line: "<<p_lex->line<<",column: "<<p_lex->column<<") " <<msg<<std::endl;
	system("pause");
	exit(1);
}
void Parser::match(int t,int int_err)
{
	//std::cout << error_list[0];
	if (look != NULL)
	{
		if ((int)look->t_tag == t)
		{
			std::cout << look->t_tag << "\t" << *look << std::endl;
			move();
		}
		else
			error(error_list[int_err]);		
	}
	else
	{
		if (flag_s)
			error("must be ;");
		else
			error("must be .");
	}
	
}
Node*  Parser::signal_program(Node *tree)
{
	
	tree = tree->addNode("signal_program", tree,1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=program(tree->son_tree[0]);
	return tree;
}
Node* Parser::program(Node *tree)
{
	
	if (look->t_tag == PROGRAM)
	{
		flag_s = false;
		tree = tree->addNode("program", tree, 5, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = program_t(tree->son_tree[0]);
		match(PROGRAM,0);
		tree->son_tree[1]=procedure_identifier(tree->son_tree[1]);
		tree->son_tree[2] = P_S(tree->son_tree[2]);
		match(';',1);
		tree->son_tree[3]=block(tree->son_tree[3]);
		tree->son_tree[4] = P_P(tree->son_tree[4]);
		match('.',8);
	}	
	else if (look->t_tag == PROCEDURE)
	{
		tree = tree->addNode("program", tree, 6, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = procedure_t(tree->son_tree[0]);
		match(PROCEDURE,11);
		tree->son_tree[1]=procedure_identifier(tree->son_tree[1]);
		tree->son_tree[2]=parametrs_list(tree->son_tree[2]);
		tree->son_tree[3] = P_S(tree->son_tree[3]);
		match(';',1);
		tree->son_tree[4]=block(tree->son_tree[4]);
		tree->son_tree[5] = P_S(tree->son_tree[5]);
		match(';',1);
	}
	else
		error("must be PROCEDURE OR PROGRAM");
	return tree;
}

Node* Parser::program_t(Node *tree)
{
	
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node* Parser::while_t(Node *tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}

Node* Parser::endwhile_t(Node *tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}

Node* Parser::do_t(Node *tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}

Node* Parser::procedure_t(Node *tree)
{
	
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}

Node * Parser::P_S(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::P_C(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::P_P(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::P_sk1(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::P_sk2(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::P_PP(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::GE_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::LE_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::L_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::G_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::IF_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::THEN_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::ELSE_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node * Parser::ENDIF_t(Node* tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}

Node* Parser::block(Node *tree)
{
	tree=tree->addNode("block", tree,3, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = block_begin(tree->son_tree[0]);
	match(BEGIN,2);
	
	tree->son_tree[1]= statements_list(tree->son_tree[1]);
	tree->son_tree[2] = block_end(tree->son_tree[2]);
	match(END,3);
	return tree;
}
Node* Parser::block_begin(Node* tree)
{
	tree = tree->addNode("BEGIN", tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node* Parser::statements_list(Node* tree)
{
	
	if (look->t_tag == END)
	{
		tree = tree->addNode("statements_list", tree, 1, p_lex->line, p_lex->column, NULL);

		tree->son_tree[0] = empty(tree->son_tree[0]);
	}
	else if (look->t_tag == ENDWHILE)
	{
		tree = tree->addNode("statements_list", tree, 1, p_lex->line, p_lex->column, NULL);

		tree->son_tree[0] = empty(tree->son_tree[0]);
	}
	else if (look->t_tag==WHILE)
	{
		tree = tree->addNode("statements_list", tree, 2, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = statement(tree->son_tree[0]);
		tree->son_tree[1] = statements_list(tree->son_tree[1]);
	}
	else if (look->t_tag == IF)
	{
		tree = tree->addNode("statements_list", tree, 2, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = if_stmt(tree->son_tree[0]);
		tree->son_tree[1] = statements_list(tree->son_tree[1]);
	}
	else
	{
		tree = tree->addNode("statements_list", tree, 1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = empty(tree->son_tree[0]);
	}

	return tree;

}
Node* Parser::statement(Node* tree)
{
	tree = tree->addNode("statement", tree, 6, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = while_t(tree->son_tree[0]);
	match(WHILE,13);
	tree->son_tree[1] = conditional_expression(tree->son_tree[1]);
	tree->son_tree[2] = do_t(tree->son_tree[2]);
	match(DO, 14);
	tree->son_tree[3] = statements_list(tree->son_tree[3]);
	tree->son_tree[4] = endwhile_t(tree->son_tree[4]);
	match(ENDWHILE,15);
	tree->son_tree[5] = P_S(tree->son_tree[5]);
	match(';',1);
	return tree;
}

Node* Parser::conditional_expression(Node * tree)
{
	tree = tree->addNode("conditional_expression", tree, 2, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=logical_summand(tree->son_tree[0]);
	tree->son_tree[1] = logical(tree->son_tree[1]);
	return tree;
}

Node * Parser::logical_summand(Node *tree)
{
	tree = tree->addNode("logical_summand", tree, 2, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = logical_multiplier(tree->son_tree[0]);
	tree->son_tree[1] = logical_multiplier_list(tree->son_tree[1]);
	return tree;
}
Node * Parser::logical(Node *tree)
{
	tree = tree->addNode("logical", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = empty(tree->son_tree[0]);
	return tree;
}
Node * Parser::logical_multiplier(Node *tree)
{
	tree = tree->addNode("logical_multiplier", tree, 3, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = expression(tree->son_tree[0]);
	tree->son_tree[1] = comparison_operator(tree->son_tree[1]);
	tree->son_tree[2] = expression(tree->son_tree[2]);
	return tree;
}
Node * Parser::logical_multiplier_list(Node *tree)
{
	tree = tree->addNode("logical_multiplier_list", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = empty(tree->son_tree[0]);
	return tree;
}
Node * Parser::expression(Node *tree)
{
	tree = tree->addNode("expression", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = variable(tree->son_tree[0]);
	return tree;
}
Node * Parser::comparison_operator(Node *tree)
{
	tree = tree->addNode("comparison_operator", tree, 1, p_lex->line, p_lex->column, NULL);
	switch (look->t_tag)
	{
	case GE: tree->son_tree[0] = GE_t(tree->son_tree[0]);  match(GE, 12); break;
	case LE:tree->son_tree[0] = LE_t(tree->son_tree[0]); match(LE,12); break;
	default:
		break;
	}
	if ((int)look->t_tag == 60)
	{
		tree->son_tree[0] = L_t(tree->son_tree[0]);
		match('<', 12);
	}
	if ((int)look->t_tag == 62)
	{
		tree->son_tree[0] = G_t(tree->son_tree[0]);
		match('>', 12);
	}
	return tree;
}
Node * Parser::variable(Node *tree)
{
	tree = tree->addNode("variable", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = variable_identifier(tree->son_tree[0]);
	return tree;
}
Node* Parser::block_end(Node* tree)
{
	tree = tree->addNode("END", tree, 0, p_lex->line, p_lex->column, look);
	return tree;
}
Node* Parser::parametrs_list(Node *tree)
{
	tree=tree->addNode("parametrs_list", tree,1, p_lex->line, p_lex->column, NULL);
	if (look->t_tag == '(')
	{
		tree = tree->addNode("parametrs_list", tree, 3, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = P_sk1(tree->son_tree[0]);
		match('(',4);
		tree->son_tree[1] = declaration_list(tree->son_tree[1]);	
		tree->son_tree[2] = P_sk2(tree->son_tree[2]);
		match(')',5);
	}
	else
	{
		tree = tree->addNode("parametrs_list", tree, 1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = empty(tree->son_tree[0]);
	}
		
	return tree;
}
Node* Parser::declaration_list(Node *tree) {
	if (look->t_tag!=')')
	{
		tree = tree->addNode("declaration_list", tree, 2, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = declaration(tree->son_tree[0]);
		tree->son_tree[1]=declaration_list(tree->son_tree[1]);
	}
	else
	{
		tree = tree->addNode("declaration_list", tree,1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = empty(tree->son_tree[0]);
	}
	return tree;
}
Node* Parser::declaration(Node *tree)
{
	tree=tree->addNode("declaration", tree,6, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=variable_identifier(tree->son_tree[0]);
	tree->son_tree[1]=identifier_list(tree->son_tree[1]);
	tree->son_tree[2] = P_PP(tree->son_tree[2]);
	match(':',6);
	tree->son_tree[3]=attribute(tree->son_tree[3]);
	tree->son_tree[4]=attribute_list(tree->son_tree[4]);
	tree->son_tree[5] = P_S(tree->son_tree[5]);
	match(';',1);
	return tree;
}
Node* Parser::attribute(Node *tree)
{
	tree=tree->addNode("attribute", tree,1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = BASIC_t(tree->son_tree[0]);
	return tree;
}
Node* Parser::BASIC_t(Node *tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	match(BASIC, 9);
	return tree;
}
Node* Parser::attribute_list(Node *tree)
{
	if (look->t_tag == BASIC)
	{
		tree = tree->addNode("attribute_list", tree, 2, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = attribute(tree->son_tree[0]);
		tree->son_tree[1] = attribute_list(tree->son_tree[1]);
	}
	else
	{

		tree = tree->addNode("attribute_list", tree, 1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = empty(tree->son_tree[0]);
	}
	return tree;
}
Node* Parser::procedure_identifier(Node *tree)
{
	tree=tree->addNode("procedure_identifier", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=identifier(tree->son_tree[0]);
	return tree;
}
Node* Parser::identifier(Node *tree)
{
	tree=tree->addNode("identifier", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0] = ID_t(tree->son_tree[0]);
	return tree;
}
Node* Parser::ID_t(Node *tree)
{
	tree = tree->addNode((*look).toString(), tree, 0, p_lex->line, p_lex->column, look);
	match(ID, 10);
	return tree;
}
Node* Parser::identifier_list(Node *tree)
{
	if (look->t_tag==',')
	{
		tree = tree->addNode("identifier_list", tree, 3, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0] = P_C(tree->son_tree[0]);
		match(',',7);
		
		tree->son_tree[1] = variable_identifier(tree->son_tree[1]);
		tree->son_tree[2]=identifier_list(tree->son_tree[2]);
	}
	else
	{
		tree = tree->addNode("identifier_list", tree, 1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0]=empty(tree->son_tree[0]);
	}
	return tree;
}
Node* Parser::empty(Node *tree)
{
	tree=tree->addNode("empty", tree, 0, p_lex->line, p_lex->column, NULL);
	return tree;
}
Node* Parser::variable_identifier(Node *tree)
{
	tree=tree->addNode("variable_identifier", tree, 1, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=identifier(tree->son_tree[0]);
	return tree;
}
Node* Parser::if_stmt(Node * tree)
{
	tree = tree->addNode("if_stmt", tree, 5, p_lex->line, p_lex->column, NULL);
	tree->son_tree[0]=IF_t(tree->son_tree[0]);
	match(IF, 1);
	tree->son_tree[1]=variable_identifier(tree->son_tree[1]);
	tree->son_tree[2]=THEN_t(tree->son_tree[2]);
	match(THEN, 1);
	tree->son_tree[3]=statements_list(tree->son_tree[3]);
	tree->son_tree[4]=if_tail(tree->son_tree[4]);
	return tree;
}
Node* Parser::if_tail(Node * tree)
{
	if (look->t_tag == ELSE)
	{
		tree = tree->addNode("if_tail", tree, 3, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0]=ELSE_t(tree->son_tree[0]);
		match(ELSE, 1);
		tree->son_tree[1]=statements_list(tree->son_tree[1]);
		tree->son_tree[2]=ENDIF_t(tree->son_tree[2]);
		match(ENDIF, 1);

	}
	if (look->t_tag == ENDIF)
	{
		tree = tree->addNode("if_tail", tree, 1, p_lex->line, p_lex->column, NULL);
		tree->son_tree[0]=ENDIF_t(tree->son_tree[0]);
		match(ENDIF, 1);
	}

	return tree;
}