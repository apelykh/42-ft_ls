/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 21:35:56 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/16 21:35:56 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

t_node_info	*lst_add_back(t_node_info *head, t_node_info *node_info)
{
	t_node_info *tmp;

	if (head)
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node_info;
		tmp->next->next = NULL;
	}
	return (head);
}

void		node_pre_free(t_node_info *node)
{
	ft_memdel((void**)&(node->owner_name));
	ft_memdel((void**)&(node->owner_group));
	ft_memdel((void**)&(node->last_mod_time));
	ft_memdel((void**)&(node->last_mod_date));
	ft_memdel((void**)&(node->last_mod_year));
}

void		lst_free(t_node_info *head)
{
	t_node_info *node;
	t_node_info *next;

	if (head)
	{
		node = head;
		while (node)
		{
			next = node->next;
			ft_memdel((void**)&(node->name));
			ft_memdel((void**)&(node->full_path));
			ft_memdel((void**)&(node->acc_rights));
			ft_memdel((void**)&(node));
			node = next;
		}
	}
}
