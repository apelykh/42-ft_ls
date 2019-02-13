/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 20:37:09 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/09 20:37:09 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

t_node_info	*get_prev_node(t_node_info *head, t_node_info *x)
{
	t_node_info *prev;
	t_node_info *tmp;

	prev = NULL;
	if (head == x)
		return (prev);
	tmp = head;
	while (tmp && tmp != x)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
}

void		swap_nodes_links(t_node_info **head, t_node_info **x,
							t_node_info **y)
{
	t_node_info *prev_x;
	t_node_info *prev_y;
	t_node_info *temp;

	if (x == y || !(*head) || !x || !y)
		return ;
	prev_x = get_prev_node(*head, *x);
	prev_y = get_prev_node(*head, *y);
	if (prev_x)
		prev_x->next = *y;
	if (prev_y)
		prev_y->next = *x;
	temp = (*x)->next;
	(*x)->next = (*y)->next;
	(*y)->next = temp;
	if ((*head) == (*x))
		*head = *y;
	else if ((*head) == (*y))
		*head = *x;
}

void		sort_list(t_node_info **head,
						int (*f)(t_node_info *, t_node_info *))
{
	t_node_info *node;
	t_node_info *inner_node;
	t_node_info *min;

	if (!(*head) || !(*head)->next)
		return ;
	node = *head;
	while (node)
	{
		min = node;
		inner_node = node->next;
		while (inner_node)
		{
			if (f(inner_node, min) < 0)
				min = inner_node;
			inner_node = inner_node->next;
		}
		if (min != node)
		{
			swap_nodes_links(head, &node, &min);
			node = min;
		}
		node = node->next;
	}
}

void		apply_sorting(t_node_info **head, t_flags *flags)
{
	if (!flags->f_flag)
	{
		sort_list(head, ft_nodestrcmp);
		if (!flags->r_flag && flags->t_flag)
			sort_list(head, ft_nodetimecmp);
		else if (flags->r_flag)
			sort_list(head, (flags->t_flag ? ft_revnodetimecmp :
											ft_revnodestrcmp));
	}
}
