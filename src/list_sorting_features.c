/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting_features.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 22:39:58 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/09 22:39:58 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

int		ft_nodetimecmp(t_node_info *n1, t_node_info *n2)
{
	if (n1->ts.tv_sec != n2->ts.tv_sec)
		return ((int)(n2->ts.tv_sec - n1->ts.tv_sec));
	else if (n1->ts.tv_nsec != n2->ts.tv_nsec)
		return ((int)(n2->ts.tv_nsec - n1->ts.tv_nsec));
	else
		return (ft_nodestrcmp(n1, n2));
}

int		ft_revnodetimecmp(t_node_info *n1, t_node_info *n2)
{
	return (ft_nodetimecmp(n2, n1));
}

int		ft_nodestrcmp(t_node_info *n1, t_node_info *n2)
{
	return (ft_strcmp(n1->name, n2->name));
}

int		ft_revnodestrcmp(t_node_info *n1, t_node_info *n2)
{
	return (ft_strcmp(n2->name, n1->name));
}
