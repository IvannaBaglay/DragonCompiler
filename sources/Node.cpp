#include "Node.h"
#include "Lexer.h"
#include "ExternGlobal.h"

int Node::label = 0;

Node::Node(void)
{

}

Node::~Node(void)
{

}

void Node::error(std::string str) 
{
	std::cerr<<"Near Line "<<lexerLine<<": "<<str<<std::endl;
	intermediaRepresentStream << "Near Line " << lexerLine << ": " << str << std::endl;
}

int Node::newLabel() 
{
	return ++label;
}

void Node::emitLabel(int i) 
{
	std::cout<<"L"<<i<<":";
	intermediaRepresentStream << "L" << i << ":";
}

void Node::emit(std::string str) 
{
	std::cout<<"\t"<<str<<std::endl;
	intermediaRepresentStream << "\t" << str << std::endl;
}
Node* Node::addNode(std::string name, Node* tree,int num_son_tree, int l, int c,Token *x)
{
	

		tree = new Node;
		tree->lexerLine = l;
		tree->column = c;
		tree->token = x;
		tree->name_node = name;
		while (num_son_tree)
		{
			tree->son_tree.push_back(NULL);
			num_son_tree--;
		}
		return tree;
}
void Node::treeprint(Node* tree, int level)
{
	if (tree != NULL) {
		for (int i = 0; i < level; i++)
			std::cout << ".";

		
		if (tree->name_node == "PROCEDURE")
			if (tree->token->t_tag == -572662307)
				tree->token->t_tag = PROCEDURE;		

		if (tree->token != nullptr)
			std::cout << (tree->token->t_tag) << "\t";		
		std::cout << tree->name_node << "\n";
		level++;
		for (size_t i = 0; i < tree->son_tree.size(); i++)
			treeprint(tree->son_tree[i],level);
	}
}