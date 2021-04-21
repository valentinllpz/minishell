/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-garr <ade-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 17:40:33 by ade-garr          #+#    #+#             */
/*   Updated: 2021/04/15 19:37:12 by ade-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_execution(t_node *node)
{
	if (node->type == CMD)
	{
		ft_exec_cmd(node); // a modifier
	}
	else
	{
		launch_execution(node->left);
		launch_execution(node->right);
	}
}