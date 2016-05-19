/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 14:57:02 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:13:53 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			name_room_ok(t_fourmiliere **env, char **recup, char *line)
{
	int		ok;

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

int			room_ok(t_fourmiliere **env, char **recup, char *line)
{
	int		ok;
	t_rooms	*tmp;

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

int			test_pipe(t_fourmiliere **env, char **recup, int *id_1, int *id_2)
{
	t_rooms	*tmp;
	int		ok;

	ok = 0;
	tmp = HROOMS;
	while (tmp)
	{
		if (ft_strequ(tmp->name_room, recup[0]) ||
				ft_strequ(tmp->name_room, recup[1]))
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
