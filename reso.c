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

// int			lemin(int start, int end, int **matrice, int longueur)
// {
// 	int		i;

// 	i = 0;
// 	//la premiere fois id room == start
// 	while (i < longueur)
// 	{
// 		if (matrice[start][i] == 1)
// 		{
// 			if (i == end)
// 			{
// 				ft_printf("coucou\n");
// 				ft_printf("%d ", i);
// 				return (1);
// 			}
// 			matrice[start][i] = 0;
// 			matrice[i][start] = 0;
// 			if (lemin(i, end, matrice, longueur) == 1)
// 			{
// 				// matrice[start][i] = 1;
// 				// matrice[i][start] = 1;
// 				ft_printf("%d ", i);
// 				return (1);
// 			}
// 			matrice[start][i] = 1;
// 			matrice[i][start] = 1;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int		lemin(int start, int end, int **matrice, int longueur)
{
	int		i;
	int		y;
	int		j;

	i = 0;
	y = 0;
	//la premiere fois id room == start
	// ft_printf("START %d\n", start);
	while (i < longueur)
	{
		ft_printf("matrice[%d][%d] == %d\n", start, i, matrice[start][i]);
		if (matrice[start][i] == 1)
		{
			if (i == end)
			{
				ft_printf("!end reached [%d]\n", i);
				ft_printf("COUCOU\n");
				// ft_printf("\nmatrice finale\n");
				// while (y < longueur)
				// {
				// 	j = 0;
				// 	while (j < longueur)
				// 	{
				// 		ft_putnbr(matrice[y][j]);
				// 		j++;
				// 	}
				// 	ft_printf("\n");
				// 	y++;
				// }
				return (1);
			}
			else
			{
				matrice[start][i] = 0;
				matrice[i][start] = 0;
				// ft_printf("\nnouvelle matrice \n");
				// while (y < longueur)
				// {
				// 	j = 0;
				// 	while (j < longueur)
				// 	{
				// 		ft_putnbr(matrice[y][j]);
				// 		j++;
				// 	}
				// 	ft_printf("\n");
				// 	y++;
				// }
				ft_printf("jump to [%d]\n", i);
				if (lemin(i, end, matrice, longueur) == 0)
				{
					ft_printf("return to last [-1]\n");
					
				}
				else
				{
					ft_printf("save this way!\n");
				}
				matrice[start][i] = 1;
				matrice[i][start] = 1;
			}
		}
		i++;
	}
	return (0);
}
