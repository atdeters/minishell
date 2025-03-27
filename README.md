# Welcome to our Minishell!
Say hello and welcome to the project blahblahblah


# Installation & Setup
### Dependencies

The minishell program requires the following to compile and run:

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
The alias (.msh_alias) and history (.msh_history) files will not be stored when exiting and reopening this docker image. 
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
