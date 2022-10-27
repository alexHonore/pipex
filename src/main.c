/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:13:50 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/27 17:43:23 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
/*
int	init_parse(char **argv, char** envp)
{
	char	*PATH_from_envp;
	char	**mypaths;
	char	**mycmdargs;
	int		i;
	char	*cmd;

	i = -1;
	// retrieve the line PATH from envp
	PATH_from_envp = ft_substr(envp, 0, ft_strlen(envp));
	mypaths = ft_split(PATH_from_envp, ":");
	mycmdargs = ft_split(argv[2], " ");
	// in your child or parent process
	// perror("Error"); <- add perror after exceve() to debug
	while (mypaths[++i])
	{
		cmd = ft_join(mypaths[i], argv[2]); // protect your ft_join
		if (access(argv[2], ) == -1) // if execve succeeds, it exits
            execve(cmd, mycmdargs, envp);
        else
            throw_error("Command does not exists", 1);
		free(cmd); // if execve fails, we free and we try a new path
	}
	return (EXIT_FAILURE);
}*/
/*
void	pipex(int f1, int f2, char **argv, char **envp)
{
	int		end[2];
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
		return (perror("Fork: "));
	if (!parent) // if fork() returns 0, we are in the child process end[1], child write and parent end[0] read
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}
*/
void    pipex(char **argv, char **envp)
{
    int   fd[2];
    pid_t	pid1;
    
    if (pipe(fd) == -1)
		throw_error("pipe function failed", -1);
    pid1 = fork();
    if (pid1 < 0)
         throw_error("Fork failed", -1);
    if (pid1 == 0)
        child_process(argv, envp, fd);
    close(fd[0]);         // this is the parent
    waitpid(pid1, NULL, 0);  // while they finish their tasks
    parent_process(argv, envp, fd);
}
/*
int		execve(const char *path, char *const argv[], char *envp[]);
#path : the path to our command
        type `which ls` and `which wc` in your terminal
        you'll see the exact path to the commands' binaries
#argv []: the args the command needs, for ex. `ls -la`
          you can use your ft_split to obtain a char **
          like this { "ls", "-la", NULL }
          it must be null terminated
#envp : the environmental variable
        you can simply retrieve it in your main (see below)
        and pass it onto execve, no need to do anything here
        in envp you'll see a line PATH which contains all possible
        paths to the commands' binaries
int	main(int ac, char **ag, char **envp)
{
     int f1;
     int f2;

     f1 = open(ag[1], O_RDONLY);
     f2 = open(ag[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
     if (f1 < 0 || f2 < 0)
          return (-1);
     pipex(f1, f2, ag, envp);
     return (0);
}
*/
int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
        throw_error("Invalid number of arguments", -1);
	/*if (init_parse(argv, envp) == EXIT_FAILURE)
		return (0);*/
	pipex(argv, envp);
	return (0);
}