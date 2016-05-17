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
	t_node	*ch;
	t_rooms	*rooms;
	int		i;

	i = 0;
	ft_putstr("Error\n");//free everythings
	ch = (*lstch)->head;
	rooms = (*env)->rooms->head;
	while (ch != NULL)
	{
		free(ch->array.id);
		free(ch->array.dispo);
		ch = ch->next;
	}
	(*lstch)->head = NULL;
	(*lstch)->tail = NULL;
	free(*lstch);
	while (i < (*env)->rooms->nb_rooms)
	{
		free((*env)->tubes[i]);
		i++;
	}
	while (rooms != NULL)
	{
		free(rooms->name_room);
		rooms = rooms->next;
	}
	(*env)->rooms->head = NULL;
	(*env)->rooms->tail = NULL;
	free((*env)->visite);
	while (1);
	exit (0);
	// free(*env);
	// ft_printf("coucou");
}

int			main(void)
{
	t_fourmiliere	*env;
	t_chemin		ch;
	t_linkedlst		*lstch;

	initenv(&env);
	if (!parsing_fourmiliere(&env))
		error(&lstch, &env);
	env->visite = (int *)malloc(sizeof(int) * env->rooms->nb_rooms);
	ft_bzero(env->visite, sizeof(int) * env->rooms->nb_rooms);
	env->visite[0] = 1;
	ft_newchemin(&ch);
	initlstchemin(&lstch);
	if (lemin(0, env, &lstch, &ch) == -1)
		error(&lstch, &env);
	if (lstch->len == 0)
		error(&lstch, &env);
	ft_removecrossch(&lstch);
	nb_chemin(env, &lstch);
	ajout_dispo(&lstch);
	ft_printf("\n");
	check_dispo(lstch, env);
	while (1);
	return (0);
}
