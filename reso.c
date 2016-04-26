/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reso.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 17:34:35 by kvignau           #+#    #+#             */
/*   Updated: 2016/04/21 17:34:55 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			lemin(int start, int end, int **matrice, int longueur)
{
	int		i;

	i = 0;
	//la premiere fois id room == start
	while (i < longueur)
	{
		if (matrice[start][i] == 1)
		{
			if (i == end)
			{
				ft_printf("coucou\n");
				ft_printf("%d ", i);
				return (1);
			}
			matrice[start][i] = 0;
			matrice[i][start] = 0;
			if (lemin(i, end, matrice, longueur) == 1)
			{
				// matrice[start][i] = 1;
				// matrice[i][start] = 1;
				ft_printf("%d ", i);
				return (1);
			}
			matrice[start][i] = 1;
			matrice[i][start] = 1;
		}
		i++;
	}
	return (0);
}

// int			lemin(t_rooms *room, int **matrice)
// {
// 	int		i;
// 	int		y;
// 	t_rooms *tmp;

// 	i = 0;
// 	ft_printf("room id %d\n", room->id);
// 	while (i < 4)
// 	{
// 		ft_printf("\nid matrice %d", i);
// 		if (matrice[room->id][i] == 1)
// 		{
// 			tmp = room;
// 			y = 0;
// 			while (tmp && y < i)
// 			{
// 				tmp = tmp->next;
// 				y++;
// 			}
// 			ft_printf("\nCOUCOU");
// 			if (tmp->end == 1)
// 				return (1);
// 			else
// 				return (lemin(tmp, matrice));
// 		}
// 		i++;
// 	}
// 	ft_printf("\nnom de la salle nok : %s", tmp->name_room);
// 	return (0);
// }

// void		lemin()
// {
// 	int		start;
// 	int		end;
// 	t_rooms	*tmp;

// 	tmp = env->rooms->head;
// 	while (tmp)
// 	{
// 		if (tmp->start == 1)
// 			start = tmp->id;
// 		if (tmp->end == 1)
// 			end = tmp->id;
// 		tmp = tmp->next;
// 	}
// 	while (i < env->rooms->nb_rooms)
// 	{
// 		if (matrice[start][i] == 1)
// 	}
// }