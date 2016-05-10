/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hant.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:43:48 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 17:43:58 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		initlsthant(t_lsthant **lst)
{
	(*lst) = (t_lsthant *)malloc(sizeof(t_lsthant));
	if ((*lst) == NULL)
		return ;
	else
	{
		(*lst)->len = 0;
		(*lst)->tail = NULL;
		(*lst)->head = NULL;
	}
}

void		ft_newhant(t_hant **hant, int id_hant)
{
	*hant = (t_hant *)malloc(sizeof(t_hant));
	if (*hant == NULL)
		return ;
	(*hant)->id_hant = id_hant;
	(*hant)->id_room = 0;
	(*hant)->move = 0;
	(*hant)->prev = NULL;
	(*hant)->next = NULL;
}

void			create_hant(t_fourmiliere *env)
{
	t_hant		*hant;
	t_lsthant	*lst;

	initlsthant(&lst);
	while (lst->len < env->nb_fourmis)
	{
		ft_newhant(&hant, lst->len + 1);
		if (lst->len == 0)
		{
			hant->next = NULL;
			hant->prev = NULL;
			lst->head = hant;
			lst->tail = hant;
		}
		else
		{
			hant->next = NULL;
			hant->prev = lst->tail;
			lst->tail->next = hant;
			lst->tail = hant;
		}
		lst->len++;
	}
	hant = lst->head;
	while (hant)
	{
		ft_printf("fourmis > %d\n", hant->id_hant);
		hant = hant->next;
	}
}