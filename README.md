# minihell
Our implementation of the 42 minishell project.

## Parser/Lexer Tests
- `lexer_test.c`: quick tokenization check using `ms_lexer`.
- `parser_test.c`: quick AST build check using `ms_parse`.



fix ctrl+\ behaviour


executor_utils.c

ms_has_slash
ms_free_split
ms_env_path
ms_path_join
ms_exec_search


executor_io.c

ms_dup_io
ms_is_builtin
ms_execute_builtin_only
ms_execute_builtin
ms_execute_simple_cmd


executor_process.c

ms_execute_child
ms_wait_children
ms_execute_pipe
ms_execute_logic
node_no_command


executor_node.c

node_type_zero
ms_execute_node
ms_execute_ast