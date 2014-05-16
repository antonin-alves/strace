/*
** print_types2.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Thu May 15 00:57:02 2014 chauvo_t
** Last update Fri May 16 10:34:35 2014 Thomas de Beauchene
*/

#include "strace.h"

extern pid_t	g_tracee_pid;

static void	print_char(char c)
{
  if ((c > 32 && c < 127) || c == ' ' || c == '\0')
    (void)fprintf(stderr, "%c", c);
  else if (c != '\n')
    (void)fprintf(stderr, "\\%o", c);
}

void	print_string(unsigned long long int register_value)
{
  char	c;

  (void)fprintf(stderr, "\"");
  c = -1;
  while (c != '\0')
    {
      if ((c = ptrace(PTRACE_PEEKDATA, g_tracee_pid,
		      register_value, NULL)) == -1)
	{
	  warn("ptrace PTRACE_PEEK_DATA error");
	  return ;
	}
      print_char(c);
      ++register_value;
    }
  (void)fprintf(stderr, "\"");
}

void	print_unimplemented(unsigned long long int register_value)
{
  (void)register_value;
  (void)fprintf(stderr, "unimplemented");
}

void	print_nothing(unsigned long long int register_value)
{
  (void)register_value;
}
