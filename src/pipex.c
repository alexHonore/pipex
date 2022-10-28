/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshimiy <anshimiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:03:45 by anshimiy          #+#    #+#             */
/*   Updated: 2022/10/28 16:02:12 by anshimiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_free_str_array(paths);
	return (0);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = find_path(cmd[0], envp);
	if (!path)	
	{
		ft_free_str_array(cmd);
		throw_error("Error occured at execute", 1);
	}
	if (execve(path, cmd, envp) == -1)
		throw_error("Error occured at execute", 1);
}

void child_process(char **argv, char **envp, int *fd)
{
    int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
    if (filein == -1)
		throw_error("Error occured at child process", 1);
    if (dup2(fd[1], STDIN_FILENO) < 0)
        throw_error("Error occured at child process", 1);
    if (dup2(filein, STDOUT_FILENO) < 0)
        throw_error("Error occured at child process", 1);
    close(fd[0]);
    execute(argv[2], envp);
}

/* Parent process that take the data from the pipe, change the output for the
 fileout and also close with the exec function */
void	parent_process(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fileout == -1)
		throw_error("Error occured at parent process", -1);
    if (dup2(fd[0], STDIN_FILENO) < 0)
        throw_error("Error occured at parent process", -1);
    if (dup2(fileout, STDOUT_FILENO) < 0)
        throw_error("Error occured at parent process", -1);
	close(fd[1]);
	execute(argv[3], envp);
}
