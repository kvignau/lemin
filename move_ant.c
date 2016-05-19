/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:12:29 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:15:40 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		move_ant(t_linkedlst *lst_ch, t_ant *ant,
		int *first, t_fourmiliere *env)
{
	t_node	*ch;

	while (ant != NULL)
	{
		ch = lst_ch->head;
		if (ant->id_room == 0)
			ant_start(ch, ant, first, env);
		else
		{
			while (ch != NULL)
			{
				ant_move(ch, ant, first, env);
				ch = ch->next;
			}
		}
		ant = ant->next;
	}
}

void		ant_start(t_node *ch, t_ant *ant, int *first, t_fourmiliere *env)
{
	while (ch != NULL)
	{
		if (ch->array.dispo[0] == 1)
		{
			ant->id_room = ch->array.id[0];
			ch->array.dispo[0] = 0;
			(*first)++;
			display(ant->id_ant, ant->id_room, env, *first);
			break ;
		}
		ch = ch->next;
	}
}

void		ant_move(t_node *ch, t_ant *ant, int *first, t_fourmiliere *env)
{
	int		i;

	i = 0;
	while (i < ch->array.length)
	{
		if (ch->array.id[i] == ant->id_room)
		{
			if (i + 1 < ch->array.length)
			{
				move_ch(ch, ant, i);
				(*first)++;
				display(ant->id_ant, ant->id_room, env, *first);
				break ;
			}
			else
			{
				ant->id_room = 1;
				ch->array.dispo[i] = 1;
				(*first)++;
				display(ant->id_ant, ant->id_room, env, *first);
				break ;
			}
		}
		i++;
	}
}

void		move_ch(t_node *ch, t_ant *ant, int i)
{
	ant->id_room = ch->array.id[i + 1];
	ch->array.dispo[i] = 1;
	ch->array.dispo[i + 1] = 0;
}
