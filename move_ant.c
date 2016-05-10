/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ant.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:12:29 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 19:12:40 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_finish(t_lstant *lst_ant)
{
	t_ant	*ant;

	ant = lst_ant->head;
	while (ant)
	{
		if (ant->id_room != 1)
			return (0);
		ant = ant->next;
	}
	return (1);
}

int			check_dispo(t_linkedlst *lst_ch, t_lstant *lst_ant)
{
	t_node	*ch;
	t_ant	*ant;
	int		i;

	i = 0;
	ch = lst_ch->head;
	ant = lst_ant->head;
	while (ant)
	{
		while (ant->array.id[i])
		{
			if (ant->id_room == p->id_room)
			{
				ft_move();
				return (1);
			}
			i++;
		}
		ant = ant->next;
	}
	return (0);
}