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
## What is the difference between this shell and the OSTEP and bash shell?
### Built-in commands:
#### cd
The **cd** command does not work as stated in **OSTEP**. Rather, its behavior is closer to the behavior of the **cd** command in **bash**. The **cd** command does not accept options, unlike the **bash** version.
#### pwd
The **pwd** command also does not accept options, unlike the **bash** version and throws an error when trying to pass an argument.
#### type
In process.
#### help
The **help** command is a simplified version of a similar **bash** command. The command does not accept options.
#### exit
The **exit** command does not work as stated in **OSTEP**. Unlike the OSTEP version, the command ignores any arguments passed to it.
### Few words about the path command
There is no **path** command in my shell, unlike the **OSTEP** version. I don't understand why this command is needed. My opinion is that the development of such a command will significantly complicate the structure of the project and potentially lead to various errors.
### Executable program
I've used **execvp** instead of **execv** when implementing a function that works with executable programs. *Why reinvent the wheel?*
### Redirection
My shell does not redirect the standard error output to a file, unlike the **OSTEP** version. The user wants to see his(her) mistakes on the screen, doesn't he(she)?
### Multiple commands(Parallel commands)
I've used the **;** symbol to run multiple commands on the same line (the OSTEP version uses the **&** symbol). One important difference from the **bash** version: the **bash** version throws a syntax error, for example, when trying to run such a combination: *command ; 0 or more spaces ; command*. My version of the shell handles similar cases in a different way, which allows commands to be executed.

