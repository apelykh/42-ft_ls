/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apelykh <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:48:28 by apelykh           #+#    #+#             */
/*   Updated: 2017/05/26 14:48:31 by apelykh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "../includes/ft_ls.h"
#include <stdlib.h>

int		compare_timestamp(time_t mod_time)
{
	time_t now;

	now = time(NULL);
	if (now - 15778800 > mod_time || mod_time > now)
		return (1);
	return (0);
}

void	swap_strings(char **s1, char **s2)
{
	char *tmp_ptr;

	tmp_ptr = *s1;
	*s1 = *s2;
	*s2 = tmp_ptr;
}

int		num_len(long long nbr)
{
	int len;

	len = 0;
	if (nbr >= 0 && nbr < 10)
		return (1);
	while (nbr != 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

void	ft_putlonglong(long long n)
{
	if (n < 0)
		ft_putchar('-');
	if (ABS(n) >= 0 && ABS(n) <= 9)
		ft_putchar(ABS(n) + '0');
	else
	{
		ft_putlonglong(ABS(n / 10));
		ft_putchar(ABS(n % 10) + '0');
	}
}

void	free_str_arr(char **dt_split)
{
	int i;

	i = 0;
	while (i < 5)
		free(dt_split[i++]);
	free(dt_split);
}
