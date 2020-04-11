#include "your_code.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int offset = 0;

// Write the implementations of the functions that do the real work here

ASTNode* CreateNumNode(int num){
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_NUM; 
        node->num = num;
        return node;
}


ASTNode* CreateIdentNode(char* name){
	int ind = searchTable(name);
	if(ind == -1){
		varNotDeclared(name);
	}

	ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
	node->type = ASTNODE_IDENT;
	node->name = name;

	return node;
}

// Take a statement node and a statement list node and connect them together
// to form a bigger statement list node (add the statement to the statement list).
// Return a pointer to the bigger list that resulted from this linking
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList){

}

ASTNode* CreateAssignmentNode(ASTNode* ident, ASTNode* expr){

}

ASTNode* CreateAdditionNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateSubtractionNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateMultNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateDivNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList){

}

ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* trueStList, ASTNode* falseStList){

}

ASTNode* CreateOrNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateAndNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateLessNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateLessEqualNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateEqualNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateGreaterEqualNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateGreaterNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateNotEqualNode(ASTNode* l, ASTNode* r){

}

ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList){

}



void AddDeclaration(char* name){
	int index = searchTable(name);
	if(index == -1){
		stInsert(name);
	}else{
		dupDeclaration(name);
	}
}


int getHash(char* name){
	int index = 0;
	int i;
	for(i=0; i<strlen(name); i++){
		index += name[i];
	}
	return index % MAX_VARIABLES;

}

int searchTable(char* name){
	int index = getHash(name);

	while(symbol_table[index].offset != -1){
		if(strcmp(symbol_table[index].name, name) == 0){

			return index;
		}
		index++;
		index %= MAX_VARIABLES;
	}

	return -1;
}

int nextOffset(){
	int n = offset;
	offset += 4;
	return n;
}

void stInsert(char* name){
	int ind = getHash(name);

	while(symbol_table[ind].offset != -1){
		ind = (ind + 1) % MAX_VARIABLES;
	}
	symbol_table[ind].name = name;
	symbol_table[ind].offset = nextOffset();

}

void dupDeclaration(char* name){

	char* str = "Multiple declarations of '";
	char* error = (char*) malloc(strlen(str)+strlen(name)+1);
	strcat(error, str);
	strcat(error, name);
	strcat(error, "'");
	yyerror(error);
}

void varNotDeclared(char* name){

	char* str = "IDENT not declared";
	yyerror(str);
}


// Commented out in this assignment 
/*void GenerateILOC(ASTNode* node);
{

}*/

