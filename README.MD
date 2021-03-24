Welcome to my Minishell project! (IN PROGRESS)

The very first thing to do before starting this project is to read A LOT of docs in order to understand how BASH works, and its grammatical logic. You also need to understand how to parse methodologically, if you want to avoid spending weeks trying to handle each specific case because there are many to handle and if you started your parser without the logic Lexer + Parser + AST you're certainly going to struggle. I am not saying it's impossible since at the end of the day we only need to build a minimalistic shell, but you will have a hard time and probably not learn much.

1. Lexer
A Lexer creates a stream of "tokens" that will be used by the parser to build the Abstract Syntax Tree. For example, let's say your minishell you type the following command then press enter: ["echo I love bananas and 'chai tea' > foo"]
The following tokens will be created: [echo] [I] [love] [bananas] [and] [chai tea] [>] [foo] [newline]

TBC