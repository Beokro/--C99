%option yylineno
%pointer

%{
#include <cstdlib>
#include <cstring>
#include "parser.hpp"

void yyerror(const char *);
%}



%%

"bool"		    {return BOOL;}
"char"		    {return CHAR;}
"int"   	    {return INT;}
"float"             {return FLOAT;}
"double"            {return DOUBLE;}
"short"             {return SHORT;}
"unsigned"          {return UNSIGNED;}
"signed"            {return SIGNED;}
"void"              {return VOID;}
"const"             {return CONST;}
"string"	    {return STRING;}
"long"              {return LONG;}
"switch"            {return SWITCH;}
"break"             {return BREAK;}
"enum"              {return ENUM;}
"case"              {return CASE;}
"2continue"          {return CONTINUE;}
"goto"              {return GOTO;}
"sizeof"            {return SIZEOF;}
"default"           {return DEFAULT;}
"struct"            {return STRUCT;}

"do"                {return DO;}
"typedef"           {return TYPEDEF;}
"if"  		    {return IF;}
"for"               {return FOR;}
"else"		    {return ELSE;}
"while"		    {return WHILE;}
"return"	    {return RETURN;}
"NULL"		    {return NULLX;}
"true"		    {return TRUE;}
"false"		    {return FALSE;}
"include"           {return INCLUDE;}

"->"                {return ARROW;}
"&&"		    {return AND;}
"||"		    {return OR;}
">>"                {return SR;}
"<<"                {return SL;}
"=="		    {return EQ;}
">="		    {return GE;}
"<="		    {return LE;}
"!="		    {return NEQ;}
"&="                {return ANDASSIGN;}
"^="                {return XORASSIGN;}
"|="                {return ORASSIGN;}
"<<="               {return SLASSIGN;}
">>="               {return SRASSIGN;}
"*="                {return TIMESASSIGN;}
"/="                {return DIVASSIGN;}
"%="                {return REMASSIGN;}
"+="                {return ADDASSIGN;}
"-="                {return MINUSASSIGN;}
"++"                {return ADDADD;}
"--"                {return MINUSMINUS;}


[\"].*[\"]			{
char * temp = strdup(yytext);
temp+=1;
temp[strlen(temp)-1] = '\0';
/*yylval.u_base_charptr = temp;*/
return STRINGV;
}

[\'][a-zA-Z][\']      {/*yylval.u_base_int=(int)(*(yytext+1));*/   return CHARV;}

[\/\=\>\<\-\!\+\*\&\^\;\:\,\|\{\}\(\)\[\]\?\%\~\#\.]  	{return *yytext; }

0[0-7]* 				{
/*yylval.u_base_int = strtol(yytext,NULL,8);*/
return NUMBER;
}

0X[0-9A-F][0-9A-F]* 		{/*yylval.u_base_int=strtol(yytext,NULL,16);*/ return NUMBER;}
0x[0-9A-F][0-9A-F]* 		{/*yylval.u_base_int=strtol(yytext,NULL,16);*/ return NUMBER;}
0|[1-9][0-9]*         		{/*yylval.u_base_int=strtol(yytext,NULL,10);*/ return NUMBER; }
0b[0-1]*		        {/*yylval.u_base_int=strtol(yytext,NULL,2);*/  return NUMBER; }

[a-zA-Z][0-9a-zA-Z_]*		{/*yylval.u_base_charptr = strdup(yytext);*/ return ID;}


[ \t\n]				; /* skip whitespace */
"/*" 				{
			        	char current = yyinput();
					char last = ' ';
					while(true){
						last = current;
						current = yyinput();
						if(last == '*' && current == '/'){
							break;
					}
					if(current == EOF)
						yyerror((char *) "comment not ended");
					}
				}

<<EOF>> 			{yyterminate();}
.                               yyerror((char *) "invalid character");


%%

/** You shall not pass!
 *  You should not  have to do or edit anything past this.
 */

int yywrap(void) {
    return 1;
}
