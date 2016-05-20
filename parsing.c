/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:43:49 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:21:30 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				parsing_fourmiliere(t_fourmiliere **env)
{
	char		*line;
	int			end;
	int			start;
	int			ok;

	end = 0;
	start = 0;
	while (get_next_line(0, &line))
	{
		if (!iscomment(line))
		{
			ok = parsing_choise(env, line, &start, &end);
			if (ok == 0)
				return (0);
			else if (ok == -1)
				return (1);
		}
		ft_putendl(line);
		free(line);
	}
	return (1);
}

int				parsing_choise(t_fourmiliere **env, char *line, int *start,
		int *end)
{
	int			ok;

	if ((*env)->nb_fourmis < 0)
	{
		if (nbfourmis(line, env) == 0)
			return (error_parsing(line, 0));
	}
	else
	{
		ok = parsing_room_pipe(env, line, start, end);
		if (ok == 0)
			return (0);
		else if (ok == -1)
			return (-1);
	}
	return (1);
}

int				parsing_room_pipe(t_fourmiliere **env, char *line, int *start,
		int *end)
{
	int static	ok = 0;
	int			roomok;

	roomok = 1;
	if (ok == 0)
	{
		roomok = ft_room(env, line, end, start);
		if (roomok == 0)
			ok++;
		if (roomok == -1)
			return (error_parsing(line, 0));
	}
	if (ok == 1)
	{
		if (!start_end(*env))
			return (error_parsing(line, 0));
		ft_initpipe(env);
	}
	if (ok >= 1)
	{
		if (ft_pipe(env, line) == 0)
			return (error_parsing(line, -1));
		ok++;
	}
	return (1);
}

int				error_parsing(char *line, int ret)
{
	free(line);
	return (ret);
}
