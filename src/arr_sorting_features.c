/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_sorting_features.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 13:52:59 by apelykh           #+#    #+#             */
/*   Updated: 2017/06/26 13:53:00 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

int		ft_revstrcmp(const char *s1, const char *s2)
{
	return (ft_strcmp(s2, s1));
}

int		ft_modcmp(const char *s1, const char *s2)
{
	struct stat		f_stat;
	struct timespec ts1;
	struct timespec ts2;

	if (lstat(s1, &f_stat) == 0)
		ts1 = f_stat.st_mtimespec;
	if (lstat(s2, &f_stat) == 0)
		ts2 = f_stat.st_mtimespec;
	if (((double)ts2.tv_sec + 1.0e-9 * ts2.tv_nsec) >
		((double)ts1.tv_sec + 1.0e-9 * ts1.tv_nsec))
	{
		return (1);
	}
	else
		return (-1);
}

int		ft_revmodcmp(const char *s1, const char *s2)
{
	return (ft_modcmp(s2, s1));
}
