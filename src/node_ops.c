/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/23 16:25:37 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/23 16:25:40 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

t_node_info	*init_node(char *name, char *path, int is_dir)
{
	t_node_info *node;

	node = (t_node_info *)malloc(sizeof(t_node_info));
	node->next = NULL;
	node->name = ft_strdup(name);
	if (is_dir && path)
	{
		node->full_path = ft_strnew(ft_strlen(path) + 1 + ft_strlen(name));
		ft_strcat(node->full_path, path);
		ft_strcat(node->full_path, "/");
		ft_strcat(node->full_path, name);
	}
	else
		node->full_path = ft_strdup(name);
	return (node);
}

void		set_file_mode(char *acc_rights, struct stat *file_stat, int *i)
{
	if (S_ISDIR(file_stat->st_mode))
		acc_rights[(*i)++] = 'd';
	else if (S_ISLNK(file_stat->st_mode))
		acc_rights[(*i)++] = 'l';
	else if (S_ISCHR(file_stat->st_mode))
		acc_rights[(*i)++] = 'c';
	else if (S_ISBLK(file_stat->st_mode))
		acc_rights[(*i)++] = 'b';
	else if (S_ISSOCK(file_stat->st_mode))
		acc_rights[(*i)++] = 's';
	else if (S_ISFIFO(file_stat->st_mode))
		acc_rights[(*i)++] = 'p';
	else if (S_ISREG(file_stat->st_mode))
		acc_rights[(*i)++] = '-';
}

void		set_acc_rights(t_node_info *node, struct stat *file_stat)
{
	int i;

	i = 0;
	node->acc_rights = ft_strnew(10);
	set_file_mode(node->acc_rights, file_stat, &i);
	node->acc_rights[i++] = (file_stat->st_mode & S_IRUSR) ? 'r' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IWUSR) ? 'w' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IXUSR) ? 'x' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IRGRP) ? 'r' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IWGRP) ? 'w' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IXGRP) ? 'x' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IROTH) ? 'r' : '-';
	node->acc_rights[i++] = (file_stat->st_mode & S_IWOTH) ? 'w' : '-';
	if (file_stat->st_mode & S_IXOTH)
		node->acc_rights[i] = ((file_stat->st_mode & S_ISVTX) ? 't' : 'x');
	else
		node->acc_rights[i] = '-';
}

void		set_datetime(t_node_info *node, struct stat *file_stat)
{
	char	**dt_split;

	dt_split = ft_strsplit(ctime(&file_stat->st_mtime), ' ');
	node->last_mod_time = ft_strnew(5);
	ft_strncpy(node->last_mod_time, dt_split[3], 5);
	node->last_mod_date = ft_strnew(6);
	ft_strcat(node->last_mod_date, dt_split[1]);
	ft_strcat(node->last_mod_date, (ft_strlen(dt_split[2]) == 1 ? "  " : " "));
	ft_strcat(node->last_mod_date, dt_split[2]);
	node->last_mod_year = ft_strnew(4);
	ft_strncpy(node->last_mod_year, dt_split[4], 4);
	free_str_arr(dt_split);
}

void		set_node_info(t_node_info *node, struct stat *file_stat)
{
	struct passwd	*s_passwd;
	struct group	*s_group;

	set_acc_rights(node, file_stat);
	node->num_links = file_stat->st_nlink;
	s_passwd = getpwuid(file_stat->st_uid);
	node->owner_name = ft_strdup(s_passwd->pw_name);
	s_group = getgrgid(file_stat->st_gid);
	node->owner_group = ft_strdup(s_group->gr_name);
	node->size_bytes = file_stat->st_size;
	node->num_blocks = file_stat->st_blocks;
	node->ts = file_stat->st_mtimespec;
	node->mod_time = file_stat->st_mtime;
	node->dev_major = major(file_stat->st_rdev);
	node->dev_minor = minor(file_stat->st_rdev);
	set_datetime(node, file_stat);
}
