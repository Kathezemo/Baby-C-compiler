%{
	#include <stdio.h>
	#include "your_code.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here 
%initial-action 
{

}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	struct ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> StatementList
%type <node> If
%type <node> Condition
%type <node> While
%type <node> LTerm
%type <node> LFactor
%type <node> Compare

// Add the rest of the types for the grammar's symbols


%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot=$6;} // Store the AST root node in gASTRoot
;

DeclarationList:  | Declaration DeclarationList // Note that a DeclarationList may be empty
;

Declaration: "int" IDENT ';' {AddDeclaration($2); printf("Processing declaration of %s\n", $2);}
;

Factor: IDENT 		{$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
	| NUM 		{$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
	| '('Expr')'	{$$ = $2;}
;

StatementList: 	{$$ = NULL;}
               | Statement StatementList	{$$ = CreateStatementListNode($1,$2); printf("Adding a statement to a statement list \n");}
;

Statement: Assignment		{$$ = $1;}
	| If			{$$ = $1;}
	| While			{$$ = $1;}
;

Assignment: LHS '=' Expr ';'	{$$ = CreateAssignmentNode($1, $3; printf("Adding assignment node of %d to %d\n", $3, $1);}
;

Expr: Term			{$$ = $1;}
 	| Expr '+' Term		{$$ = CreateAdditionNode($1, $3);}
	| Expr '-' Term		{$$ = CreateSubtractionNode($1, $3);}
;

Term: Factor       		{$$ = $1;}
	| Term '*' Factor	{$$ = CreateMultNode($1, $3);}
	| Term '/' Factor	{$$ = CreateDivNode(#1, $3);}
;

If: IF '(' Condition ')' '{' StatementList '}'		{$$ = CreateIfNode($3, $6); printf("Creating if node\n")}
	| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}'	{$$ = CreateIfElseNode($3, $6, $10); printf("Creating If-Else node\n")}
;

Condition: LTerm		{$$ = $1;}
	| Condition OR LTerm	{$$ = CreateOrNode($1, $3);}
;

LTerm: LFactor			{$$ = $1;}
	| LTerm AND LFactor	{$$ = CreateAndNode($1, $3); printf("Creating and node\n");}
;

LFactor: Compare		{$$ = $1;}
;

Compare: Expr LE Expr		{$$ = CreateLessEqualNode($1, $3); printf("Creating less/equal node\n");}
	|Expr GE Expr		{$$ = CreateGreaterEqualNode($1, $3); printf("Creating greater/equal than node\n");}
	|Expr EQ Expr		{$$ = CreateEqualNode($1, $3); printf("Creating equal node\n");}
	|Expr NE Expr		{$$ = CreateNotEqualNode($1, $3); printf("Creating not equal node\n");}
	|Expr '>' Expr		{$$ = CreateGreaterThanNode($1, $3); printf("Creating greater than node\n");}
	|Expr '<' Expr		{$$ = CreateLessThanNode($1, $3); printf("Creating less than node\n");}
;

While: "while" '(' Condition ')' '{' StatementList '}'	{$$ + CreateWhileNode($3, $6); printf("Creating while node\n");}



%%
