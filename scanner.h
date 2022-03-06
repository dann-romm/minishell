
typedef enum e_token_type
{
	UNKNOWN_TOKEN,
	/**************************** GRAMMAR SYMBOLS ****************************/
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE, // \n
	IO_NUMBER,
	
	// The following are the operators containing more than one character
	AND_IF, // &&
	OR_IF, // ||
	DSEMI, // ;;
	DLESS, // <<
	DGREAT, // >>
	LESSAND, // <&
	GREATAND, // >&
	LESSGREAT, // <>
	DLESSDASH, // <<-

	CLOBBER, // >|

	// The following are the reserved words
	IF, // if
	THEN, // then
	ELSE, // else
	ELIF, // elif
	FI, // fi
	DO, // do
	DONE, // done

	CASE, // case
	ESAC, // esac
	WHILE, // while
	UNTIL, // until
	FOR, // for

	// These are reserved words, not operator tokens, and are
	// recognized when reserved words are recognized
	LBRACE, // {
	RBRACE, // }
	BANG, // !

	PIPE, // |
	LPARENTHESIS, // (
	RPARENTHESIS, // )
	AND, // &
	SEMI, // ;

	IN, // in

	/******************************** GRAMMAR ********************************/

	// linebreak complete_commands linebreak
	// linebreak
	program,

	// complete_commands newline_list complete_command
	// complete_command
	complete_commands,

	// list separator_op
	// list
	complete_command,

	// list separator_op and_or
	// and_or
	list,

	// pipeline
	// and_or AND_IF linebreak pipeline
	// and_or OR_IF  linebreak pipeline
	and_or,

	// BANG pipe_sequence
	// pipe_sequence
	pipeline,

	// command
	// pipe_sequence '|' linebreak command
	pipe_sequence,

	// simple_command
	// compound_command
	// compound_command redirect_list
	// function_definition
	command,

	// brace_group
	// subshell
	// for_clause
	// case_clause
	// if_clause
	// while_clause
	// until_clause
	compound_command,

	// '(' compound_list ')'
	subshell,

	// linebreak term
	// linebreak term separator
	compound_list,

	// term separator and_or
	// and_or
	term,

	// FOR name do_group
	// FOR name sequential_sep do_group
	// FOR name linebreak in sequential_sep do_group
	// FOR name linebreak in wordlist sequential_sep do_group
	for_clause,

	// NAME
	name,

	// IN
	in,

	// wordlist WORD
	// WORD
	wordlist,
	
	// CASE WORD linebreak in linebreak case_list ESAC
	// CASE WORD linebreak in linebreak case_list_ns ESAC
	// CASE WORD linebreak in linebreak ESAC
	case_clause,

	// case_list case_item_ns
	// case_item_ns
	case_list_ns,

	// case_list case_item
	// case_item
	case_list,

	// pattern ')' linebreak
	// pattern ')' compound_list
	// '(' pattern ')' linebreak
	// '(' pattern ')' compound_list
	case_item_ns,

	// pattern ')' linebreak DSEMI linebreak
	// pattern ')' compound_list DSEMI linebreak
	// '(' pattern ')' linebreak DSEMI linebreak
	// '(' pattern ')' compound_list DSEMI linebreak
	case_item,

	// WORD
	// pattern '|' WORD
	pattern,

	// IF compound_list THEN compound_list else_part FI
	// IF compound_list THEN compound_list FI
	if_clause,

	// ELIF compound_list Then compound_list
	// ELIF compound_list Then compound_list else_part
	// ELSE compound_list
	else_part,

	// WHILE compound_list do_group
	while_clause,

	// UNTIL compound_list do_group
	until_clause,

	// fname '(' ')' linebreak function_body
	function_definition,

	// compound_command
	// compound_command redirect_list
	function_body,

	// NAME
	fname,

	// LBRACE compound_list RBRACE
	brace_group,

	// DO compound_list DONE
	do_group,

	// cmd_prefix cmd_word cmd_suffix
	// cmd_prefix cmd_word
	// cmd_prefix
	// cmd_name cmd_suffix
	// cmd_name
	simple_command,

	// WORD
	cmd_name,

	// WORD
	cmd_word,

	// io_redirect
	// cmd_prefix io_redirect
	// ASSIGNMENT_WORD
	// cmd_prefix ASSIGNMENT_WORD
	cmd_prefix,

	// io_redirect
	// cmd_suffix io_redirect
	// WORD
	// cmd_suffix WORD
	cmd_suffix,

	// io_redirect
	// redirect_list io_redirect
	redirect_list,

	// io_file
	// IO_NUMBER io_file
	// io_here
	// IO_NUMBER io_here
	io_redirect,

	// '<' filename
	// LESSAND filename
	// '>' filename
	// GREATAND filename
	// DGREAT filename
	// LESSGREAT filename
	// CLOBBER filename
	io_file,

	// WORD
	filename,

	// DLESS here_end
	// DLESSDASH here_end
	io_here,

	// WORD
	here_end,

	// NEWLINE
	// newline_list NEWLINE
	newline_list,

	// newline_list
	// /* empty */
	linebreak,

	// '&'
	// ';'
	separator_op,

	// separator_op linebreak
	// newline_list
	separator,

	// ';' linebreak
	// newline_list
	sequential_sep
}	t_token_type;
