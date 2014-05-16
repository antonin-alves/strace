/*
** trace.c for strace in /home/ubuntu/rendu/AUSP_strace
**
** Made by chauvo_t
** Login   <chauvo_t@epitech.net>
**
** Started on  Wed May 14 21:58:47 2014 chauvo_t
** Last update Sat May 17 00:57:56 2014 chauvo_t
*/

#include "strace.h"

pid_t	g_tracee_pid = -1;

int	step_instruction(pid_t pid, int *status)
{
  handle_exit(status);
  if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) == -1)
    {
      warn("trace PTRACE_SINGLESTEP error");
      return (FAILURE);
    }
  if (waitpid(pid, status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  return (SUCCESS);
}

int			analyse_registers(struct user_regs_struct *registers,
					  pid_t pid, int *status)
{
  unsigned long long	syscall_number;
  long			rip_pointed_data;

  if ((rip_pointed_data = ptrace(PTRACE_PEEKDATA, pid,
				 registers->rip, NULL)) == -1)
    {
      warn("ptrace PTRACE_PEEK_DATA error");
      return (FAILURE);
    }
  rip_pointed_data &= 0xffff;
  if (rip_pointed_data == SYSCALL_OPCODE)
    {
      syscall_number = registers->rax;
      if (step_instruction(pid, status) == FAILURE)
	return (FAILURE);
      if (ptrace(PTRACE_GETREGS, pid, NULL, registers) == -1)
	return (FAILURE);
      if (syscall_number > MAX_SYSCALL
	  || print_syscall(syscall_number, registers) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}

int				trace_process(pid_t pid)
{
  struct user_regs_struct	registers;
  int				status;

  if (waitpid(pid, &status, 0) == -1)
    {
      warn("wait error");
      return (FAILURE);
    }
  while (42)
    {
      if (ptrace(PTRACE_GETREGS, pid, NULL, &registers) == -1)
	{
	  warn("ptrace PTRACE_GETREGS error");
	  return (FAILURE);
	}
      if (analyse_registers(&registers, pid, &status) == FAILURE)
	return (FAILURE);
      if (step_instruction(pid, &status) == FAILURE)
	return (FAILURE);
    }
}

int	trace_by_pid(pid_t pid)
{
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1)
    {
      warn("ptrace PTRACE_ATTACH error");
      return (FAILURE);
    }
  g_tracee_pid = pid;
  if (trace_process(pid) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}

int	trace_by_cmd(char **cmd)
{
  pid_t	child;

  if ((child = fork()) == -1)
    {
      warn("fork error");
      return (FAILURE);
    }
  if (child == 0)
    {
      if (launch_child(cmd) == FAILURE)
	exit(EXIT_FAILURE);
    }
  else
    {
      g_tracee_pid = child;
      if (trace_process(child) == FAILURE)
      	return (FAILURE);
    }
  return (SUCCESS);
}
