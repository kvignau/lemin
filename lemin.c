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
	ft_putstr("Error");//free everythings

}

int			main(void)
{
	t_fourmiliere	*env;
	t_chemin		ch;
	t_linkedlst		*lstch;

	initenv(&env);
	if (!parsing_fourmiliere(&env))
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
	ajout_dispo(&lstch);
	ft_printf("\n");
	check_dispo(lstch, env);
	return (0);
}
