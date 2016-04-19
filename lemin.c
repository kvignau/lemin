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

void		ft_room(t_fourmiliere **env, char *line, int *end, int *start)
{
	char	**recup;
	t_rooms	*room;

	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strequ("start", line + 2))
			*start = 1;
		if (ft_strequ("end", line + 2))
			*end = 1;
		else
			ft_printf("\nError\n");//debug ajout fonction error()
	}
	else
	{
		recup = ft_strsplit(line, ' ');
		if (recup[3])
			ft_printf("\nError trop de param dans ligne\n");//debug ajout fonction error()
		ft_newroom(&room, recup[0], ft_atoi(recup[1]), ft_atoi(recup[2]));
		//if (*start)
		//room->start = 1;
		//*start = 0;
		//if (end)
		//room->end = 1;
		//*end = 0;
		ft_addroomfront(env, room);
	}
}

int			parsing_fourmiliere(t_fourmiliere **env)
{
	char	*line;
	int		end;
	int		start;

	end = 0;
	start = 0;
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
			else
			{
				ft_room(env, line, &end, &start);
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

	// ft_newroom(&room, "room 1", 5, 6);//test fonction creation room
	// ft_addroomfront(&env, room);//test fonction add front
	// ft_newroom(&room, "room 2", 4, 1);//test fonction creation room
	// ft_addroomfront(&env, room);//test fonction add front
	// ft_delrooms(&env);//test supp
	while (env->rooms->head)
	{
		ft_printf("\nnom de la room : %s, x: %d, y: %d\n", env->rooms->head->name_room, env->rooms->head->x, env->rooms->head->y);
		env->rooms->head = env->rooms->head->next;
	}

	if (!parsing_fourmiliere(&env))//si parsing != 0 display all file
		exit (0);//error 
	return (0);
}
