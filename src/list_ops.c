/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:18:45 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/23 16:18:46 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

int		*init_maxes(t_node_info *node)
{
	int *maxes;

	maxes = (int *)malloc(sizeof(int) * 5);
	maxes[0] = num_len(node->num_links);
	maxes[1] = (int)ft_strlen(node->owner_name);
	maxes[2] = (int)ft_strlen(node->owner_group);
	maxes[3] = (ft_strstr(node->full_path, "/dev") == node->full_path) ?
		num_len(node->dev_major) : num_len(node->size_bytes);
	maxes[4] = (ft_strstr(node->full_path, "/dev") == node->full_path) ?
		num_len(node->dev_minor) : 0;
	return (maxes);
}

void	update_maxes(t_node_info *node, int *maxes)
{
	maxes[0] = MAX(num_len(node->num_links), maxes[0]);
	maxes[1] = MAX((int)ft_strlen(node->owner_name), maxes[1]);
	maxes[2] = MAX((int)ft_strlen(node->owner_group), maxes[2]);
	maxes[3] = (ft_strstr(node->full_path, "/dev") == node->full_path) ?
		MAX(num_len(node->dev_major), maxes[3]) :
		MAX(num_len(node->size_bytes), maxes[3]);
	maxes[4] = (ft_strstr(node->full_path, "/dev") == node->full_path) ?
		MAX(num_len(node->dev_minor), maxes[4]) : 0;
}

void	count_list_maxes(t_node_info *head, t_flags *flags, int if_total)
{
	t_node_info	*tmp;
	int			*maxes;
	int			total;

	total = 0;
	tmp = head;
	maxes = init_maxes(tmp);
	while (tmp)
	{
		if (((tmp->name)[0] != '.' && !flags->a_flag) || flags->a_flag ||
				flags->f_flag)
		{
			total += tmp->num_blocks;
			update_maxes(tmp, maxes);
		}
		tmp = tmp->next;
	}
	if (flags->l_flag && if_total)
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
	count_spaces(head, maxes);
	free(maxes);
}

void	count_spaces(t_node_info *head, int maxes[5])
{
	t_node_info	*tmp;

	tmp = head;
	while (tmp)
	{
		tmp->spaces[0] = 2 + maxes[0] - num_len(tmp->num_links);
		tmp->spaces[1] = 1;
		tmp->spaces[2] = 2 + maxes[1] - (int)ft_strlen(tmp->owner_name);
		tmp->spaces[3] = maxes[2] - (int)ft_strlen(tmp->owner_group);
		if ((ft_strstr(tmp->full_path, "/dev") == tmp->full_path)
			&& tmp->full_path)
		{
			tmp->spaces[3] += 3;
			tmp->spaces[3] += maxes[3] - num_len(tmp->dev_major);
		}
		else
			tmp->spaces[3] += maxes[3] - num_len(tmp->size_bytes);
		tmp->spaces[7] = ((ft_strstr(tmp->full_path, "/dev") == tmp->full_path)
			&& tmp->full_path) ? (maxes[4] - num_len(tmp->dev_minor) + 1) : 0;
		tmp->spaces[4] = 1;
		tmp->spaces[5] = compare_timestamp(tmp->mod_time) ? 2 : 1;
		tmp->spaces[6] = 1;
		tmp = tmp->next;
	}
}

void	apply_list_ops(t_node_info **head, t_flags *flags, int if_total)
{
	count_list_maxes(*head, flags, if_total);
	apply_sorting(head, flags);
	print_list(*head, flags);
}
