#include "shell.h"

// typedef enum e_lexer_mode
// {
// 	UNQUOTED, //  the start mode, for echo foo

// 	SQ, // for 'single-quoted strings'
// 	DQ, // for "double quoted strings, which allow $ expansions"
// 	DOLLAR_SQ, // for $'\n' -- literal strings that accept C escapes

// 	ARITH, // for arithmetic expressions, e.g. in $((1+2))
// 	VS_1, // for the first token after ${
// 	VS_2, // for a token in ${ after a name, like :- in ${foo:-bar}
// 	VS_ArgUnquoted, // for the argument after an operator, e.g. ${foo:-var op}
// 	VS_ArgDQ, // for the argument after an operator when double quoted, e.g. "${foo:-var op}"
// 	REGEX, // for the right hand side of [[ foo =~ ^foo$ ]]
// 	Backtick, // To treat quotes and backslashes differently in "`echo hi`" versus "$(echo hi)".
// 	DBracket // For what's inside [[, aka the bool sublanguage.
// }	t_lexer_mode;





