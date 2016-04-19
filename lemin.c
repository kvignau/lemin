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

int			ft_room(t_fourmiliere **env, char *line, int *end, int *start)
{
	char	**recup;
	t_rooms	*room;
	int		ok;

	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strequ("start", line + 2))
			*start = 1;
		else if (ft_strequ("end", line + 2))
			*end = 1;
		else
			return (-1);
	}
	else
	{
		recup = ft_strsplit(line, ' ');
		if (!recup[0] || !recup[1] || !recup[2])
			return (-1);
		ok = test_room(line);
		if (ok != 1)
			return (ok);//error();
		ft_newroom(&room, recup[0], ft_atoi(recup[1]), ft_atoi(recup[2]));
		if (*start)
			room->start = 1;
		if (*end)
			room->end = 1;
		*start = 0;
		*end = 0;
		ft_addroomfront(env, room);
	}
	return (1);
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
			else if (ft_room(env, line, &end, &start) == -1)
				//error si -1
				return (0);
			// else
			// {
			// 	ft_pipe();//fonction creation matrice
			// }
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

	if (!parsing_fourmiliere(&env))//si parsing != 0 display all file
	{
		ft_printf("\nError\n");
		exit (0);//error
	} 
	while (env->rooms->head)
	{
		ft_printf("\nnom de la room : %s, x: %d, y: %d, start: %d, end: %d\n", env->rooms->head->name_room, env->rooms->head->x, env->rooms->head->y, env->rooms->head->start, env->rooms->head->end);
		env->rooms->head = env->rooms->head->next;
	}

	return (0);
}
