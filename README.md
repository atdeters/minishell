# Welcome to our Minishell!
Say hello and welcome to the project blahblahblah


# Installation & Setup
To get the program and compile it, run the following command in your terminal:
```sh
git  clone https://github.com/atdeters/minishell.git && cd minishell && make
```
## Dependencies

Your minishell requires the following to compile and run:

- GNU Make

- GCC or Clang

- Readline library (for command-line input handling)

Install Dependencies (Debian-based systems like Ubuntu):

```sh

sudo apt update && sudo apt install -y build-essential libreadline-dev
```
Install  Dependencies (MacOS –  Homebrew  required):
```sh

brew install readline

```

Once compiled, start the shell with:
```sh
./minishell
```


# Features
Descripe which features are in it.
- Built-in Functions
- Permanent History List
- Permanent Alias List
- Show Folder in Prompt
- Show Git in Prompt

## Built-in Functions
### alias
Set or display aliases for commands.
Usage: `alias [flags] alias[=expansion]`
-	`alias` (without arguments) displays all active aliases.
-	`alias -r` removes alias permanently.
-	`alias "st= git status"` sets "st" as alias for "git status"
-	`alias st` displays the corresponding alias with its expansion

### biman
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
