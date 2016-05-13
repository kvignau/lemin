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
	(*env)->nb_fourmis = ft_atoi(line);
	if ((*env)->nb_fourmis == 0 && line[0] != '0')
		return (0);
	ft_printf("%d\n", (*env)->nb_fourmis);
	return (1);
}

int					test_room(char *line)
{
	int				i;
	int				space;

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
	if (space == 2)
		return (1);
	return (0);
}

int				ft_room(t_fourmiliere **env, char *line, int *end, int *start)
{
	char		**recup;
	t_rooms		*room;
	int			ok;
	t_rooms		*tmp;
	static int	nb = 1;

	if (line[0] == '#' && line[1] == '#')
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
	else
	{
		recup = ft_strsplit(line, ' ');
		if (!recup[0] || !recup[1] || !recup[2])
		{
			ft_deltab(recup);
			return (0);
		}
		ok = test_room(line);
		if (ok != 1)
			return (ok);//error();
		tmp = HROOMS;
		while (tmp)
		{
			if (ft_strequ(tmp->name_room, recup[0]))
				return (-1);
			tmp = tmp->next;
		}
		ft_newroom(&room, ft_strdup(recup[0]), ft_atoi(recup[1]), ft_atoi(recup[2]));
		ft_addroomfront(env, room);
		ft_deltab(recup);
		if (*start == 1)
		{
			(*env)->rooms->head->id = 0;
			(*env)->rooms->head->start = 1;
			nb--;
		}
		else if (*end == 1)
		{
			(*env)->rooms->head->id = 1;
			(*env)->rooms->head->end = 1;
			nb--;
		}
		else
			(*env)->rooms->head->id = NBROOMS + nb;
		*start = 0;
		*end = 0;
	}
	if ((*env)->rooms->head && (*start) != 1 && (*end) != 1)
		ft_printf("%s %d %d\n", (*env)->rooms->head->name_room, (*env)->rooms->head->x, (*env)->rooms->head->y);
	return (1);
}