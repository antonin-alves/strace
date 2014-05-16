/*
** main.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Mon May 12 23:47:03 2014 chauvo_t
** Last update Fri May 16 10:35:19 2014 Thomas de Beauchene
*/

#include "strace.h"

extern pid_t	g_tracee_pid;

static void	sig_handler(int signum)
{
  (void)signum;
  if (ptrace(PTRACE_DETACH, g_tracee_pid, NULL, NULL) == -1)
    warn("ptrace PTRACE_DETACH error");
  exit(EXIT_SUCCESS);
}

static int	get_args(int ac, char **av, char ***cmd)
{
  if (ac < 2)
    return (FAILURE);
  if (!strcmp(av[1], "-p") && ac > 2)
    return (atoi(av[2]));
  *cmd = av + 1;
  return (SUCCESS);
}

int	main(int ac, char **av)
{
  char	**cmd;
  int	ret_value;

  if ((ret_value = get_args(ac, av, &cmd)) == FAILURE)
    {
      fprintf(stderr, "USAGE:\n%s [command]\n%s [-p [pid]]\n", av[0], av[0]);
      return (EXIT_FAILURE);
    }
  if (signal(SIGINT, &sig_handler) == SIG_ERR
      || signal(SIGTERM, &sig_handler) == SIG_ERR)
    {
      warn("signal error");
      return (EXIT_FAILURE);
    }
  if (ret_value == SUCCESS)
    ret_value = trace_by_cmd(cmd);
  else
    ret_value = trace_by_pid(ret_value);
  if (ret_value == FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
