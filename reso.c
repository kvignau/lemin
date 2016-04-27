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

void		lemin(int start, int end, int **matrice, int longueur)
{
	int		i;
	static char *tmp;

	i = 0;
	//la premiere fois id room == start
	// ft_printf("START %d\n", start);
	while (i < longueur)
	{
		if (matrice[start][i] == 1)
		{
			if (i == end)
			{
				ft_printf("%s\n", tmp);
				tmp = NULL;
///				ft_printf("%d ", i);
				//save chemin
				return ;
			}
			else
			{
				matrice[start][i] = 0;
				matrice[i][start] = 0;
				if (tmp)
					tmp = ft_strjoin(tmp, ft_itoa(i));
				else
					tmp = ft_strdup(ft_itoa(i));
				lemin(i, end, matrice, longueur);
				if (tmp && ft_strlen(tmp) > 1)
					tmp[ft_strlen(tmp) - 1] = '\0';
					// matrice[start][i] = 1;
					// matrice[i][start] = 1;
					// return (1);
				matrice[start][i] = 1;
				matrice[i][start] = 1;
			}
		}
		i++;
	}
	// return (1);
}
