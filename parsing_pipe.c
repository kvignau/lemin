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

int			split_minus(char *line)
{
	int		i;
	int		minus;

	i = 0;
	minus = 0;
	while (line[i])
	{
		if (line[i] == '-')
			minus++;
		if (minus >= 2)
			return (0);
		i++;
	}
	return (1);
}

int			display_hashtag(char *line)
{
	if (ft_strequ(line + 2, "start") || ft_strequ(line + 2, "end"))
		return (0);
	ft_printf("%s\n", line);
	return (1);
}

int			ft_pipe(t_fourmiliere **env, char *line)
{
	char	**recup;
	int		id_1;
	int		id_2;

	if (line[0] == '#' && line[1] == '#')
	{
		return (display_hashtag(line));
	}
	if (!split_minus(line))
		return (0);
	recup = ft_strsplit(line, '-');
	if (!recup[0] || !recup[1])
	{
		ft_deltab(recup);
		return (0);
	}
	if (test_pipe(env, recup, &id_1, &id_2) == 0)
	{
		ft_deltab(recup);
		return (0);
	}
	(*env)->tubes[id_1][id_2] = 1;
	(*env)->tubes[id_2][id_1] = 1;
	ft_deltab(recup);
	return (1);
}

int			test_pipe(t_fourmiliere **env, char **recup, int *id_1, int *id_2)
{
	t_rooms	*tmp;
	int		ok;

	ok = 0;
	tmp = HROOMS;
	while (tmp)
	{
		if (ft_strequ(tmp->name_room, recup[0]) || ft_strequ(tmp->name_room, recup[1]))
		{
			if (ok == 0)
			{
				(*id_1) = tmp->id;
				ft_printf("%s-", tmp->name_room);	
			}
			if (ok == 1)
			{
				(*id_2) = tmp->id;
				ft_printf("%s\n", tmp->name_room);	
			}
			ok++;
		}
		tmp = tmp->next;
	}
	return ((ok != 2) ? 0 : 1);
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
	int		ok;

	end = 0;
	start = 0;
	while (get_next_line(0, &line))
	{
		if (!iscomment(line))
		{
			if ((*env)->nb_fourmis < 0)
			{
				if (!nbfourmis(line, env))
					return (error_parsing(line));
			}
			else
			{
				ok = parsing_room_pipe(env, line, &start, &end);
				if (ok == 0)
					return (0);
				else if (ok == -1)
				{
					free(line);
					break ;
				}
			}
		}
		free(line);
	}
	return (1);
}

int			parsing_room_pipe(t_fourmiliere **env, char *line, int *start, int *end)
{
	int		static ok = 0;
	int		roomok;

	roomok = 1;
	if (ok == 0)
	{
		roomok = ft_room(env, line, end, start);
		if (roomok == 0)
			ok++;
		if (roomok == -1)
			return (error_parsing(line));
	}
	if (ok == 1)
	{
		if (!start_end(*env))
			return (error_parsing(line));
		ft_initpipe(env);
	}
	if (ok >= 1)
	{
		if (ft_pipe(env, line) == 0)
			return (-1);
		ok++;
	}
	return (1);
}

int			error_parsing(char *line)
{
	free(line);
	return (0);
}