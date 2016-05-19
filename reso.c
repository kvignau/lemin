/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reso.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 17:34:35 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:12:30 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			ft_realloc(t_chemin *ch)
{
	int			*tmp;

	ch->length_malloc *= 2;
	tmp = (int *)malloc(sizeof(int) * ch->length_malloc);
	ft_memcpy(tmp, ch->id, sizeof(int) * ch->length);
	free(ch->id);
	ch->id = tmp;
}

int				lemin(int start, t_fourmiliere *env, t_linkedlst **lstch,
		t_chemin *ch)
{
	int			i;
	t_node		*tmp;
	int			stop;

	i = 0;
	stop = 0;
	while (stop == 0 && i < env->rooms->nb_rooms)
	{
		if (env->tubes[start][i] == 1 && env->visite[i] == 0)
		{
			if (i == 1)
				return (add_good_way(lstch, ch, &stop));
			else
			{
				go_next(ch, env, i, start);
				if (lemin(i, env, lstch, ch) == -1)
					return (-1);
				go_back(ch, env, i, start);
			}
		}
		i++;
	}
	return (0);
}

void			go_back(t_chemin *ch, t_fourmiliere *env, int i, int start)
{
	ch->length = ch->length - 1;
	env->visite[i] = 0;
	env->tubes[start][i] = 1;
	env->tubes[i][start] = 1;
}

void			go_next(t_chemin *ch, t_fourmiliere *env, int i, int start)
{
	env->visite[i] = 1;
	env->tubes[start][i] = 0;
	env->tubes[i][start] = 0;
	if (ch->length >= ch->length_malloc)
		ft_realloc(ch);
	ch->id[ch->length] = i;
	ch->length = ch->length + 1;
}

int				add_good_way(t_linkedlst **lstch, t_chemin *ch, int *stop)
{
	if (ch->length == 0)
	{
		if (ch->length >= ch->length_malloc)
			ft_realloc(ch);
		ch->id[ch->length] = 1;
		ch->length = ch->length + 1;
		(*stop)++;
	}
	ft_addch(lstch, ch);
	return (1);
}
