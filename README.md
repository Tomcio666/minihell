*This project has been created as part of the 42 curriculum by tloin and mgumienn.*

## Description
`minishell` is a small Bash-like shell written in C. The goal of the project is to understand
how a UNIX shell works by implementing a full interactive loop: lexing/parsing user input,
building an AST, and executing commands using processes, pipes, redirections, environment
expansion, and signal handling.

The implementation focuses on:
- an interactive prompt using `readline`
- a command history (also via `readline`)
- an execution engine based on `fork`, `execve`, `pipe`, `dup2`, and proper FD management

## Features
- **Prompt & history**: interactive prompt + history via `readline` / `add_history`
- **Executable resolution**: runs commands using `PATH`, absolute paths, or relative paths
- **Quotes**
  - `'single quotes'`: prevent interpretation of metacharacters
  - `"double quotes"`: prevent interpretation except for `$` expansions
- **Expansions**
  - environment variables: `$VAR`
  - last exit status: `$?`
- **Redirections**
  - input: `<`
  - output truncate: `>`
  - output append: `>>`
  - heredoc: `<< DELIM`
- **Pipelines**: `cmd1 | cmd2 | cmd3`
- **Signals (interactive behavior like bash)**:
  - `Ctrl-C`: interrupts current input and shows a new prompt on a new line
  - `Ctrl-D`: exits the shell
  - `Ctrl-\`: ignored in interactive mode
- **Builtins**
  - `echo` (supports `-n`)
  - `cd` (relative or absolute path)
  - `pwd`
  - `export` (no options)
  - `unset` (no options)
  - `env` (no options/arguments)
  - `exit` (no options)

### Bonus
This repository also includes support for:
- **Logical operators**: `&&` and `||`
- **Parentheses / subshell grouping**: `( ... )` for priority
- **Wildcards**: `*` expansion in the current working directory (no `/` in the pattern)

## Instructions
### Requirements
- **OS**: Linux / macOS (POSIX)
- **Compiler**: `cc`
- **Libraries**: `readline` and `ncurses` (linked via `-lreadline -lncurses`)

### Build

```bash
make
```

This builds the `minishell` binary in the repository root.

### Run

```bash
./minishell
```

Notes:
- The script uses `.readline.supp` to suppress known `readline`-related leaks (allowed by the subject).
- Your own code should remain leak-free.

## Resources
- **42 subject**: `en.subject (1).pdf`
- **Bash manual**: `man bash`
- **GNU Readline**: `man readline`
- **Process & exec**: `man fork`, `man execve`, `man waitpid`
- **Pipes & redirections**: `man pipe`, `man dup2`, `man open`
- **Signals**: `man signal`, `man sigaction`

### AI usage
AI was used to:
- draft and restructure this `README.md` based on the project subject requirements and the current codebase

No AI-generated code was copy-pasted into the implementation without full understanding and manual review.