/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:45:57 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 14:46:08 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		ft_printf("%s\n", line);
		return (1);
	}
	return (0);
}

int			nbfourmis(char *line, t_fourmiliere **env)
{
	int		i;

	i = 0;
	if (line && line[0] == '+')
		i++;
	while (line && line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	if (strlen(line) > 10)
		return (0);
	if (strlen(line) == 10)
	{
		if (nb_ant_max_int(line) == 0)
			return (0);
	}
	(*env)->nb_fourmis = ft_atoi(line);
	if ((*env)->nb_fourmis == 0)
		return (0);
	ft_printf("%d\n", (*env)->nb_fourmis);
	return (1);
}

int			nb_ant_max_int(char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] < MAXINT[i])
			break ;
		else if (line[i] > MAXINT[i])
			return (0);
		i++;
	}
	return (1);
}
