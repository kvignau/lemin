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
	if ((*env)->nb_fourmis == 0 && line[0] != '0')
		return (0);
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
	t_rooms	*tmp;

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
			return (0);
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
		ft_newroom(&room, recup[0], ft_atoi(recup[1]), ft_atoi(recup[2]));
		if (*start)
			room->start = 1;
		if (*end)
			room->end = 1;
		room->id = NBROOMS;
		*start = 0;
		*end = 0;
		ft_addroomfront(env, room);
	}
	return (1);
}

int					start_end(t_fourmiliere *env)
{
	t_rooms	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	tmp = env->rooms->head;
	while (tmp)
	{
		if (tmp->start)
			start++;
		if (tmp->end)
			end++;
		tmp = tmp->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}

void		ft_initpipe(t_fourmiliere **env)
{
	int		i;
	int		j;

	i = 0;
	(*env)->tubes = (int **)malloc(sizeof(int *) * NBROOMS);
	while (i < NBROOMS)
	{
		j = 0;
		(*env)->tubes[i] = (int *)malloc(sizeof(int) * NBROOMS);
		while (j < NBROOMS)
		{
			(*env)->tubes[i][j] = 0;
			j++;
		}
		i++;
	}
	// //debug
	// i = 0;
	// while (i < NBROOMS)
	// {
	// 	j = 0;
	// 	while (j < NBROOMS)
	// 	{
	// 		ft_putnbr((*env)->tubes[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }
}

int			ft_pipe(t_fourmiliere **env, char *line)
{
	// int		i;
	// int		j;
	char	**recup;

	recup = ft_strsplit(line, '-');
	if (!recup[0] || !recup[1])
		return (0);
	(*env)->tubes[ft_atoi(recup[0])][ft_atoi(recup[1])] = 1;
	(*env)->tubes[ft_atoi(recup[1])][ft_atoi(recup[0])] = 1;
	// //debug
	// i = 0;
	// while (i < NBROOMS)
	// {
	// 	j = 0;
	// 	while (j < NBROOMS)
	// 	{
	// 		ft_putnbr((*env)->tubes[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }
	return (1);
}

int			parsing_fourmiliere(t_fourmiliere **env)
{
	char	*line;
	int		end;
	int		start;
	int		roomok;
	int		ok;

	end = 0;
	start = 0;
	roomok = 1;
	ok = 0;
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
				if (ok == 0)
				{
					roomok = ft_room(env, line, &end, &start);
					if (roomok == 0)
						ok++;
					if (roomok == -1)
						return (0);
				}
				if (ok == 1)
				{
					if (!start_end(*env))
						return (0);
					ft_initpipe(env);
				}
				if (ok >= 1)
				{
					if (!ft_pipe(env, line))
						return (0);
					ok++;
				}
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

	if (!parsing_fourmiliere(&env))//si parsing != 0 display all file
	{
		ft_printf("\nError\n");
		exit (0);//error
	} 
	while (env->rooms->head)
	{
		ft_printf("\nid room : %d, nom de la room : %s, x: %d, y: %d, start: %d, end: %d\n", env->rooms->head->id, env->rooms->head->name_room, env->rooms->head->x, env->rooms->head->y, env->rooms->head->start, env->rooms->head->end);
		env->rooms->head = env->rooms->head->next;
	}

	return (0);
}
