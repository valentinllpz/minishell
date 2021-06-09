/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:53:42 by ade-garr          #+#    #+#             */
/*   Updated: 2021/06/09 16:49:58 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_from(t_shell *shell)
{
	int		fd;
	char	*buf;

	fd = open(((t_rdir *)shell->tmp_rdir->content)->file, O_RDWR);
	if (fd == -1)
	{
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		write(2, "\r\n", 2);
		shell->error_flag = 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_error(shell);
		if (close(fd) == -1)
			ft_error(shell);
	}
	shell->tmp_rdir = shell->tmp_rdir->next;
}

void	ft_redirect_to_append(t_shell *shell)
{
	int	fd;

	fd = open(((t_rdir *)shell->tmp_rdir->content)->file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error(shell);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(shell);
	if (close(fd) == -1)
		ft_error(shell);
	shell->tmp_rdir = shell->tmp_rdir->next;
}

void	ft_redirect_to(t_shell *shell)
{
	int	fd;
	
	fd = open(((t_rdir *)shell->tmp_rdir->content)->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error(shell);
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error(shell);
	if (close(fd) == -1)
		ft_error(shell);
	shell->tmp_rdir = shell->tmp_rdir->next;
}

void	ft_do_redirections(t_shell *shell)
{
	shell->tmp_rdir = ((t_cmd *)shell->tmp_cmd->content)->rdir_lst;
	expansion_in_rdir_lst(((t_cmd *)shell->tmp_cmd->content)->rdir_lst, shell->env);
	while (shell->tmp_rdir != NULL && shell->error_flag == 0)
	{
		if (((t_rdir *)shell->tmp_rdir->content)->flag == 0)
		{
			write(2, "minishell: ", 11);
			ft_putstr_fd(((t_rdir *)shell->tmp_rdir->content)->file, 2);
			write(2, ": ambigous redirect\r\n", 21);
			shell->error_flag = 1;
		}
		else if (((t_rdir *)shell->tmp_rdir->content)->flag == 1)
			ft_redirect_to(shell);
		else if (((t_rdir *)shell->tmp_rdir->content)->flag == 3)
			ft_redirect_to_append(shell);
		else if (((t_rdir *)shell->tmp_rdir->content)->flag == 2)
			ft_redirect_from(shell);
		else if (((t_rdir *)shell->tmp_rdir->content)->flag == 4)
			ft_heredoc(shell, ((t_rdir *)shell->tmp_rdir->content)->file);
	}
}
