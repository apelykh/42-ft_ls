/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 15:17:44 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/26 15:17:45 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

void	print_lnk_src(t_node_info *node)
{
	char	buf[MAX_PATH_LEN];
	size_t	i;

	if (node->full_path)
		i = readlink(node->full_path, buf, MAX_PATH_LEN);
	else
		i = readlink(node->name, buf, MAX_PATH_LEN);
	buf[i] = '\0';
	ft_putstr(" -> ");
	ft_putstr(buf);
}

void	print_list(t_node_info *head, t_flags *flags)
{
	t_node_info	*tmp;

	tmp = head;
	while (tmp)
	{
		if (((tmp->name)[0] != '.' && !flags->a_flag && !flags->f_flag) ||
			(flags->a_flag || flags->f_flag))
		{
			if (!flags->l_flag)
			{
				ft_putstr(tmp->name);
				ft_putchar('\n');
			}
			else
				print_node(tmp);
		}
		node_pre_free(tmp);
		tmp = tmp->next;
	}
}

void	print_dev_nums(t_node_info *node)
{
	if ((node->acc_rights)[0] == 'd' || (node->acc_rights)[0] == 'l')
		print_padded_str(NULL, num_len(node->dev_major) + 1);
	else
	{
		ft_putnbr(node->dev_major);
		ft_putchar(',');
	}
	print_padded_str(NULL, node->spaces[7]);
	ft_putnbr(node->dev_minor);
}

void	print_padded_str(char *str, int pad_n)
{
	int i;

	i = 0;
	if (str)
		ft_putstr(str);
	while (i++ < pad_n)
		ft_putchar(' ');
}

void	print_node(t_node_info *node)
{
	print_padded_str(node->acc_rights, node->spaces[0]);
	ft_putnbr(node->num_links);
	print_padded_str(NULL, node->spaces[1]);
	print_padded_str(node->owner_name, node->spaces[2]);
	print_padded_str(node->owner_group, node->spaces[3]);
	if (ft_strstr(node->full_path, "/dev") == node->full_path &&
		ft_strcmp(node->name, ".") && ft_strcmp(node->name, "..") &&
		node->full_path)
	{
		print_dev_nums(node);
	}
	else
	{
		print_padded_str(NULL, num_len(node->dev_major) + 1);
		ft_putlonglong(node->size_bytes);
	}
	print_padded_str(NULL, node->spaces[4]);
	print_padded_str(node->last_mod_date, node->spaces[5]);
	print_padded_str((compare_timestamp(node->mod_time) ?
		node->last_mod_year : node->last_mod_time), node->spaces[6]);
	ft_putstr(node->name);
	if ((node->acc_rights)[0] == 'l')
		print_lnk_src(node);
	ft_putchar('\n');
}
