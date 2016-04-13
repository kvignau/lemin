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

int			iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		ft_printf("\n%s\n", line);//debug
		return (1);
	}
	return (0);
}

int			nbfourmis(char *line, t_fourmiliere **env)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	(*env)->nb_fourmis = ft_atoi(line);
	return (1);
}

int			parsing_fourmiliere(t_fourmiliere **env)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (!iscomment(line))
		{
			if ((*env)->nb_fourmis < 0)
			{
				if (!nbfourmis(line, env))
					return (0);
				ft_printf("\n%d\n", (*env)->nb_fourmis);//debug
			}
		}
	}
	return (1);
}

int			main(void)
{
	t_fourmiliere	*env;
	t_rooms			*room;//test fonction creation room

	initenv(&env);

	ft_newroom(&room, "room 1", 5, 6);//test fonction creation room
	ft_addroomfront(&env, room);//test fonction add front
	ft_newroom(&room, "room 2", 4, 1);//test fonction creation room
	ft_addroomfront(&env, room);//test fonction add front
	ft_delrooms(&env);//test supp
	while (env->rooms->head)
	{
		ft_printf("\nnom de la room : %s, x: %d, y: %d\n", env->rooms->head->name_room, env->rooms->head->x, env->rooms->head->y);
		env->rooms->head = env->rooms->head->next;
	}

	parsing_fourmiliere(&env);//si parsing != 0 display all file
	return (0);
}
