# shell
This repository holds the source code for shell. The idea for the project is taken from OSTEP https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell , but the details are different.

To compile: **make all**.

## What can this shell do?
### Built-in commands:
#### cd
Change the shell working directory. For more information on options type **help cd** or visit https://en.wikipedia.org/wiki/Cd_(command).
#### pwd
Print the name of the current working directory.
#### type 
Display information about command type.
#### help
Display information about built-in commands.
#### exit
Quit the shell.
### Executable program
You can run any program whose path is contained in the **PATH** environment variable.
### Redirection
Redirection only works for executable programs.
### Multiple commands
You can run multiple commands on the same line by separating them from each other with a semicolon.
