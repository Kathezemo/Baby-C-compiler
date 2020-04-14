#ifndef YOUR_CODE_H
#define YOUR_CODE_H

#define ST_StartSize 20
#define threshold = .75f;


typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_WHILE} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{ADD_OP, MULT_OP, SUB_OP, DIV_OP, OR_OP, AND_OP} ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
	
	// The following pointer is just a suggestion; you don't have to use it if you have a better design.
	ASTNode* next; // a pointer used to link statement nodes together in a statement list

// Depending on your implementation, you may need to add other fields to this struct 

};

typedef struct {
	int offset;
	char* name;
} st_entry;

typedef struct {
	st_entry* table;
	int size;
	int thresh;
	int curSize;
} symbol_table;

symbol_table symbolTable;


// Add functions to create the different kinds of ASTNodes 
// These functions are called by the code embedded in the grammar.
// Here are some samples:  
ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* CreateAssignmentNode(ASTNode* ident, ASTNode* expr);
ASTNode* CreateLHSNode(char* ident);

ASTNode* CreateAdditionNode(ASTNode* l, ASTNode* r);
ASTNode* CreateSubtractionNode(ASTNode* l, ASTNode* r);
ASTNode* CreateMultNode(ASTNode* l, ASTNode* r);
ASTNode* CreateDivNode(ASTNode* l, ASTNode* r);

ASTNode* CreateIfNode(ASTNode* cond, ASTNode* stList);
ASTNode* CreateIfElseNode(ASTNode* cond, ASTNode* trueStList, ASTNode* falseStList);
ASTNode* CreateOrNode(ASTNode* l, ASTNode* r);
ASTNode* CreateAndNode(ASTNode* l, ASTNode* r);

ASTNode* CreateLessNode(ASTNode* l, ASTNode* r);
ASTNode* CreateLessEqualNode(ASTNode* l, ASTNode* r);
ASTNode* CreateEqualNode(ASTNode* l, ASTNode* r);
ASTNode* CreateGreaterEqualNode(ASTNode* l, ASTNode* r);
ASTNode* CreateGreaterNode(ASTNode* l, ASTNode* r);
ASTNode* CreateNotEqualNode(ASTNode* l, ASTNode* r);


ASTNode* CreateWhileNode(ASTNode* cond, ASTNode* stList);



// Need a function to add a declaration to your symbol table
void AddDeclaration(char* name);
int getHash(char* name);
int searchTable(char* name);
int nextOffset();
void stInsert(char* name);
void dupDeclaration(char* name);
void varNotDeclared(char* name);


// This is the function that generates ILOC code after the construction of the AST
//void GenerateILOC(ASTNode* node);
#endif
