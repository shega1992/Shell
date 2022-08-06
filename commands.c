#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void execute(char ** tokens)
{
     if(built_in(tokens))
	  ;
     else
	  executable_program(tokens);
}

bool built_in(char ** tokens)
{
     if(!strcmp(tokens[0], "cd"))
     {
	  cd(tokens);
	  free(tokens);
	  return true;
     }
     else if(!strcmp(tokens[0], "pwd"))
     {
	  pwd(tokens);
	  free(tokens);
	  return true;
     }
     else if(!strcmp(tokens[0], "type"))
     {
	  type(tokens);
	  free(tokens);
	  return true;
     }
     else if(!strcmp(tokens[0], "help"))
     {
	  help(tokens);
	  free(tokens);
	  return true;
     }	       
     else if(!strcmp(tokens[0], "exit"))
     {
          free(*tokens);
	  free(tokens);
	  exit(0);
     }
	  
     return false;
}

void cd(char ** tokens)
{
     FILE * fp;
     char * path;
     char * line = NULL;
     size_t len = 0;
     ssize_t nread;
     int count = 0;
     
     while(tokens[count] != NULL)
	  count++;

     switch(count)
     {
     case 1:
	  if(chdir(getenv("HOME")) == -1)
	       fprintf(stderr, "wish: cannot change to home directory\n");
	  else
	       update_PWD_OLDPWD();
	  break;
     case 2:
	  if(!strcmp(tokens[1], "~"))
	  {
	       if(chdir(getenv("HOME")) == -1)
		    fprintf(stderr, "wish: cannot change to home directory\n");
	       else
		    update_PWD_OLDPWD();
	  }
	  else if(tokens[1][0] == '~' && tokens[1][1] == '/')
	  {
	       path = (char *) calloc(strlen(getenv("HOME")) + strlen(&tokens[1][1]) + 1, sizeof(char));
	       strcpy(path, getenv("HOME"));
	       strcat(path, &tokens[1][1]);

	       if(chdir(path) == -1)
		    fprintf(stderr, "wish: cannot change directory\n");
	       else
		    update_PWD_OLDPWD();
	       
	       free(path);
	  }
	  else if(tokens[1][0] == '~' && (isalpha(tokens[1][1]) || tokens[1][1] == '_'))
	  {
	       if((fp = fopen("/etc/passwd", "r")) == NULL)
		    fprintf(stderr, "cannot open /etc/passwd\n");
	       else
	       {
		    while((nread = getline(&line, &len, fp)) != -1
			  && strncmp(line, &tokens[1][1], strlen(&tokens[1][1])))
			 ;
		    if(nread == -1)
			 fprintf(stderr, "Username \"%s\" does not exist\n", &tokens[1][1]);
		    else
		    {
			 path = line;
			 // omit 5 colons and select 6th field
			 for(int i = 0; i < 5; i++) 
			 {
			      path = strchr(path, ':');
			      path++;
			 }
			 if(chdir(strtok(path, ":")) == -1)
			      fprintf(stderr, "wish: cannot change directory\n");
			 else
			      update_PWD_OLDPWD();
		    }
		    fclose(fp);
		    free(line);
	       }
	  }
	  else if(!strcmp(tokens[1], "-"))
	  {
	       if(chdir(getenv("OLDPWD")) == -1)
			 fprintf(stderr, "wish: previous working directory is not defined\n");
	       else
		    update_PWD_OLDPWD();
	  }
	  else if(chdir(tokens[1]) == -1)
	       fprintf(stderr, "wish: cannot change directory\n");
	  else
	       update_PWD_OLDPWD();
	  break;
     default:
	  fprintf(stderr, "usage: cd [arg]\n");
	  break;
     }
}

void pwd(char ** tokens)
{
     if(tokens[1] != NULL)
	  fprintf(stderr, "usage: pwd\n");
     else
	  printf("%s\n", getenv("PWD"));

}

void type(char ** tokens)
{
     char * path;

     if(tokens[1] == NULL)
	  ;
     else
	  for(int i = 1; tokens[i] != NULL; i++)
	  {
	       if(!strcmp(tokens[i], "cd") || !strcmp(tokens[i], "pwd") ||
		  !strcmp(tokens[i], "type") || !strcmp(tokens[i], "help") ||
		  !strcmp(tokens[i], "exit"))	     
		    printf("%s is built-in command\n", tokens[i]);
	       else
	       {
		    path = (char *) calloc(strlen("/usr/bin/") + strlen(tokens[i] + 1) + 1, sizeof(char));
		    strcpy(path, "/usr/bin/");
		    strcat(path, tokens[i]);
		    (!access(path, X_OK))? printf("%s is %s\n", tokens[i], path) :
			 printf("wish: type: %s was not found\n", tokens[i]);
		    free(path);
	       }
	  }
}
	       

void help(char ** tokens)
{
     if(tokens[1] == NULL)
	  printf("Built-in commands:\n"
		 "cd\n"
		 "pwd\n"
		 "help\n"
		 "exit\n"
		 "To get information about command enter help followed by command\n");
     else
	  for(int i = 1; tokens[i] != NULL; i++)
	  {
	       if(!strcmp(tokens[i], "cd"))
		  printf("cd command usage: cd [arg]\n"
			 "Change the shell working directory.\n"
                         "Description:\n"
			 "cd by itself or cd ~ will always put the user in their home directory.\n"
			 "cd . will leave the user in the same directory they are currently in.\n"
			 "cd ~username will put the user in the username's home directory.\n"
			 "cd dir (without a /) will put the user in a subdirectory.\n"
			 "cd .. will move the user up one directory.\n"
			 "cd - will switch the user to the previous directory.\n");
	       else if(!strcmp(tokens[i], "pwd"))
		    printf("pwd command usage: pwd\n"
			   "Print the name of the current working directory.\n");
	       else if(!strcmp(tokens[i], "type"))
		    printf("type command usage: type [command ...]\n"
			   "Display information about command type\n");
	       else if(!strcmp(tokens[i], "help"))
		    printf("help command usage: help [built-in command ...]\n"
			   "Display information about built-in commands.\n");
	       else if(!strcmp(tokens[i], "exit"))
		    printf("exit command usage: exit\n"
			   "Quit the shell\n");
	       else
		    fprintf(stderr, "%s: built-in command was not found\n", tokens[i]);
	  }
}
     
     
void update_PWD_OLDPWD(void)
{
     char * buf = getcwd(NULL, 0);
     setenv("OLDPWD", getenv("PWD"), 1);
     setenv("PWD", buf, 1);
     free(buf);
}
     
void executable_program(char ** tokens)
{
     int rc = fork();
     if(rc < 0)
     {
	  fprintf(stderr, "wish: fork failed\n");
	  exit(1);
     }
     else if(rc == 0)
     {
	  redirection(tokens);
	  execvp(tokens[0], tokens);
	  fprintf(stderr, "wish: %s: command was not found\n", tokens[0]);
	  exit(1);
     }
     else
     {
	  wait(NULL);
	  free(tokens);
     }
}

void redirection(char ** tokens)
{
     int i = 1;
     
     while(tokens[i] != NULL && strcmp(tokens[i], ">")) 
	  i++;
     
     if(tokens[i] == NULL)
	  ;
     else
     {
	  tokens[i++] = NULL;
	  fclose(stdout);
	  if(fopen(tokens[i], "w") == NULL)
	       fprintf(stderr, "wish: cannot open %s\n", tokens[i]);
     }
}
	  
	       
	       
     
	  
