#include "../minishell.h"


t_exec *new_exec(void)
{
   t_exec   *new;

   new = malloc(sizeof(t_exec));
   if (!new)
      return (NULL);
   new->cmd = NULL;
   new->opt = NULL;
   new->run_it = true;
   new->fd_in = 0;
   new->fd_out = 1;
   new->next = NULL;
   return (new);
}


void  add_back_exec(t_exec **head, t_exec *new)
{
   t_exec   *tmp;

   if (!head || !new)
      return ;
   if (!*head)
      *head = new;
   else
   {
      tmp = *head;
      while (tmp->next)
         tmp = tmp->next;
      tmp->next = new;
   }
}

char  **get_options(t_parser **s, t_exec *new)
{
   t_parser          *tmp;
   int               i;
   char              **opts;

   (1) && (i = 0, tmp = *s);
   while (tmp && tmp->type != PIPE)
   {
      if (is_reder(tmp->type))
         tmp = tmp->next->next;
      else
      {
         i++;
         tmp = tmp->next;
      }
   }
   opts = malloc(sizeof(char *) * (i + 1));
   if (!opts)
      return (NULL);
   (1) && (opts[i] = NULL, i = 0);
   while (*s && (*s)->type != PIPE)
   {
      if (is_reder((*s)->type))
      {
         set_fd(new, (*s)->type, (*s)->next->token);
         *s = (*s)->next->next;
      }
      else
      {
         opts[i++] = ft_strdup((*s)->token);
         if (!opts[i - 1])
            return (NULL);
         *s = (*s)->next;
      }
   }
   (*s) && (*s = (*s)->next);
   return (opts);
}

int   pipe_count(t_exec *h)
{
   int   i;

   i = 0;
   while (h)
   {
      i++;
      h = h->next;
   }
   return (i);
}

t_exec   *setup_exec_list(t_parser *s, t_minishell *msh)
{
   t_exec   *tmp;
   t_exec   *head;
   char     **opts;

   (1) && (head = NULL, msh->p_count = 0);
   while (s)
   {
      tmp = new_exec();
      if (!tmp)
         return (NULL);
      opts = get_options(&s, tmp);
      if (!opts)
         return (NULL);
      tmp->cmd = opts[0];
      tmp->opt = opts;
      add_back_exec(&head, tmp);
      msh->p_count++;
   }
   return (head);
}
