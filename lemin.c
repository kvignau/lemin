/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:37:07 by kvignau           #+#    #+#             */
/*   Updated: 2016/04/12 13:37:13 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

// void		ft_initdbl(t_rooms **lst)
// {
// 	*lst = (t_dbl *)malloc(sizeof(t_dbl));
// 	if (*lst == NULL)
// 		return ;
// 	else
// 	{
// 		(*lst)->length = 0;
// 		(*lst)->tail = NULL;
// 		(*lst)->head = NULL;
// 	}
// }

// void		initenv(t_fourmiliere **env)
// {
// 	ft_initdbl(env->rooms);
// }

// int			iscomment(char *line)
// {
// 	if (line[0] == '#' && line[1] != '#')
// 	{
// 		ft_printf("\n%s\n", line);//debug
// 		return (1);
// 	}
// 	return (0);
// }

int			nbfourmis(char *line, int *nb_fourmis)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	*nb_fourmis = ft_atoi(line);
	return (1);
}

int			parsing_fourmiliere()
{
	int		nb_fourmis;
	char	*line;

	nb_fourmis = -1;
	while (get_next_line(0, &line))
	{
		if (!iscomment(line))
		{
			if (nb_fourmis < 0)
			{
				if (!nbfourmis(line, &nb_fourmis))
					return (0);
				ft_printf("\n%d\n", nb_fourmis);//debug
			}
		}
	}
	return (1);
}

int			main(void)
{
	parsing_fourmiliere();//si parsing != 0 display all file
	return (0);
}
