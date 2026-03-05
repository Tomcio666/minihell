# minihell
Our implementation of the 42 minishell project.

## Parser/Lexer Tests
- `lexer_test.c`: quick tokenization check using `ms_lexer`.
- `parser_test.c`: quick AST build check using `ms_parse`.

in heredoc after cntrl + C 
tloin:~/Desktop/core/minishell$ << a
heredoc> ^C
heredoc> 
tloin:~/Desktop/core/minishell$ 