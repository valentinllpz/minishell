/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:53:42 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/20 12:07:50 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redirect_from(void)
{
	int		fd;
	char	*buf;

	fd = open(((t_rdir *)g_shell->tmp_dir->content)->file, O_RDWR);
	if (fd == -1)
	{
		buf = strerror(errno);
		write(2, buf, ft_strlen_safe(buf));
		g_shell->error_flag = 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_error();
		if (close(fd) == -1)
			ft_error();
	}
	g_shell->tmp_dir = g_shell->tmp_dir->next;
}

void	ft_redirect_to_append(void)
{
	int	fd;

	fd = open(((t_rdir *)g_shell->tmp_dir->content)->file, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error();
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error();
	if (close(fd) == -1)
		ft_error();
	g_shell->tmp_dir = g_shell->tmp_dir->next;
}

void	ft_redirect_to(void)
{
	int	fd;
	
	fd = open(((t_rdir *)g_shell->tmp_dir->content)->file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		ft_error();
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_error();
	if (close(fd) == -1)
		ft_error();
	g_shell->tmp_dir = g_shell->tmp_dir->next;
}

void	ft_do_redirections(void)
{
	g_shell->tmp_dir = ((t_cmd *)g_shell->tmp_cmd->content)->rdir_lst;
	expansion_in_rdir_lst(((t_cmd *)g_shell->tmp_cmd->content)->rdir_lst, g_shell->env);
	while (g_shell->tmp_dir != NULL && g_shell->error_flag == 0)
	{
		if (((t_rdir *)g_shell->tmp_dir->content)->flag == 0)
		{
			write(2, "bash: ambigous redirect\r\n", 25);
			g_shell->error_flag = 1;
		}
		else if (((t_rdir *)g_shell->tmp_dir->content)->flag == 1)
			ft_redirect_to();
		else if (((t_rdir *)g_shell->tmp_dir->content)->flag == 3)
			ft_redirect_to_append();
		else if (((t_rdir *)g_shell->tmp_dir->content)->flag == 2)
			ft_redirect_from();
	}
}