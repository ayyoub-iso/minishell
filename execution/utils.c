#include "../minishell.h"


bool  is_reder(int type)
{
   return (type >= 1 && type <= 4);
}

char  **get_char_env(char **envv, int set)
{
   static char **env;

   if (set)
      env = envv;
   return (env);
}

