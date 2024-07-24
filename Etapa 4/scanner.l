
%{
	//Gabriel Antônio Pereira - 0032449
    #include "ast.h"
    #include "hash.h"
    #include "y.tab.h"
    int running = 1;
    int lineNumber = 1;

%}

%x COMMENT

%%


int                               { return KW_INT; }
char                              { return KW_CHAR; }
float                             { return KW_FLOAT; }
bool                              { return KW_BOOL; }

if                                { return KW_IF; }
else                              { return KW_ELSE; }
while                             { return KW_WHILE; }
read                              { return KW_READ; }
print                             { return KW_PRINT;  }
return                            { return KW_RETURN; }

false                             {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_FALSE); return LIT_FALSE; }
true                              {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_TRUE); return LIT_TRUE; }

(<=)                              { return OPERATOR_LE; }
(>=)                              { return OPERATOR_GE; }
(==)                              { return OPERATOR_EQ; }
(!=)                              { return OPERATOR_DIF; }

[-,;:=()\[\]\{\}\+\*\/%<>&|~]     { return yytext[0]; }     


(\"([^\"\n]*(\\\"|\\\n)?)*\")     {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_STR); return LIT_STRING; }

[a-zA-Z_][a-zA-Z_0-9]*            {yylval.symbol = insertHashAddress(yytext,SYMBOL_IDENTIFIER); return TK_IDENTIFIER; }

[0-9]+                            {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_INT); return LIT_INT; }
\'.\'                             {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_CHAR); return LIT_CHAR; }
[0-9]*\.[0-9]+                    {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_REAL); return LIT_REAL; }
[0-9]+\.[0-9]*                    {yylval.symbol = insertHashAddress(yytext,SYMBOL_LIT_REAL); return LIT_REAL; }
"\n"                              {++lineNumber;}
"//".*                 
"/*"                              { BEGIN(COMMENT); }

[\t ]+  
.                                 { return TOKEN_ERROR; }

<COMMENT>"*/"                     { BEGIN(INITIAL); }
<COMMENT>"\n"                     { ++lineNumber; }
<COMMENT>.                       
%%

void initMe(){
    hashInit();
}

int getLineNumber(void){
    return lineNumber;
}

int isRunning(){
    return running;
}

int yywrap(){ 
    running = 0; 
    return 1;
}
