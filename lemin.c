/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:37:07 by kvignau           #+#    #+#             */
/*   Updated: 2016/04/12 13:37:13 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		error(t_linkedlst **lstch, t_fourmiliere **env)
{
	int		i;

	i = 0;
	ft_putstr("Error\n");
	free_ch(lstch);
	if ((*env)->rooms->head != NULL)
	{
		del_room(env);
		if ((*env)->tubes != NULL)
		{
			while (i < (*env)->rooms->nb_rooms)
			{
				free((*env)->tubes[i]);
				i++;
			}
		}
		if ((*env)->visite)
			free((*env)->visite);
	}
	//while (1);
	exit (0);
}

void		del_room(t_fourmiliere **env)
{
	t_rooms	*rooms;

	if ((*env)->rooms->head->next)
		rooms = (*env)->rooms->head->next;
	else
		rooms = NULL;
	while (rooms != NULL)
	{
		free(rooms->prev->name_room);
		free(rooms->prev);
		rooms = rooms->next;
	}
	free((*env)->rooms->tail->name_room);
	free((*env)->rooms->tail);
	(*env)->rooms->head = NULL;
	(*env)->rooms->tail = NULL;
}

void		free_ch(t_linkedlst **lstch)
{
	t_node	*ch;

	if ((*lstch)->head == NULL)
		return ;
	ch = NULL;
	if ((*lstch)->head->next)
		ch = (*lstch)->head;
	while (ch != NULL)
	{
		ft_delone(lstch, ch->prev);
		ch = ch->next;
	}
	free((*lstch)->tail->array.id);
	free((*lstch)->tail->array.dispo);
	free((*lstch)->tail);
	(*lstch)->head = NULL;
	(*lstch)->tail = NULL;
	free(*lstch);
}

// void		free_all(t_linkedlst **lstch, t_fourmiliere **env)
// {
// 	t_rooms	*rooms;
// 	int		i;

// 	i = 0;
// 	free_ch(lstch);
// 	if ((*env)->rooms->head != NULL)
// 	{
// 		if ((*env)->rooms->head->next)
// 			rooms = (*env)->rooms->head->next;
// 		while (i < (*env)->rooms->nb_rooms)
// 		{
// 			free((*env)->tubes[i]);
// 			i++;
// 		}
// 		while (rooms != NULL)
// 		{
// 			free(rooms->prev->name_room);
// 			free(rooms->prev);
// 			rooms = rooms->next;
// 		}
// 		free((*env)->rooms->tail->name_room);
// 		free((*env)->rooms->tail);
// 		(*env)->rooms->head = NULL;
// 		(*env)->rooms->tail = NULL;
// 		free((*env)->visite);
// 	}
// }

void		free_all(t_linkedlst **lstch, t_fourmiliere **env)
{
	int		i;

	i = 0;
	free_ch(lstch);
	if ((*env)->rooms->head != NULL)
	{
		del_room(env);
		if ((*env)->tubes != NULL)
		{
			while (i < (*env)->rooms->nb_rooms)
			{
				free((*env)->tubes[i]);
				i++;
			}
		}
		if ((*env)->visite)
			free((*env)->visite);
	}
}

int			main(void)
{
	t_fourmiliere	*env;
	t_chemin		ch;
	t_linkedlst		*lstch;

	initenv(&env);
	initlstchemin(&lstch);
	if (!parsing_fourmiliere(&env))
		error(&lstch, &env);
	env->visite = (int *)malloc(sizeof(int) * env->rooms->nb_rooms);
	ft_bzero(env->visite, sizeof(int) * env->rooms->nb_rooms);
	env->visite[0] = 1;
	ft_newchemin(&ch);
	if (lemin(0, env, &lstch, &ch) == -1)
		error(&lstch, &env);
	if (lstch->len == 0)
		error(&lstch, &env);
	ft_removecrossch(&lstch);
	nb_chemin(env, &lstch);
	ajout_dispo(&lstch);
	ft_printf("\n");
	check_dispo(lstch, env);
	free_all(&lstch, &env);
	//while (1);
	return (0);
}
