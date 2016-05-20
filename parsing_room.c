/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:40:56 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:11:10 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				test_room(char *line)
{
	int			i;
	int			space;

	i = 0;
	space = 0;
	while (line && line[i])
	{
		if (line[i] == ' ')
			space++;
		else if (line[i] == '+')
			space++;
		else if (space != 0 && !ft_isdigit(line[i]))
			return (-1);
		i++;
	}
	return (1);
}

int				split_space(char *line)
{
	int			i;
	int			space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			space++;
		if (space >= 3)
			return (0);
		i++;
	}
	return (1);
}

int				info_room(int *start, int *end, char *line)
{
	if (ft_strequ("start", line + 2))
		(*start)++;
	else if (ft_strequ("end", line + 2))
		(*end)++;
	return (1);
}

void			id_room(int start, int end, int *nb, t_fourmiliere **env)
{
	if (start == 1)
	{
		(*env)->rooms->head->id = 0;
		(*env)->rooms->head->start = 1;
		(*nb)--;
	}
	else if (end == 1)
	{
		(*env)->rooms->head->id = 1;
		(*env)->rooms->head->end = 1;
		(*nb)--;
	}
	else
		(*env)->rooms->head->id = NBROOMS + (*nb);
}

int				ft_room(t_fourmiliere **env, char *line, int *end, int *start)
{
	char		**recup;
	t_rooms		*room;
	int			ok;
	static int	nb = 1;

	if (line[0] == '#' && line[1] == '#')
		return (info_room(start, end, line));
	else
	{
		if (line[0] == 'L' || split_space(line) == 0)
			return (0);
		recup = ft_strsplit(line, ' ');
		if ((ok = name_room_ok(env, recup, line)) != 1)
			return (ok);
		ft_newroom(&room, ft_strdup(recup[0]), ft_atoi(recup[1]),
				ft_atoi(recup[2]));
		ft_addroomfront(env, room);
		ft_deltab(recup);
		id_room(*start, *end, &nb, env);
		*start = 0;
		*end = 0;
	}
	return (1);
}
