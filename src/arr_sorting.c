/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:40:49 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/24 16:40:49 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/includes/libft.h"
#include <sys/stat.h>

void	sort_arr(char **arr, int start, int end,
					int (*f)(const char *, const char *))
{
	int i;
	int j;
	int pos_min;

	i = start;
	while (i < end - 1)
	{
		pos_min = i;
		j = i + 1;
		while (j < end)
		{
			if (f(arr[j], arr[pos_min]) < 0)
				pos_min = j;
			j++;
		}
		if (pos_min != i)
			swap_strings(&arr[i], &arr[pos_min]);
		i++;
	}
}

void	nexist_to_beginning(char **arr, struct stat *f_stat, int *file_i)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		if (lstat(arr[i], f_stat) != 0)
		{
			if (i != *file_i)
				swap_strings(&arr[i], &arr[*file_i]);
			(*file_i)++;
		}
	}
}

void	files_to_beginning(char **arr, struct stat *f_stat, int *dir_i,
							int file_i)
{
	int i;

	i = file_i - 1;
	*dir_i = file_i;
	while (arr[++i])
	{
		if (lstat(arr[i], f_stat) == 0 && !S_ISDIR(f_stat->st_mode))
		{
			if (i != *dir_i)
				swap_strings(&arr[i], &arr[*dir_i]);
			(*dir_i)++;
		}
	}
}

void	sort_full_len(char **dirpaths, int *file_i, int *dir_i,
						t_flags *flags)
{
	int len;

	len = get_dlen(dirpaths);
	sort_arr(dirpaths, 0, *file_i, ft_strcmp);
	sort_arr(dirpaths, *file_i, *dir_i, ft_strcmp);
	sort_arr(dirpaths, *dir_i, len, ft_strcmp);
	if (!flags->r_flag && flags->t_flag)
	{
		sort_arr(dirpaths, *file_i, *dir_i, ft_modcmp);
		sort_arr(dirpaths, *dir_i, len, ft_modcmp);
	}
	else if (flags->r_flag)
	{
		sort_arr(dirpaths, *file_i, *dir_i, flags->t_flag ? ft_revmodcmp :
															ft_revstrcmp);
		sort_arr(dirpaths, *dir_i, len, flags->t_flag ? ft_revmodcmp :
														ft_revstrcmp);
	}
}

void	sort_dirpaths(char **dirpaths, int *file_i, int *dir_i,
						t_flags *flags)
{
	struct stat f_stat;

	*file_i = 0;
	*dir_i = 0;
	nexist_to_beginning(dirpaths, &f_stat, file_i);
	files_to_beginning(dirpaths, &f_stat, dir_i, *file_i);
	sort_full_len(dirpaths, file_i, dir_i, flags);
}
