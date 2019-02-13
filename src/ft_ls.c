/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:46:41 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/02 18:46:42 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>

void	ls_object(char *path, t_flags *flags, int n_flag, int name_flag)
{
	struct stat file_stat;

	if (lstat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			if (n_flag)
				ft_putchar('\n');
			if (name_flag)
			{
				ft_putstr(path);
				ft_putendl(":");
			}
			ls_dir(path, flags);
		}
		else
			ls_file(path, flags);
	}
	else
		handle_error(path, "Error", 0);
}

void	ls_files_group(char **files, int i_from, int i_to, t_flags *flags)
{
	struct stat		file_stat;
	t_node_info		*node;
	t_node_info		*head;

	head = NULL;
	while (i_from < i_to)
	{
		node = init_node(files[i_from], NULL, 0);
		if (lstat(node->full_path, &file_stat) == 0)
			set_node_info(node, &file_stat);
		if (!head)
			head = node;
		else
			lst_add_back(head, node);
		i_from++;
	}
	if (!head)
		return ;
	apply_list_ops(&head, flags, 0);
	lst_free(head);
}

void	ls_file(char *filename, t_flags *flags)
{
	t_node_info	*node;
	struct stat file_stat;
	int			*maxes;

	if (!flags->l_flag)
		ft_putendl(filename);
	else
	{
		node = init_node(filename, NULL, 0);
		if (lstat(node->name, &file_stat) == 0)
			set_node_info(node, &file_stat);
		maxes = init_maxes(node);
		count_spaces(node, maxes);
		print_node(node);
		free(maxes);
		lst_free(node);
	}
}

void	ls_dir(char *dirpath, t_flags *flags)
{
	struct dirent	*dp;
	struct stat		file_stat;
	t_node_info		*node;
	t_node_info		*head;
	DIR				*dirp;

	head = NULL;
	if (!(dirp = opendir(dirpath)) && handle_error(dirpath, NULL, 0))
		return ;
	while ((dp = readdir(dirp)))
	{
		node = init_node(dp->d_name, dirpath, 1);
		if (lstat(node->full_path, &file_stat) == 0)
			set_node_info(node, &file_stat);
		else if (handle_error(dp->d_name, NULL, 0))
			continue;
		head = (head ? lst_add_back(head, node) : node);
	}
	if (!head)
		return ;
	apply_list_ops(&head, flags, 1);
	if (flags->rb_flag)
		recursive_ls_dir(head, flags);
	closedir(dirp);
	lst_free(head);
}

void	recursive_ls_dir(t_node_info *head, t_flags *flags)
{
	t_node_info *tmp;

	tmp = head;
	while (tmp)
	{
		if (((tmp->name)[0] != '.' && !flags->a_flag && !flags->f_flag) ||
			((flags->a_flag || flags->f_flag) && (ft_strcmp(tmp->name, ".."))
			&& (ft_strcmp(tmp->name, "."))))
			if ((tmp->acc_rights)[0] == 'd')
			{
				ft_putchar('\n');
				ft_putstr(tmp->full_path);
				ft_putendl(":");
				ls_dir(tmp->full_path, flags);
			}
		tmp = tmp->next;
	}
}
