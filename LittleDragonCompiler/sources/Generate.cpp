#include"Generate.h"
#include<iostream>
#include"DataType.h"
#include<string>
#include"ExternGlobal.h"
Generate::Generate(Node *r) :root(r)
{
	//std::cout << root->name_node;
	move_tree(root,0);
	
}

void Generate::move_tree(Node *tree, int level){
		if (tree != NULL) { //Пока не встретится пустой узел
			//std::cout << "move-tree\n";
			//std::cout << "tree " << tree->name_node<< std::endl;
			//std::cout << *(tree->son_tree[0]->son_tree[0]->token);
			
			if (tree->son_tree[0]->son_tree[0]->token!=NULL)
			{
				if (*(tree->son_tree[0]->son_tree[0]->token) == PROGRAM)
				{
					move_tree_program(tree->son_tree[0]);
				}
				if (*(tree->son_tree[0]->son_tree[0]->token) == PROCEDURE)
				{
					move_tree_procedure(tree->son_tree[0]);
				}
			}
			
		}
}
void Generate::move_tree_program(Node* tree)
{
	//std::cout << "move_tree_program\n";

	//std::cout << "tree " << tree->name_node<< std::endl;
	//std::cout << *(tree->son_tree[0]->token);
	std::cout<<";"<<*(tree->son_tree[1]->son_tree[0]->son_tree[0]->token);
	intermediaRepresentStream <<";"<< *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token);
	intermediaRepresentStream << "code SEGMENT\n ASSUME cs:code\n";
	std::cout << "code SEGMENT\n ASSUME cs:code\n";
	intermediaRepresentStream << "\tbegin:";
	intermediaRepresentStream << "\tpush ebp\n";
	intermediaRepresentStream << "\tmov	ebp, esp\n";
	intermediaRepresentStream << "\txor	eax, eax\n";
	intermediaRepresentStream << "\tmov	esp, ebp\n";
	intermediaRepresentStream << "\tpop	ebp\n";
	statements_list(tree->son_tree[3]->son_tree[1]);
	std::cout << "\tbegin:";
	std::cout << "\tpush ebp\n";
	std::cout << "\tmov	ebp, esp\n";
	std::cout << "\txor	eax, eax\n";
	std::cout << "\tmov	esp, ebp\n";
	std::cout << "\tpop	ebp\n";
	intermediaRepresentStream << "\n\tmov ax, 4c00h\n\tint 21h\ncode ENDS\n\tend begin\n\n";
	std::cout << "\n\tmov ax, 4c00h\n\tint 21h\ncode ENDS\n\tend begin\n\n";
}
void Generate::move_tree_procedure(Node * tree)
{
	//std::cout << "move_tree_procedure\n";
	//std::cout << "tree " << tree->name_node<< std::endl;
	//std::cout << *(tree->son_tree[1]->son_tree[0]->token);
	
	intermediaRepresentStream << *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token) << "PROC" << std::endl;
	std::cout << *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token) << "PROC" <<std::endl;
	
	if (tree->son_tree[2]->son_tree[0]->name_node != "empty")
		declaration_list(tree->son_tree[2]->son_tree[1]);
	if (int_atr != int_iden)
	{
		std::cout << "Generate error: num attribute!=num identifier\n";
		system("pause");
		exit(1);
	}
	int j = 8;
	//записуємо вивід зі стеку
	intermediaRepresentStream << "push ebp \nmov ebp, esp\n";
	std::cout << "push ebp \nmov ebp, esp\n";
	for (int i = identifier.size() - 1; i >= 0; i--)
	{
		intermediaRepresentStream << "[ebp+" << j << "]" << ";" << *(identifier[i].token);
;
		std::cout << "[ebp+" << j << "]" << ";" << *(identifier[i].token);
		identifier[i].p = j;
		j += identifier[i].sm;

	} 
	statements_list(tree->son_tree[4]->son_tree[1]);
	intermediaRepresentStream << "ret\n";
	std::cout << "ret\n";
	intermediaRepresentStream << *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token) << "endp ";
	std::cout << *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token) << "endp ";
}
void Generate::declaration_list(Node * tree)
{
	//std::cout << "decl_list\n";
	//std::cout << "tree " << tree->name_node << std::endl;
	
	//std::cout << (tree->son_tree[2]->name_node);
	if (tree->son_tree[0]->name_node != "empty")
	{
		//std::cout << (tree->son_tree[0]->name_node)<<std::endl;
		//std::cout << (tree->son_tree[1]->name_node) << std::endl;
		declaration(tree->son_tree[0]);
		declaration_list(tree->son_tree[1]);
	}	
}
void Generate::declaration(Node * tree)
{
	//std::cout << "decl\n";
	//std::cout<<"tree " << tree->name_node << std::endl;
	for (std::vector<T_I>::iterator iter = identifier.begin(); iter != identifier.end(); iter++)
	{
		if (iter->token->toString() == tree->son_tree[0]->son_tree[0]->token->toString())
			{
				std::cout << "1";
				std::cout << "GENERATE ERROR redefinition "<<*(tree->son_tree[0]->son_tree[0]->token) <<"\n";
				system("pause");
				exit(1);
			}
	}
	//std::cout << *(tree->son_tree[0]->son_tree[0]->son_tree[0]->token);
	identifier.push_back({tree->son_tree[0]->son_tree[0]->son_tree[0]->token, 0});
	int_iden++;
	identifier_list(tree->son_tree[1]);	
	//std::cout << *(tree->son_tree[2]->token);
	//std::cout << *(tree->son_tree[3]->son_tree[0]->token);
	atr(tree->son_tree[3]->son_tree[0]->token->toString());
	atribute_list(tree->son_tree[4]);
}
void Generate::identifier_list(Node * tree)
{
	//std::cout << "identifier_list\n";
	//std::cout << "tree " << tree->name_node << std::endl;
	if (tree->son_tree[0]->name_node != "empty")
	{
		std::cout << "2";
		//std::cout << tree->son_tree[1]->name_node;
		//std::cout << tree->son_tree[1]->son_tree[0]->name_node;
		//std::cout << tree->son_tree[1]->son_tree[0]->son_tree[0]->token->toString();
		for (std::vector<T_I>::iterator iter = identifier.begin(); iter != identifier.end(); iter++)
		{
			//std::cout << *(iter->token);
			
			if (iter->token->toString() == tree->son_tree[1]->son_tree[0]->son_tree[0]->token->toString())
			{
				std::cout << "2";
				std::cout << "GENERATE ERROR redefinition"<<*(tree->son_tree[1]->son_tree[0]->son_tree[0]->token) <<"\n";
				system("pause");
				exit(1);
			}
		}
		//std::cout << *(tree->son_tree[1]->son_tree[0]->son_tree[0]->token);
		identifier.push_back({ tree->son_tree[1]->son_tree[0]->son_tree[0]->token, 0 });
		int_iden++;
		identifier_list(tree->son_tree[2]);
	}
}
void Generate::atribute_list(Node * tree)
{
	//std::cout << "atribute_list\n";
	//std::cout << "tree " << tree->name_node << std::endl;
	if (tree->son_tree[0]->name_node != "empty")
	{
		//std::cout << *(tree->son_tree[0]->son_tree[0]->token);
		atr(tree->son_tree[0]->son_tree[0]->token->toString());
		atribute_list(tree->son_tree[1]);
	}
}
void Generate::atr(std::string str)
{
	//std::cout << "atr\n";
	//std::cout << tree->name_node << std::endl;
	if (int_atr<=int_iden)
	{
		if (str == "INTEGER")
			identifier[int_atr].sm = 2;
		if (str == "FLOAT")
			identifier[int_atr].sm = 4;
		if (str == "BLOCKFLOAT")
			identifier[int_atr].sm = 4;
		if (str == "COMPLEX")
			identifier[int_atr].sm = 4;
		if (str == "EXT")
			identifier[int_atr].sm = 4;
		if (str == "SIGNAL")
			identifier[int_atr].sm = 1;
		int_atr++;
	}
	else
	{
		std::cout << "Code Generator: Error num attribute!=num identifier";
		system("pause");
	}
}
void Generate::statements_list(Node * tree)
{
	if (tree->son_tree[0]->name_node != "empty")
	{
		if (tree->son_tree[0]->name_node == "if_stmt")
		{
			
			if_stmt(tree->son_tree[0]);
			statements_list(tree->son_tree[1]);
		}
		statements(tree->son_tree[0]);
		statements_list(tree->son_tree[1]);
		
	}
	


}

void Generate::if_stmt(Node * tree)
{
	//std::cout << tree->son_tree[1]->name_node;
	std::string var = expression(tree->son_tree[1]);
	
	std::cout << "\tcmp " << var<<std::endl;
	std::cout << "jmp ?ELSE" << i << std::endl;
	std::cout <<"?THEN:"<<i << std::endl;

	std::cout << "?ELSE:" << i << std::endl;

	intermediaRepresentStream << "\tcmp " << var << std::endl;
	intermediaRepresentStream << "jmp ?ELSE" << i << std::endl;
	intermediaRepresentStream << "?THEN:" << i << std::endl;

	intermediaRepresentStream << "?ELSE:" << i << std::endl;
	i++;
}

void Generate::statements(Node * tree)
{
	if (*(tree->son_tree[0]->token)==WHILE)
	{
		tree = tree->son_tree[1];
		while (tree->name_node != "logical_multiplier")
		{
			tree = tree->son_tree[0];

		}
		std::string var=expression(tree->son_tree[0]);
		std::string com_op=compare_operator(tree->son_tree[1]);
		std::string var2=expression(tree->son_tree[2]);

		std::cout << "?WHILE" << i << ":\n";
		intermediaRepresentStream << "?WHILE" << i << ":\n";
		std::cout << "mov eax, " << var;
		intermediaRepresentStream << "\tmov eax, " << var << std::endl;
		std::cout << "mov ebx, " << var2;
		intermediaRepresentStream << "\tmov ebx, " << var2 << std::endl;
		std::cout << "cmp eax,ebx"<<std::endl;
		intermediaRepresentStream << "\tcmp eax, ebx" << std::endl;


		std::cout <<"\t"<<com_op <<" ?ENDWHILE" << i << "\n";
		intermediaRepresentStream<<"\t"<<com_op << " ?ENDWHILE" << i << "\n";

		std::cout << "\tnop\n";
		intermediaRepresentStream << "\tnop\n";

		std::cout << "jmp ?WHILE" << i << "\n";
		intermediaRepresentStream << "\tjmp ?WHILE" << i << "\n";

		std::cout << "?ENDWHILE"<<i<<":\n";
		intermediaRepresentStream << "?ENDWHILE" << i << ":\n";

		//std::cout << "\tnop\n";
		//intermediaRepresentStream << "\tnop\n";

		i++;
	}
}
std::string  Generate::compare_operator(Node * tree)
{
	//std::cout << tree->son_tree[0]->name_node << std::endl;
	if (tree->son_tree[0]->name_node == "<=")//jle
		return "jg";
	else if (tree->son_tree[0]->name_node == ">=")//jae
		return "jl";
	if (tree->son_tree[0]->name_node == "<")//jl
		return "jge";
	else if (tree->son_tree[0]->name_node == ">")//ja
		return "jle";
	if (tree->son_tree[0]->name_node == "=")//jz
		return "jnz";
	return "";
}
std::string Generate::expression(Node * tree)
{
	while (tree->name_node != "identifier")
	{
		tree = tree->son_tree[0];
	}
	for (auto i = identifier.begin(); i != identifier.end(); i++)
	{
		if ((*i).token->toString() ==  tree->son_tree[0]->name_node)
		{
			
			std::string str = "[ebp+" + std::to_string((*i).p) + "]";
			return str;
		}
	}
	//std::cout << tree->son_tree[0]->name_node << std::endl;
	return "";
}