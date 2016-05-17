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

int			finish(t_lstant *lst_ant)
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

// int			check_dispo(t_linkedlst *lst_ch, t_lstant *lst_ant)
// {
// 	t_node	*ch;
// 	t_ant	*ant;
// 	int		i;

// 	i = 0;
// 	ch = lst_ch->head;
// 	ant = lst_ant->head;
// 	while (ant)
// 	{
// 		while (ch->array.length < i)
// 		{
// 			if (ant->id_room == p->id_room[i])
// 			{
// 				ft_move(p->id_room);
// 				return (1);
// 			}
// 			i++;
// 		}
// 		ant = ant->next;
// 	}
// 	return (0);
// }
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
		display(ant->id_ant, ant->id_room, env, first);
		first++;
		ant = ant->next;
	}
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
	int			i;
	int			first;

	create_ant(&lst_ant, env);
	if (lst_ch->head->array.id[0] == 1)
	{
		debutfin(lst_ant, env);
		remove_ant(&lst_ant);
		//ft_printf("ALL ANT");
		return ;
	}
	while (finish(lst_ant) == 0)
	{
		first = 0;
		ant = lst_ant->head;
		while (ant != NULL)
		{
			ch = lst_ch->head;
			if (ant->id_room == 0)
			{
				while (ch != NULL)
				{
					if (ch->array.dispo[0] == 1)
					{
						ant->id_room = ch->array.id[0];
						ch->array.dispo[0] = 0;
						first++;
						display(ant->id_ant, ant->id_room, env, first);
						//ft_printf("L%d-%d ", ant->id_ant, ant->id_room);//display
						break ;
					}
					ch = ch->next;
				}
			}
			else
			{
				while (ch != NULL)
				{
					i = 0;
					while (i < ch->array.length)
					{
						if (ch->array.id[i] == ant->id_room)
						{
							if (i + 1 < ch->array.length)
							{
								ant->id_room = ch->array.id[i + 1];
								ch->array.dispo[i] = 1;
								ch->array.dispo[i + 1] = 0;
								first++;
								display(ant->id_ant, ant->id_room, env, first);
								//ft_printf("L%d-%d ", ant->id_ant, ant->id_room);//display
								break ;
							}
							else
							{
								ant->id_room = 1;
								ch->array.dispo[i] = 1;
								first++;
								display(ant->id_ant, ant->id_room, env, first);
								// ft_printf("L%d-%d ", ant->id_ant, ant->id_room);//display
								break ;
							}
						}
						i++;
					}
					ch = ch->next;
				}
			}
			ant = ant->next;
		}
		ft_printf("\n");
	}
	remove_ant(&lst_ant);
}
