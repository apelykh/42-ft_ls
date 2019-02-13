/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 18:14:25 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/04 18:14:26 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <stdlib.h>

void	init_vars(t_vars *vars, int argc, char **dirpaths)
{
	if (dirpaths && argc)
	{
		vars->i = -1;
		vars->n_flag = 0;
		vars->name_flag = -1;
		dirpaths[argc - 1] = NULL;
	}
}

int		get_dlen(char **dirpaths)
{
	int len;

	len = 0;
	while (dirpaths[len])
		len++;
	return (len);
}

int		main(int argc, char **argv)
{
	char	**dirpaths;
	t_flags	flags;
	t_vars	vars;

	dirpaths = (char**)malloc(sizeof(char*) * argc);
	init_vars(&vars, argc, dirpaths);
	parse_args(argv, dirpaths, &flags);
	sort_dirpaths(dirpaths, &vars.file_i, &vars.dir_i, &flags);
	while (dirpaths[++(vars.i)] && ++vars.name_flag > -1)
	{
		(vars.dir_i == 0 && get_dlen(dirpaths) > 1) ? vars.name_flag++ : 0;
		if (vars.i < vars.file_i)
			handle_error(dirpaths[vars.i], NULL, 0);
		else if (vars.i == vars.file_i && vars.dir_i - vars.file_i > 1)
		{
			ls_files_group(dirpaths, vars.file_i, vars.dir_i, &flags);
			vars.i = vars.dir_i - 1;
			vars.n_flag++;
		}
		else
			ls_object(dirpaths[vars.i], &flags, vars.n_flag++, vars.name_flag);
	}
	free(dirpaths);
	dirpaths = NULL;
	return (0);
}
