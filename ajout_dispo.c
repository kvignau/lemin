/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ajout_dispo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:02:22 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/19 17:02:35 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ajout_dispo(t_linkedlst **lstch)
{
	t_node	*tmp;
	int		i;

	tmp = (*lstch)->head;
	while (tmp)
	{
		tmp->array.dispo = (int *)malloc(sizeof(int) * tmp->array.length);
		i = 0;
		while (i < tmp->array.length)
		{
			tmp->array.dispo[i] = 1;
			i++;
		}
		tmp = tmp->next;
	}
}
