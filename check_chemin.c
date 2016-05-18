/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chemin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 17:36:29 by kvignau           #+#    #+#             */
/*   Updated: 2016/05/10 17:36:42 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		ft_removecrossch(t_linkedlst **lstch)
{
	t_node	*tmp;
	t_node	*tmp2;

	tmp = (*lstch)->head;
	while (tmp)
	{
		if (tmp->next)
			tmp2 = tmp->next;
		else
			return ;
		rm_cross(tmp, tmp2, lstch);
		tmp = tmp->next;
	}
}

void		rm_cross(t_node *tmp, t_node *tmp2, t_linkedlst **lstch)
{
	int		j;
	int		y;
	int		ok;

	ok = 1;
	while (tmp2)
	{
		j = 0;
		while (ok == 1 && j < tmp->array.length)
		{
			y = 0;
			while (ok == 1 && y < tmp2->array.length)
			{
				if (tmp->array.id[j] == tmp2->array.id[y])
				{
					ft_delone(lstch, tmp2);
					ok = 0;
				}
				y++;
			}
			j++;
		}
		tmp2 = tmp2->next;
		ok = 1;
	}
}

void		nb_chemin(t_fourmiliere *env, t_linkedlst **lstch)
{
	int		i;
	int		end_ch;
	int		start_ch;

	i = 0;
	start_ch = 0;
	end_ch = 0;
	while (i < env->rooms->nb_rooms)
	{
		if (env->tubes[0][i] == 1)
			start_ch++;
		i++;
	}
	i = 0;
	while (i < env->rooms->nb_rooms)
	{
		if (env->tubes[1][i] == 1)
			end_ch++;
		i++;
	}
	ft_remove(lstch, nb_chemin_hant(((start_ch < end_ch) ? start_ch : end_ch), env, *lstch));
}

int			nb_chemin_hant(int res, t_fourmiliere *env, t_linkedlst *lstch)
{
	int		i;
	int		ok;
	t_node	*tmp;

	if (lstch->len == 1)
		return (1);
	tmp = lstch->head;
	i = 1;
	ok = 0;
	while (tmp && i < res)
	{
		tmp = tmp->next;
		i++;
	}
	while (tmp && res > 1 && ok == 0)
	{
		if (env->nb_fourmis < tmp->array.length)
		{
			res--;
			tmp = tmp->prev;
		}
		else
			ok = 1;
	}
	return (res);
}

void		ft_remove(t_linkedlst **lstch, int nb_supp)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = (*lstch)->head;
	while (tmp && i < nb_supp)
	{
		tmp = tmp->next;
		i++;
	}
	while (tmp)
	{
		ft_delone(lstch, tmp);
		tmp = tmp->next;
	}
}

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
