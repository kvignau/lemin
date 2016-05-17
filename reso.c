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

void	ft_realloc(t_chemin *ch)
{
	int		*tmp;

	ch->length_malloc *= 2;
	tmp = (int *)malloc(sizeof(int) * ch->length_malloc);
	ft_memcpy(tmp, ch->id, sizeof(int) * ch->length);
	free(ch->id);
	ch->id = tmp;
}

int		lemin(int start, t_fourmiliere *env, t_linkedlst **lstch, t_chemin *ch)
{
	int			i;
	int			ret;
	t_node	 	*tmp;
	int			y;
	int			stop;

	i = 0;
	stop = 0;
	while (stop == 0 && i < env->rooms->nb_rooms)
	{
		if (env->tubes[start][i] == 1 && env->visite[i] == 0)
		{
			if (i == 1)
			{
				if (ch->length == 0)
				{
					if (ch->length >= ch->length_malloc)
					 	ft_realloc(ch);
					ch->id[ch->length] = i;
					ch->length = ch->length + 1;
					stop++;
				}
				ft_addchfront(lstch, ch);
				return (1);
			}
			else
			{
				env->tubes[start][i] = 0;
				env->tubes[i][start] = 0;
				env->visite[i] = 1;
				if (ch->length >= ch->length_malloc)
					ft_realloc(ch);
				ch->id[ch->length] = i;
				ch->length = ch->length + 1;
				ret = lemin(i, env, lstch, ch);
				if (ret == -1)
					return (-1);
				ch->length = ch->length - 1;
				env->visite[i] = 0;
				env->tubes[start][i] = 1;
				env->tubes[i][start] = 1;
			}
		}
		i++;
	}
	return (0);
}
