/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 19:12:07 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 19:12:09 by kvignau          ###   ########.fr       */
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

void			create_ant(t_fourmiliere *env)
{
	t_ant		*ant;
	t_lstant	*lst;

	initlstant(&lst);
	while (lst->len < env->nb_fourmis)
	{
		ft_newant(&ant, lst->len + 1);
		if (lst->len == 0)
		{
			ant->next = NULL;
			ant->prev = NULL;
			lst->head = ant;
			lst->tail = ant;
		}
		else
		{
			ant->next = NULL;
			ant->prev = lst->tail;
			lst->tail->next = ant;
			lst->tail = ant;
		}
		lst->len++;
	}
}
