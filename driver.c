#include <stdio.h>
#include <stdlib.h>
#include "your_code.h"

extern FILE* yyin;
extern int yyparse();

// A global variable that holds a pointer to the AST root
ASTNode* gASTRoot;
void initSymbolTable();

int main(int argc, char**argv)
{

        if (argc != 2){
                 printf("ERROR: Invalid number of command-line arguments. Usage: bcc File_Name.bc\n");
                 exit(1);
        }
	initSymbolTable();
	//printf("file opening\n");
        yyin = fopen(argv[1], "r" );

        if (yyin == NULL){
                 printf("ERROR: Failed to open the input file\n");
                 exit(1);
        }

        // Call the parser. 
        // Add embedded actions to the parser (in BabyC.y) to construct the AST and store its root in gASTRoot. 
        yyparse();
        fclose(yyin);

        // Now that the AST has been constructed, pass its root to the function that traverses it and generates the ILOC code.
        // GenerateILOC(gASTRoot);
        // Code generation is commented out in this assignment. You will implement it in the next assignment.
        return 0;
}

void initSymbolTable(){
	int i;
	symbolTable.thresh = ST_StartSize * 3 /4;
	symbolTable.table = (st_entry*) malloc(sizeof(st_entry) * ST_StartSize);
	for(i = 0; i<ST_StartSize; i++){
		symbolTable.table[i].offset = -1;
	}
	symbolTable.size = ST_StartSize;

	symbolTable.curSize = 0;
}