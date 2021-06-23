/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:28:27 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/23 15:52:08 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_heredoc_content(t_shell *shell, char *file)
{
	char	*buff;
	int		ret;
	t_list	*heredoc_lst;

	ret = 1;
	heredoc_lst = NULL;
	while (ret > 0)
	{
		write(shell->tmp_stdout, "> ", 2);
		ret = get_next_line(shell->tmp_stdin, &buff);
		if (ft_strcmp(file, buff) == 0)
			break ;
		ft_lstadd_back(&heredoc_lst, ft_lstnew(buff));
	}
	return (heredoc_lst);
}

void	ft_heredoc(t_shell *shell, char *file)
{
	int		fd[2];
	t_list	*heredoc_lst;
	t_list	*tmp;

	heredoc_lst = get_heredoc_content(shell, file);
	pipe(fd);
	dup2(fd[0], 0);
	while (heredoc_lst)
	{
		ft_putstr_fd(((char *)heredoc_lst->content), fd[1]);
		write(fd[1], "\n", 1);
		free(((char *)heredoc_lst->content));
		tmp = heredoc_lst;
		heredoc_lst = heredoc_lst->next;
		free(tmp);
	}
	close(fd[0]);
	close(fd[1]);
	shell->tmp_rdir = shell->tmp_rdir->next;
}
