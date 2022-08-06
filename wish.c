#include "token.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
     char * line = NULL;
     char * cmd;
     FILE * fp;
     size_t len = 0;

     if(argc == 1)
	  while(true)
	  {
	       printf("wish: %s > ", getenv("PWD"));
	       if(getline(&line, &len, stdin) == -1)
	       {
		    putchar('\n');
		    break;
	       }
	       else if(empty_string(line))
		    continue;
	       
	       if(strchr(line, ';'))
	       {   
		    while((cmd = strsep(&line, ";")) != NULL)
		    {
			 if(empty_string(cmd))
			      continue;
			 else
			      execute(get_tokens(cmd));
		    }
	       }
	       else
		    execute(get_tokens(line));
	  }
     else if(argc == 2)
     {
	  if((fp = fopen(argv[1], "r")) == NULL)
	  {
	       fprintf(stderr, "cannot open %s\n", argv[1]);
	       exit(1);
	  }

	  while(getline(&line, &len, fp) != -1)
	  {
	       if(empty_string(line))
		    continue;

	       if(strchr(line, ';'))
	       {
		    while((cmd = strsep(&line, ";")) != NULL)
		    {
			 if(empty_string(cmd))
			      continue;
			 else
			      execute(get_tokens(cmd));
		    }
	       }
	       else
		    execute(get_tokens(line));
	  }
     }
     else
	  fprintf(stderr, "wish: too many arguments for wish\n"
		  "usage: wish [arg]\n");
		    
     free(line);
     return 0;
}


     
