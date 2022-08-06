#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdbool.h>

void execute(char ** );
bool built_in(char ** );
void cd(char ** );
void pwd(char ** );
void type(char ** );
void help(char ** );
void update_PWD_OLDPWD(void);
void executable_program(char ** );
void redirection(char ** );

#endif
