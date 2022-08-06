#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

char ** get_tokens(char * line)
{
     char ** tokens = (char **) calloc(num_of_tokens(line) + 1, sizeof(char *)); // +1 for NULL
     int i = 0;
     
     tokens[i] = strtok(line, " \t\n");
     while(tokens[i] != NULL)
	  tokens[++i] = strtok(NULL, " \t\n"); 
	  
     return tokens;
}
     
     

unsigned int num_of_tokens(const char * line)
{
     unsigned int tokens = 0;
     bool in_word = false;

     while(*line != '\0')
     {
	  if(isspace(*line) && in_word == true)
	       in_word = false;
	  else if((isalnum(*line) || ispunct(*line)) && in_word == false) 
	  {
	       tokens++;
	       in_word = true;
	  }
	  line++;
     }

     return tokens;
}

bool empty_string(const char * line)
{
     while(isspace(*line))
	  line++;

     return (*line == ';' || *line == '\0')? true : false;
}
		    
	       
	       

     
     
