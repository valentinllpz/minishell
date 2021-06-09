/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 14:28:27 by vlugand-          #+#    #+#             */
/*   Updated: 2021/06/09 17:34:48 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_heredoc(t_shell *shell, char *file)
{
	int		fd[2];
	int		ret;
	char	*buff;
	t_list	*heredoc;
	t_list	*tmp;

	pipe(fd);
	ret = 1;
	heredoc = NULL;
	while (ret > 0)
	{
		write(shell->tmp_stdout, "> ", 2);
		ret = get_next_line(shell->tmp_stdin, &buff);
		if (ft_strcmp(file, buff) == 0)
			break ;
		ft_lstadd_back(&heredoc, ft_lstnew(buff));
	}
	dup2(fd[0], 0);
	while (heredoc)
	{
		ft_putstr_fd(((char *)heredoc->content), fd[1]);
		write(fd[1], "\n", 1);
		free(((char *)heredoc->content));
		tmp = heredoc;
		heredoc = heredoc->next;
		free(tmp);
	}
	close(fd[0]);
	close(fd[1]);
	shell->tmp_rdir = shell->tmp_rdir->next;
}
