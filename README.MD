Welcome to my Minishell project! (IN PROGRESS)

The very first thing to do before starting this project is to read A LOT of docs in order to understand how BASH works, and its grammatical logic. You also need to understand how to parse methodologically, if you want to avoid spending weeks trying to handle each specific case because there are many to handle and if you started your parser without the logic Lexer + Parser + AST you're certainly going to struggle. I am not saying it's impossible since at the end of the day we only need to build a minimalistic shell, but you will have a hard time and probably miss the point of the project.

Understand the syntax

SEMICOLON [ ; ]
- Can't start a command

Example:
bash-3.2$ ; echo test
bash: syntax error near unexpected token `;'


AND, OR, PIPE [ && ] [ || ] [ | ]
- Can't start a command
- Opens multiline if ends a command. The current subject does not requires multiline to be supported


REDIRECTION [ < ] [ > ] [ >> ]
- Can be anywhere but must be followed only by a WORD token (by WORD I mean any token that has not a special meaning for bash)

Example 1: Followed by a token PIPE
bash-3.2$ echo lol > |
bash: syntax error near unexpected token `|'

Example 2: Followed by a token NEWLINE
bash-3.2$ echo lol >
bash: syntax error near unexpected token `newline'

Example 3: Followed by a token WORD
bash-3.2$ > echo lol
bash: lol: command not found
-> Bash accepts the syntax by understanding "echo" as the redirection target hence treats "lol" as a command.

Example 4: Followed by a token WORD that contains an environment variable:
bash-3.2$ echo lol > $TEST
bash: $TEST: ambiguous redirect


BACKSLASH [ \ ]
- Nothing new or surprising, a backslash escapes the following char if not enclosed in single quotes. If it ends a command, it will open multiline.


SIMPLE QUOTES [ ' ]
- Preserves the literal value of everything enclosed in single quotes. Single quotes within single quotes may not occur, even if escaped with a backslash. 


DOUBLE QUOTES [ " ]
- Preserves the literal value of almost everything enclosed in double quotes except [ $ ] [ ` ] [ \ ] and, when history expansion is enabled, [ ! ].
Note that the current minishell project requires you only to handle [ $ ] and [ \ ].


ENVIRONNEMENT VARIABLE [ $NAME ]
- Created with the following pattern: [NAME]=[value]
- Be careful, if you set your the [value] of your variable within double quotes. Let's take for example TEST="foo    bar".

1. Example 1: without double quotes
bash-3.2$ echo $TEST
foo bar 
-> The variable will is expended into 2 tokens [foo] [bar].

2. Example 2: with double quotes
bash-3.2$ echo "$TEST"    baz
foo    bar baz
-> The literal value of the spaces will be preserved and the variable will be expanded into a single token [foo    bar].



PART 1: The Lexer
A lexer creates a stream of tokens that will be used by the parser to build the Abstract Syntax Tree. For example, let's say your minishell you type the following command then press enter: ["echo I love bananas and 'chai tea' > foo"]
The following tokens will be created: [echo] [I] [love] [bananas] [and] [chai tea] [>] [foo] [newline]

TBC