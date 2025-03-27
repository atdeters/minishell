# Welcome to our Minishell!
Hey there, welcome to our Minishell project! 🎉

This is a simplified shell program developed as part of the curriculum at the 42 School. The goal of this project is to recreate a basic Unix shell with features that mimic the behavior of a typical shell, while also offering the flexibility to extend it with custom commands and functionalities.

Minishell serves as a great exercise in system programming, process management, and working with signals, all within the context of Unix-based systems. Whether you're interested in learning how shells work under the hood or you're just looking for a fun project to play around with, Minishell has you covered!

#### Disclaimer for other 42 students
This project is intended to be a learning exercise for 42 students. Please do not copy, fork, or steal code from this repository to submit as your own. The aim of the project is to help you learn, not just complete the assignment. If you’re stuck, work through the problem, ask for help, or discuss it with peers, but do not simply use other students' solutions. We believe in the value of learning through challenges, and that’s the only way you’ll truly grow and succeed at 42. Let’s keep it fair and fun!

# Installation & Setup
### Dependencies

The minishell program requires the following to compile and run:

- A Unix-like operating system (e.g., Linux, macOS)

- GNU Make

- GCC or Clang

- Readline library (for command-line input handling)

## Running Minishell with Docker Made Easy
If you do not want to deal with dependencies than using this link will be the easiest way to try
the minishell using [docker](https://docs.docker.com/engine/install/).
```sh
git clone https://github.com/atdeters/minishell.git && cd minishell && docker build -t msh . && docker run -it msh
```
**Note:**
The `alias-` (.msh_alias) and `history-` (.msh_history) files will not be stored when exiting and reopening this docker image. 
Use the following installation to try those features.

## One-Liner Installation Command
#### For Debian-based systems (Ubuntu, Debian, etc.)

```sh
sudo apt update && sudo apt install -y build-essential libreadline-dev && git clone https://github.com/atdeters/minishell.git && cd minishell && make
```
#### For MacOS (with Homebrew)
```sh
brew install readline && git clone https://github.com/atdeters/minishell.git && cd minishell && make
```

# Running the minishell program
Once compiled, start the shell with
```sh
./minishell
```
To run minishell in single-command mode run it with the `-s` flag.
It will execute the command and exit afterwards.
```sh
./minishell -s [command]
```
For displaying a usage file in the terminal run it with the `-h` flag
```sh
./minishell -h
```


# Features Overview
- **Environment Variable Management**: Easily access and modify environment variables.
- **Signal Handling**: Properly handles the signals `SIGINT` and `SIGQUIT`.
- **Pipes and Redirections**: Supports piping between commands and file redirection.
  - `>`: Redirects the output to a file.
  - `>>`: Redirects the output to a file in append mode.
  - `<`: Redirects the input from a file.
  - `<< DELIMITER`: Creates a temporary here document, which is terminated by the specified `DELIMITER`.
- **Forking and Execution**: Executes external programs and commands.
- **Built-in Commands**: Includes essential commands like `cd`, `echo`, `exit`, `pwd`, and more!
- **Bonus Features**:
  - **Persistent History**: Automatically saves command history in a file.
  - **Persistent Aliases**: Automatically saves aliases in a file.
  - **Current Working Directory Display**: Displays the current working directory in the prompt.
  - **Git Repository Info**: Displays the current git repository (if applicable) in the prompt.


## Built-in Commands
### alias [bonus feature]
Set or display aliases for commands.
Usage: `alias [flags] alias[=expansion]`
-	`alias` (without arguments) displays all active aliases.
-	`alias -r` removes alias permanently.
-	`alias "st= git status"` sets "st" as alias for "git status"
-	`alias st` displays the corresponding alias with its expansion

### biman [bonus feature]
Display a short manual for built-in commands.
Usage: `biman [builtin name]`

### cd
Change the shell working directory.  
Usage: `cd [directory]`
-   `cd` (without arguments) changes to the home directory.
-	`cd ~` also changes to the home directory.
-   `cd ..` switches to the previous directory.
-	`cd ..` moves up one directory.
-	`cd /usr/bin`  moves to /usr/bin.

### echo
Prints a line of text to the standard output.  
Usage: `echo [-n] [string...]`
-   `-n` : Omits the trailing newline.

### env
Displays the current environment variables.

### exit
Exits the shell with an optional exit code.  
Usage: `exit [status]`
-   If no status is given, it exits with the status of the last executed command.

### export
Set or display environment variables.  
Usage: `export name[=value]`
-   `export` (without arguments) lists all exported variables in alphabetical order.
-   `export VAR=value` : Sets an environment variable.

### pwd
Prints the absolute path of the current directory.
Usage: `pwd [-c]`
-   `-c / --clean` : Only displays the current folder (without path).

### unset
Removes environment variables.
Usage: `unset [VAR]`
