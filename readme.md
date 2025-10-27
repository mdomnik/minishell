# Minishell - A simple recreation of Bash

![Showcase](./Showcase.gif)

A compact yet fully functional **UNIX shell** written in C.  
This project replicates the core behavior of `bash`, implementing **command parsing, built-in commands, pipes, redirections, environment variable expansion**, and more — all from scratch.

---

## Overview

The goal of *Minishell* is to understand how a real shell works internally:  
how user input is parsed, commands are executed, and processes interact with the operating system.

This project builds a strong foundation in **system programming**, especially process handling, file descriptors, and command interpretation.

---

## Installation

Clone and compile the project:

```bash
git clone https://github.com/mdomnik/minishell.git
cd minishell
make
```

Run the shell:

```bash
./minishell
```

You can exit the shell with:

```bash
exit
```

---

## Features

### Built-in Commands
- `echo` (with `-n` flag)  
- `cd` (supports relative, absolute, and `-`)  
- `pwd`  
- `export`, `unset`, `env`  
- `exit`

### External Commands
- Executes binaries found in `$PATH`  
- Handles absolute and relative paths  
- Preserves environment variables between commands  

### Pipes & Redirections
- Pipelines (`cmd1 | cmd2 | cmd3`)  
- Input `<`, output `>`, append `>>` redirections  
- Heredocs (`<<`) with proper delimiter behavior  

### Environment & Quoting
- `$VAR` expansion (inside double quotes)  
- Single quotes preserve literal strings  
- Works with redirections and pipes  

### Signal Handling
- `Ctrl+C` interrupts current command but not the shell  
- `Ctrl+\` and `Ctrl+D` handled gracefully  

### Error & Status Handling
- Accurate exit codes (`$?`)  
- Clear error messages for invalid commands, files, or paths  
- Behavior aligned with `bash`

---

## Demonstrated in the Showcase

The GIF demo above shows:
- Builtins such as `cd`, `echo`, `export`, `unset`, `env`  
- External command execution (`ls`, `grep`, `wc`, `cat`, etc.)  
- Redirections (`>`, `>>`, `<`) and heredocs (`<<`)  
- Pipelining between commands  
- Variable expansion and quoting rules  
- Error handling and `$?` exit status  
- Clean exit from the shell  

---

## Technical Insights

- Custom **lexer** and **parser** for tokenizing input and building commands  
- Use of `fork()` / `execve()` for executing child processes  
- Management of `pipe()` and `dup2()` for I/O redirections and pipelines  
- Environment variable storage and expansion logic  
- Signal handling using `sigaction()` to replicate bash-style behavior  

---

## Project Structure

```text
.
├── minishell          # Compiled shell binary
├── Makefile           # Build rules
├── inc/               # Headers
├── src/               # Source code (lexer, parser, executor, builtins, utils, ...)
├── lib/               # libft (custom standard library)
├── obj/               # Object files
├── suppressions.supp  # Valgrind suppression file
└── Showcase.gif       # Feature demo
```

---

## Author

**Maciej** — [@mdomnik](https://github.com/mdomnik) <br>
**Kang** — [@donkeykang316](https://github.com/donkeykang316) 
