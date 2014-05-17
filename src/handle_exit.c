/*
** handle_exit.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Fri May 16 19:22:06 2014 chauvo_t
** Last update Sat May 17 00:54:52 2014 chauvo_t
*/

#include "../include/strace.h"

static void	print_signal(int *status)
{
  if (WSTOPSIG(*status) == SIGSEGV)
    fprintf(stderr, "SIGSEGV\n");
  else if (WSTOPSIG(*status) == SIGTERM)
    fprintf(stderr, "SIGTERM\n");
  else if (WSTOPSIG(*status) == SIGINT)
    fprintf(stderr, "SIGINT\n");
  else if (WSTOPSIG(*status) == SIGKILL)
    fprintf(stderr, "SIGKILL\n");
  else if (WSTOPSIG(*status) == SIGPIPE)
    fprintf(stderr, "SIGPIPE\n");
  else if (WSTOPSIG(*status) == SIGQUIT)
    fprintf(stderr, "SIGQUIT\n");
  else if (WSTOPSIG(*status) == SIGFPE)
    fprintf(stderr, "SIGFPE\n");
  else if (WSTOPSIG(*status) == SIGBUS)
    fprintf(stderr, "SIGBUS\n");
  else if (WSTOPSIG(*status) == SIGSYS)
    fprintf(stderr, "SIGSYS\n");
  else if (WSTOPSIG(*status) == SIGSTKFLT)
    fprintf(stderr, "SIGSTKFLT\n");
  else if (WSTOPSIG(*status) == SIGABRT)
    fprintf(stderr, "SIGABRT\n");
}

void	handle_exit(int *status)
{
  if (WIFEXITED(*status))
    exit(EXIT_SUCCESS);
  if (!(WIFSTOPPED(*status)
	&& (WSTOPSIG(*status) == SIGSEGV || WSTOPSIG(*status) == SIGTERM
	    || WSTOPSIG(*status) == SIGINT || WSTOPSIG(*status) == SIGKILL
	    || WSTOPSIG(*status) == SIGPIPE || WSTOPSIG(*status) == SIGQUIT
	    || WSTOPSIG(*status) == SIGFPE || WSTOPSIG(*status) == SIGBUS
	    || WSTOPSIG(*status) == SIGSYS || WSTOPSIG(*status) == SIGSTKFLT
	    || WSTOPSIG(*status) == SIGABRT)))
    return ;
  fprintf(stderr, "tracee was terminated by default action of signal ");
  print_signal(status);
  exit(EXIT_SUCCESS);
}