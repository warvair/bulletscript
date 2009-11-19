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

"controller"					{ return (KEYWORD_CONTROLLER); }
"emitter"						{ return (KEYWORD_EMITTER); }
"affector"						{ return (KEYWORD_AFFECTOR); }
"function"						{ return (KEYWORD_FUNCTION); }
"state"							{ return (KEYWORD_STATE); }
"event"							{ return (KEYWORD_EVENT); }
"raise"							{ return (KEYWORD_RAISE); }
"enable"						{ return (KEYWORD_ENABLE); }
"disable"						{ return (KEYWORD_DISABLE); }
"while"							{ return (KEYWORD_WHILE); }
"break"							{ return (KEYWORD_BREAK); }
"continue"						{ return (KEYWORD_CONTINUE); }
"if"							{ return (KEYWORD_IF); }
"else"							{ return (KEYWORD_ELSE); }
"goto"							{ return (KEYWORD_GOTO); }
"wait"							{ return (KEYWORD_WAIT); }
"suspend"						{ return (KEYWORD_SUSPEND); }
"signal"						{ return (KEYWORD_SIGNAL); }
"die"							{ return (KEYWORD_DIE); }

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
"$"								{ return ('$'); }
":"								{ return (':'); }
","								{ return (','); }
"."								{ return ('.'); }
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
"++"							{ return (SYMBOL_INC); }
"--"							{ return (SYMBOL_DEC); }
"+="							{ return (SYMBOL_ADD_A); }
"-="							{ return (SYMBOL_SUB_A); }
"*="							{ return (SYMBOL_MUL_A); }
"/="							{ return (SYMBOL_DIV_A); }

[ \t\v\n\r\f]					{ /* eat up whitespace */ }

.								{ return (TOKEN_ERROR); }

%%


