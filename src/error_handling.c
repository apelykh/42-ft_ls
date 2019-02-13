/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 15:41:13 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/04 15:41:14 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <errno.h>

int		handle_error(char *param, char *error_msg, int to_exit)
{
	if (param && errno && !error_msg)
	{
		ft_putstr(PROG_NAME);
		ft_putstr(": ");
		ft_putstr(param);
		ft_putstr(": ");
		ft_putendl(strerror(errno));
	}
	else
	{
		ft_putstr(PROG_NAME);
		ft_putstr(": ");
		ft_putstr(error_msg);
		ft_putstr(" -- ");
		ft_putendl(&param[0]);
		ft_putstr("usage: ");
		ft_putstr(PROG_NAME);
		ft_putchar(' ');
		ft_putstr(IMPL_FLAGS);
		ft_putstr("[file ...]\n");
	}
	if (to_exit)
		exit(-1);
	return (1);
}
