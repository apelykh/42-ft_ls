/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:29:58 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/24 16:30:00 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"

void	process_flag(char *arg, t_flags *flags)
{
	int j;

	j = 0;
	while (arg[++j])
	{
		if (!ft_strrchr(IMPL_FLAGS, arg[j]) || !ft_isalnum(arg[j]))
			handle_error(&arg[j], "illegal option", 1);
		arg[j] == 'l' ? flags->l_flag = 1 : 0;
		arg[j] == 'R' ? flags->rb_flag = 1 : 0;
		arg[j] == 'r' ? flags->r_flag = 1 : 0;
		arg[j] == 't' ? flags->t_flag = 1 : 0;
		arg[j] == 'a' ? flags->a_flag = 1 : 0;
		arg[j] == 'f' ? flags->f_flag = 1 : 0;
	}
}

void	parse_args(char **argv, char **dirpaths, t_flags *flags)
{
	int i;
	int flag;
	int dir_index;

	i = 0;
	flag = 1;
	dir_index = 0;
	while (argv[++i])
	{
		if (flag && (argv[i][0] != '-' || !argv[i][1]))
			flag = 0;
		if (flag)
			process_flag(argv[i], flags);
		else
			dirpaths[dir_index++] = argv[i];
	}
	if (dir_index == 0)
		dirpaths[dir_index++] = ".";
	dirpaths[dir_index] = NULL;
}
