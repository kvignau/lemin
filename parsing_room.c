/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:40:56 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 17:41:05 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		ft_printf("%s\n", line);//afficher commentaires
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
	if ((*env)->nb_fourmis == 0 && line[0] != '0')
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

int			test_room(char *line)
{
	int		i;
	int		space;

	i = 0;
	space = 0;
	while (line && line[i])
	{
		if (line[i] == ' ')
			space++;
		else if (space != 0 && !ft_isdigit(line[i]))			
			return (-1);
		i++;
	}
	return (1);
}

int			split_space(char *line)
{
	int		i;
	int		space;

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

void			info_room(int *start, int *end, char *line)
{
	if (ft_strequ("start", line + 2))
	{
		(*start)++;
		ft_printf("%s\n", line);
	}
	else if (ft_strequ("end", line + 2))
	{
		(*end)++;
		ft_printf("%s\n", line);
	}
	// ft_printf("%s\n", line); // affiche les ligne ## a ignorer ???
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
		info_room(start, end, line);
	else
	{
		if (line[0] == 'L' || split_space(line) == 0)
			return (0);
		recup = ft_strsplit(line, ' ');
		if ((ok = name_room_ok(env, recup, line)) != 1)
			return (ok);
		ft_newroom(&room, ft_strdup(recup[0]), ft_atoi(recup[1]), ft_atoi(recup[2]));
		ft_addroomfront(env, room);
		ft_deltab(recup);
		id_room(*start, *end, &nb, env);
		*start = 0;
		*end = 0;
	}
	if ((*env)->rooms->head && (*start) != 1 && (*end) != 1)
		ft_printf("%s %d %d\n", (*env)->rooms->head->name_room, (*env)->rooms->head->x, (*env)->rooms->head->y);
	return (1);
}

int				name_room_ok(t_fourmiliere **env, char **recup, char *line)
{
	int			ok;

	if (!recup[0] || !recup[1] || !recup[2])
	{
		ft_deltab(recup);
		return (0);
	}
	if ((ok = room_ok(env, recup, line)) != 1)
	{
		ft_deltab(recup);
		return (ok);
	}
	return (1);
}

int				room_ok(t_fourmiliere **env, char **recup, char *line)
{
	int			ok;
	t_rooms		*tmp;

	ok = test_room(line);
	if (ok != 1)
		return (ok);
	tmp = HROOMS;
	while (tmp)
	{
		if (ft_strequ(tmp->name_room, recup[0]))
			return (-1);
		tmp = tmp->next;
	}
	return (1);
}
