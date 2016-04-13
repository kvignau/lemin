/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 16:15:33 by kvignau           #+#    #+#             */
/*   Updated: 2016/04/13 16:15:48 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		initlstrooms(t_fourmiliere **env)
{
	LSTROOMS = (t_lstrooms *)malloc(sizeof(t_lstrooms));
	if (LSTROOMS == NULL)
		return ;
	else
	{
		LSTROOMS->nb_rooms = 0;
		LSTROOMS->tail = NULL;
		LSTROOMS->head = NULL;
	}
}

void		initenv(t_fourmiliere **env)
{
	initlstrooms(env);
	(*env)->nb_fourmis = -1;
}

void		ft_newroom(t_rooms **room, char *name, int x, int y)
{
	*room = (t_rooms *)malloc(sizeof(t_rooms));
	if (*room == NULL)
		return ;
	(*room)->name_room = name;
	(*room)->x = x;
	(*room)->y = y;
	(*room)->prev = NULL;
	(*room)->next = NULL;
}

void		ft_addroomfront(t_fourmiliere **env, t_rooms *new_elem)
{
	if (TROOMS == NULL)
		TROOMS = new_elem;
	else
	{
		HROOMS->prev = new_elem;
		new_elem->prev = NULL;
		new_elem->next = HROOMS;
	}
	HROOMS = new_elem;
	NBROOMS = NBROOMS + 1;
}

void		ft_delrooms(t_fourmiliere **env)
{
	t_rooms	*tmp;

	tmp = NULL;
	while (HROOMS != NULL)
	{
		tmp = HROOMS->next;
		free(HROOMS);
		HROOMS = tmp;
	}
	TROOMS = NULL;
	HROOMS = NULL;
	free((*env)->rooms);
}
