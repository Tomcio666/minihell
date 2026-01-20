# minihell
Our implementation of the 42 minishell project.

## Parser/Lexer Tests
- `lexer_test.c`: quick tokenization check using `ms_lexer`.
- `parser_test.c`: quick AST build check using `ms_parse`.


gdy wywoluje komende unset na w minishell a potem urzywam env aby zobaczyc liste zmiennych srodowiskowych to user dalej tam jest blad?

błąd wynikał z tego że parser wołał ms_ast_attach_chld a w kodzie i nagłówku była już funkcja ms_ast_attach_children przez to linker nie mógł znaleźć symbolu i make kończył się błędem