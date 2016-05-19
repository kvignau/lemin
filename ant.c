/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:12:07 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 15:18:25 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		initlstant(t_lstant **lst)
{
	(*lst) = (t_lstant *)malloc(sizeof(t_lstant));
	if ((*lst) == NULL)
		return ;
	else
	{
		(*lst)->len = 0;
		(*lst)->tail = NULL;
		(*lst)->head = NULL;
	}
}

void		ft_newant(t_ant **ant, int id_ant)
{
	*ant = (t_ant *)malloc(sizeof(t_ant));
	if (*ant == NULL)
		return ;
	(*ant)->id_ant = id_ant;
	(*ant)->id_room = 0;
	(*ant)->move = 0;
	(*ant)->prev = NULL;
	(*ant)->next = NULL;
}

void		create_ant(t_lstant **lst_ant, t_fourmiliere *env)
{
	t_ant	*ant;

	initlstant(lst_ant);
	while ((*lst_ant)->len < env->nb_fourmis)
	{
		ft_newant(&ant, (*lst_ant)->len + 1);
		if ((*lst_ant)->len == 0)
		{
			ant->next = NULL;
			ant->prev = NULL;
			(*lst_ant)->head = ant;
			(*lst_ant)->tail = ant;
		}
		else
		{
			ant->next = NULL;
			ant->prev = (*lst_ant)->tail;
			(*lst_ant)->tail->next = ant;
			(*lst_ant)->tail = ant;
		}
		(*lst_ant)->len++;
	}
}

void		ft_remove_ant(t_lstant **lstant, t_ant *ant)
{
	t_ant	*tmp;

	tmp = (*lstant)->head;
	while (tmp)
	{
		if (tmp->id_ant == ant->id_ant)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			tmp->prev = NULL;
			tmp->next = NULL;
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
