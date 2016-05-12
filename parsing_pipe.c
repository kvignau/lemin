/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:38:55 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 17:39:08 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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

	i = 0;
	(*env)->tubes = (int **)malloc(sizeof(int *) * NBROOMS);
	while (i < NBROOMS)
	{
		(*env)->tubes[i] = (int *)malloc(sizeof(int) * NBROOMS);
		ft_bzero((*env)->tubes[i], sizeof(int) * NBROOMS);
		i++;
	}
}

int			ft_pipe(t_fourmiliere **env, char *line)
{
	char	**recup;
	t_rooms	*tmp;
	int		ok;
	int		id_1;
	int		id_2;

	ok = 0;
	if (line[0] == '#' && line[1] == '#')
		return (1);
	recup = ft_strsplit(line, '-');
	if (!recup[0] || !recup[1])
		return (0);
	tmp = HROOMS;
	while (tmp)
	{
		if (ft_strequ(tmp->name_room, recup[0]) || ft_strequ(tmp->name_room, recup[1]))
		{
			if (ok == 0)
			{
				id_1 = tmp->id;
				ft_printf("%s-", tmp->name_room);	
			}
			if (ok == 1)
			{
				id_2 = tmp->id;
				ft_printf("%s\n", tmp->name_room);	
			}
			ok++;
		}
		tmp = tmp->next;
	}
	if (ok != 2)
		return (0);
	(*env)->tubes[id_1][id_2] = 1;
	(*env)->tubes[id_2][id_1] = 1;
	ft_deltab(recup);
	return (1);
}

void		ft_deltab(char **recup)
{
	int		i;

	i = 0;
	while (recup[i] != NULL)
	{
		free(recup[i]);
		i++;
	}
	free(recup);
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
				//ft_printf("%d\n", (*env)->nb_fourmis);//debug
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
						break ;
						//return (0);
					ok++;
				}
			}
		}
		free(line);
	}
	return (1);
}