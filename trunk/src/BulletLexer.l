%option noyywrap
%option yylineno

DIGIT     	[0-9]
LETTER    	[a-zA-Z_]
HEX       	[a-fA-F0-9]
BINARY    	[0-1]

%{

#include <stdio.h>
#include "bsBulletParser.hpp"

%}

%%

"/*"    {
            int c;

            while ((c = yyinput ()) != 0)
            {
                if (c == '*')
                {
                    if ((c = yyinput()) == '/')
                    {
                        break;
                    }
                    else
                    {
                        unput (c);
                    }
                }
            }
		}

"//"[^\n]*                      { /* process comments */ }

"bullet"						{ return (KEYWORD_BULLET); }
"area"							{ return (KEYWORD_AREA); }
"spline"						{ return (KEYWORD_SPLINE); }
"repeat"						{ return (KEYWORD_REPEAT); }
"if"							{ return (KEYWORD_IF); }
"else"							{ return (KEYWORD_ELSE); }
"goto"							{ return (KEYWORD_GOTO); }
"wait"							{ return (KEYWORD_WAIT); }
"set"							{ return (KEYWORD_SET); }
"affectors"						{ return (KEYWORD_AFFECTORS); }
"BASE"							{ return (KEYWORD_BASE); }
"CENTRE"						{ return (KEYWORD_CENTRE); }

{DIGIT}+						{ return (INTEGER); }
{DIGIT}*"."{DIGIT}+				{ return (REAL); }
{DIGIT}+"."{DIGIT}*				{ return (REAL); }

{LETTER}({LETTER}|{DIGIT})*     { return (IDENTIFIER); }

"<="							{ return (SYMBOL_LTE); }
">="							{ return (SYMBOL_GTE); }
"=="							{ return (SYMBOL_EQ); }
"!="							{ return (SYMBOL_NEQ); }
"&&"							{ return (SYMBOL_LOG_AND); }
"||"							{ return (SYMBOL_LOG_OR); }
";"								{ return (';'); }
","								{ return (','); }
"="								{ return ('='); }
"["								{ return ('['); }
"]"								{ return (']'); }
"("								{ return ('('); }
")"								{ return (')'); }
"{"								{ return ('{'); }
"}"								{ return ('}'); }
"+"								{ return ('+'); }
"-"								{ return ('-'); }
"*"								{ return ('*'); }
"/"								{ return ('/'); }
"%"								{ return ('%'); }
"<"								{ return ('<'); }
">"								{ return ('>'); }

[ \t\v\n\r\f]					{ /* eat up whitespace */ }

.								{ return (TOKEN_ERROR); }

%%


