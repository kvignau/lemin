/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_display_ant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 15:06:13 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:09:06 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				finish(t_lstant *lst_ant)
{
	t_ant		*ant;

	ant = lst_ant->head;
	while (ant)
	{
		if (ant->id_room != 1)
			return (0);
		ant = ant->next;
	}
	return (1);
}

void			display(int id_ant, int id_room, t_fourmiliere *env, int first)
{
	t_rooms		*tmp;

	tmp = env->rooms->head;
	while (tmp != NULL)
	{
		if (tmp->id == id_room)
		{
			if (first == 1)
				ft_printf("L%d-%s", id_ant, tmp->name_room);
			else
				ft_printf(" L%d-%s", id_ant, tmp->name_room);
		}
		tmp = tmp->next;
	}
}

void			debutfin(t_lstant *lst_ant, t_fourmiliere *env)
{
	t_ant		*ant;
	int			first;

	first = 1;
	ant = lst_ant->head;
	while (ant)
	{
		display(ant->id_ant, 1, env, first);
		first++;
		ant = ant->next;
	}
	ft_printf("\n");
}

void			remove_ant(t_lstant **lstant)
{
	t_ant		*ant;

	ant = NULL;
	if ((*lstant)->head->next)
		ant = (*lstant)->head->next;
	while (ant != NULL)
	{
		free(ant->prev);
		ant = ant->next;
	}
	free((*lstant)->tail);
	(*lstant)->head = NULL;
	(*lstant)->tail = NULL;
	free(*lstant);
}

void			check_dispo(t_linkedlst *lst_ch, t_fourmiliere *env)
{
	t_node		*ch;
	t_lstant	*lst_ant;
	t_ant		*ant;
	int			first;

	create_ant(&lst_ant, env);
	if (lst_ch->head->array.id[0] == 1)
	{
		debutfin(lst_ant, env);
		remove_ant(&lst_ant);
		return ;
	}
	while (finish(lst_ant) == 0)
	{
		first = 0;
		ant = lst_ant->head;
		move_ant(lst_ch, ant, &first, env);
		ft_printf("\n");
	}
	remove_ant(&lst_ant);
}
