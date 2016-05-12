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

int			main(void)
{
	t_fourmiliere	*env;
	//int				start;
	t_chemin		ch;
	t_linkedlst		*lstch;
	t_node			*tmp;//debug
	int 			y;//debug
	int 			j;//debug
	// int i;//debug
	// int j;//debug

	initenv(&env);
	if (!parsing_fourmiliere(&env))//si parsing != 0 display all file
	{
		ft_printf("\nError\n");
		exit (0);//error
	}

	env->visite = (int *)malloc(sizeof(int) * env->rooms->nb_rooms);
	ft_bzero(env->visite, sizeof(int) * env->rooms->nb_rooms);
	env->visite[0] = 1;

	ft_newchemin(&ch);
	initlstchemin(&lstch);

	if (lemin(0, env, &lstch, &ch) == -1)
	{
		ft_printf("\nError\n");
		exit (0);//error
	}
	if (lstch->len == 0)
	{
		ft_printf("\nError\n");
		exit (0);//error
	}
	ft_removecrossch(&lstch);
	nb_chemin(env, &lstch);

	//fonction ajout tableau dispo
	ajout_dispo(&lstch);
	// //debug
	tmp = lstch->head;
	while (tmp)
	{
		y = 0;
		while (y < tmp->array.length)
		{
			ft_printf("%d ", tmp->array.id[y]);
			y++;
		}
		tmp = tmp->next;
		ft_printf("\n");
	}
	ft_printf("\n");
	// tmp = lstch->head;
	// while (tmp)
	// {
	// 	y = 0;
	// 	ft_printf("\n");
	// 	while (y < tmp->array.length)
	// 	{
	// 		ft_printf("%d", tmp->array.dispo[y]);
	// 		y++;
	// 	}
	// 	tmp = tmp->next;
	// }

	//fonction resolution
	check_dispo(lstch, env);
	//debug
	// tmp = lstch->head;
	// while (tmp)
	// {
	// 	y = 0;
	// 	while (y < tmp->array.length)
	// 	{
	// 		ft_printf("%d ", tmp->array.id[y]);
	// 		y++;
	// 	}
	// 	tmp = tmp->next;
	// 	ft_printf("\n");
	// }
	// ft_printf("\n");

	//creation des fourmis
// // fonction de suppression des chemins qui se croisent a revoir
	// t_node	*tmp2;

	// tmp = lstch->head->next;
	// tmp2 = lstch->head;
	// while (tmp)
	// {
	// 	j = 0;
	// 	while (j < tmp2->array.length)
	// 	{
	// 		while (y < tmp->array.length)
	// 		{
	// 			if (tmp2->array.id[j] == tmp->array.id[y])
	// 			{
	// 				ft_delone(&lstch, tmp);
	// 			}
	// 			y++;
	// 		}
	// 		y = 0;
	// 		j++;
	// 	}
	// 	if (tmp->next)
	// 		tmp = tmp->next;
	// 	else
	// 		tmp = lstch->head->next;
	// }

	// tmp = lstch->head;
	// while (tmp)
	// {
	// 	y = 0;
	// 	while (y < tmp->array.length)
	// 	{
	// 		ft_printf("%d ", tmp->array.id[y]);
	// 		y++;
	// 	}
	// 	tmp = tmp->next;
	// 	ft_printf("\n");
	// }
	// ft_printf("\n");
	// ft_printf("start: %d, end: %d\n", start, end);
	// //lemin (start, end, env->tubes, env->rooms->nb_rooms);

	// //debug
	// i = 0;
	// while (i < env->rooms->nb_rooms)
	// {
	// 	j = 0;
	// 	while (j < env->rooms->nb_rooms)
	// 	{
	// 		ft_putnbr(env->tubes[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }

	// while (env->rooms->head)
	// {
	// 	ft_printf("\nid room : %d, nom de la room : %s, x: %d, y: %d, start: %d, end: %d\n", env->rooms->head->id, env->rooms->head->name_room, env->rooms->head->x, env->rooms->head->y, env->rooms->head->start, env->rooms->head->end);
	// 	env->rooms->head = env->rooms->head->next;
	// }
	return (0);
}
