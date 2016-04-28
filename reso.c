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

// int		lemin(int start, int end, int **matrice, int longueur)
// {
// 	int			i;
// 	// int			y;
// 	// int			j;

// 	i = 0;
// 	// y = 0;
// 	//la premiere fois id room == start
// 	ft_printf("START %d\n", start);
// 	ft_printf("end %d\n", end);
// 	while (i < longueur)
// 	{
// 		ft_printf("matrice[%d][%d] == %d\n", start, i, matrice[start][i]);
// 		if (matrice[start][i] == 1)
// 		{
// 			if (i == end)
// 			{
// 				ft_printf("!end reached [%d]\n", i);
// 				ft_printf("COUCOU\n");
// 				// ft_printf("\nmatrice finale\n");
// 				// while (y < longueur)
// 				// {
// 				// 	j = 0;
// 				// 	while (j < longueur)
// 				// 	{
// 				// 		ft_putnbr(matrice[y][j]);
// 				// 		j++;
// 				// 	}
// 				// 	ft_printf("\n");
// 				// 	y++;
// 				// }
// 				return (1);
// 			}
// 			else
// 			{
// 				matrice[start][i] = 0;
// 				matrice[i][start] = 0;
// 				// ft_printf("\nnouvelle matrice \n");
// 				// while (y < longueur)
// 				// {
// 				// 	j = 0;
// 				// 	while (j < longueur)
// 				// 	{
// 				// 		ft_putnbr(matrice[y][j]);
// 				// 		j++;
// 				// 	}
// 				// 	ft_printf("\n");
// 				// 	y++;
// 				// }
// 				ft_printf("jump to [%d]\n", i);
// 				if (lemin(i, end, matrice, longueur) == 0)
// 				{
// 					ft_printf("return to last [-1]\n");
					
// 				}
// 				else
// 				{
// 					ft_printf("save this way!\n");
// 				}
// 				matrice[start][i] = 1;
// 				matrice[i][start] = 1;
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		lemin(int start, t_fourmiliere *env)
{
	int			i;
	// int			y;
	// int			j;

	i = 0;
	// y = 0;
	//la premiere fois id room == start
	ft_printf("START %d\n", start);
	ft_printf("end %d\n", env->id_end);
	while (i < env->rooms->nb_rooms)
	{
		ft_printf("matrice[%d][%d] == %d\n", start, i, env->tubes[start][i]);
		if (env->tubes[start][i] == 1)
		{
			if (i == env->id_end)
			{
				ft_printf("!end reached [%d]\n", i);
				ft_printf("COUCOU\n");
				// ft_printf("\nenv->tubes finale\n");
				// while (y < env->rooms->nb_rooms)
				// {
				// 	j = 0;
				// 	while (j < env->rooms->nb_rooms)
				// 	{
				// 		ft_putnbr(env->tubes[y][j]);
				// 		j++;
				// 	}
				// 	ft_printf("\n");
				// 	y++;
				// }
				return (1);
			}
			else
			{
				env->tubes[start][i] = 0;
				env->tubes[i][start] = 0;
				// ft_printf("\nnouvelle env->tubes \n");
				// while (y < env->rooms->nb_rooms)
				// {
				// 	j = 0;
				// 	while (j < env->rooms->nb_rooms)
				// 	{
				// 		ft_putnbr(env->tubes[y][j]);
				// 		j++;
				// 	}
				// 	ft_printf("\n");
				// 	y++;
				// }
				ft_printf("jump to [%d]\n", i);
				if (lemin(i, env) == 0)
				{
					ft_printf("return to last [-1]\n");
					
				}
				else
				{
					ft_printf("save this way!\n");
				}
				env->tubes[start][i] = 1;
				env->tubes[i][start] = 1;
			}
		}
		i++;
	}
	return (0);
}
