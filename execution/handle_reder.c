#include "../minishell.h"

int get_permissions(int type)
{
   if (type == LESS)
      return (O_RDONLY);
   else if (type == GREATERGREATER)
      return (O_CREAT | O_WRONLY | O_APPEND);
   else
      return (O_CREAT | O_WRONLY | O_TRUNC);
}

int set_fd(t_exec *s, int reder_type, char *file)
{
   int perm;
   int fd;

   if (reder_type == LESSLESS || !s->run_it)
      return (1);
   perm = get_permissions(reder_type);
   fd = open(file, perm, 0644);
   if (fd == -1)
   {
      perror(file);
      return (s->run_it = false, 0);
   }
   if (reder_type == LESS && s->fd_in == 0)
      s->fd_in = fd;
   else if (reder_type == LESS)
      (1) && (close(s->fd_in), s->fd_in = fd);
   else if (s->fd_out != 1)
      close(s->fd_out);
   if (reder_type != LESS)
      s->fd_out = fd;
   return (1);
}
