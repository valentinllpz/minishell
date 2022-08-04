# Minishell

![demo](demo.gif)

This [42](https://42.fr/en/homepage/) project teached us how to build our own minimalistic shell in C. I worked on this project with [Alexandre De Guarrigues](https://github.com/Ade-garr).

We built a [lexer](https://en.wikipedia.org/wiki/Lexical_analysis) to split the input command into meaningful tokens, which were then parsed and stored in an [Abstract Syntax Tree](https://en.wikipedia.org/wiki/Abstract_syntax_tree). It took time to work on the lexer since we needed to learn depth how [Bash](https://www.gnu.org/software/bash/) handles inputs and reverse engineer it, with the help of documentation. We then had to work on the execution part, with file descriptors in order to handle output redirections. 


## ✨ Features

- The following commands are built-in : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Other commands are called with `execve`
- Redirections : `>`, `>>`, `<`, `<<`
- Environment variable management
- signals  : `ctrl-C`, `ctrl-D`, `ctrl -\`
- Pipes `|`
- Separators `;`, `&&`
- Term caps with inline editor
- commands history `↑` `↓`


## 🧭 Usage

1. Clone this repo and access it with `cd`
2. Run `make` to build the image
3. Use `./minishell` to launch it


## 📚 Ressources

- [Bash Reference Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
- [Making your own Linux Shell in C](https://www.geeksforgeeks.org/making-linux-shell-c/)
- [42sh APPSINGES](https://files.gogaz.org/42sh-appsinges.html)
- [aosabook doc](https://www.aosabook.org/en/bash.html)
- [Abstract Syntax Tree explained](https://ruslanspivak.com/lsbasi-part7/)
- [Abstract Syntax Tree video](https://www.youtube.com/watch?v=r14Vtwi2k7s)
- [Creating pipes in C](https://tldp.org/LDP/lpg/node11.html)

## 👨‍💻 Authors
 
 - [Alexandre De Guarrigues](https://github.com/Ade-garr)
 - [Valentin Lugand Lopez](https://github.com/valentinllpz)
