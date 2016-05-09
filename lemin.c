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

int			iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
	{
		ft_printf("\n%s\n", line);//debug
		return (1);
	}
	return (0);
}

int			nbfourmis(char *line, t_fourmiliere **env)
{
	int		i;

	i = 0;
	if (line && line[0] == '+')
		i++;
	while (line && line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	(*env)->nb_fourmis = ft_atoi(line);
	if ((*env)->nb_fourmis == 0 && line[0] != '0')
		return (0);
	return (1);
}

int					test_room(char *line)
{
	int				i;
	int				space;

	i = 0;
	space = 0;
	while (line && line[i])
	{
		if (line[i] == ' ')
			space++;
		else if (space != 0 && !ft_isdigit(line[i]))			
			return (-1);
		i++;
	}
	if (space == 2)
		return (1);
	return (0);
}

int				ft_room(t_fourmiliere **env, char *line, int *end, int *start)
{
	char		**recup;
	t_rooms		*room;
	int			ok;
	t_rooms		*tmp;
	static int	nb = 1;

	if (line[0] == '#' && line[1] == '#')
	{
		if (ft_strequ("start", line + 2))
			(*start)++;
		else if (ft_strequ("end", line + 2))
			(*end)++;
		else
			return (-1);
	}
	else
	{
		recup = ft_strsplit(line, ' ');
		if (!recup[0] || !recup[1] || !recup[2])
		{
			ft_deltab(recup);
			return (0);
		}
		ok = test_room(line);
		if (ok != 1)
			return (ok);//error();
		tmp = HROOMS;
		while (tmp)
		{
			if (ft_strequ(tmp->name_room, recup[0]))
				return (-1);
			tmp = tmp->next;
		}
		ft_newroom(&room, ft_strdup(recup[0]), ft_atoi(recup[1]), ft_atoi(recup[2]));
		ft_addroomfront(env, room);
		ft_deltab(recup);
		if (*start == 1)
		{
			(*env)->rooms->head->id = 0;
			(*env)->rooms->head->start = 1;
			nb--;
		}
		else if (*end == 1)
		{
			(*env)->rooms->head->id = 1;
			(*env)->rooms->head->end = 1;
			nb--;
		}
		else
			(*env)->rooms->head->id = NBROOMS + nb;
		*start = 0;
		*end = 0;
	}
	if ((*env)->rooms->head && (*start) != 1 && (*end) != 1)
		ft_printf("\nid room : %d, nom de la room : %s, x: %d, y: %d, start: %d, end: %d\n", (*env)->rooms->head->id, (*env)->rooms->head->name_room, (*env)->rooms->head->x, (*env)->rooms->head->y, (*env)->rooms->head->start, (*env)->rooms->head->end);
	return (1);
}

int					start_end(t_fourmiliere *env)
{
	t_rooms	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	tmp = env->rooms->head;
	while (tmp)
	{
		if (tmp->start)
			start++;
		if (tmp->end)
			end++;
		tmp = tmp->next;
	}
	if (start == 1 && end == 1)
		return (1);
	return (0);
}

void		ft_initpipe(t_fourmiliere **env)
{
	int		i;

	i = 0;
	(*env)->tubes = (int **)malloc(sizeof(int *) * NBROOMS);
	while (i < NBROOMS)
	{
		(*env)->tubes[i] = (int *)malloc(sizeof(int) * NBROOMS);
		ft_bzero((*env)->tubes[i], sizeof(int) * NBROOMS);
		i++;
	}
}

int			ft_pipe(t_fourmiliere **env, char *line)
{
	// int		i;
	// int		j;
	char	**recup;
	t_rooms	*tmp;
	int		ok;
	int		id_1;
	int		id_2;

	ok = 0;
	recup = ft_strsplit(line, '-');
	if (!recup[0] || !recup[1])
		return (0);
	tmp = HROOMS;
	while (tmp)
	{
		if (ft_strequ(tmp->name_room, recup[0]) || ft_strequ(tmp->name_room, recup[1]))
		{
			if (ok == 0)
				id_1 = tmp->id;
			if (ok == 1)
				id_2 = tmp->id;
			ok++;
		}
		tmp = tmp->next;
	}
	if (ok != 2)
		return (0);
	(*env)->tubes[id_1][id_2] = 1;
	(*env)->tubes[id_2][id_1] = 1;
	ft_deltab(recup);	
	// //debug
	// i = 0;
	// while (i < NBROOMS)
	// {
	// 	j = 0;
	// 	while (j < NBROOMS)
	// 	{
	// 		ft_putnbr((*env)->tubes[i][j]);
	// 		j++;
	// 	}
	// 	ft_printf("\n");
	// 	i++;
	// }
	return (1);
}

void		ft_deltab(char **recup)
{
	int		i;

	i = 0;
	while (recup[i] != NULL)
	{
		free(recup[i]);
		i++;
	}
	free(recup);
}

int			parsing_fourmiliere(t_fourmiliere **env)
{
	char	*line;
	int		end;
	int		start;
	int		roomok;
	int		ok;

	end = 0;
	start = 0;
	roomok = 1;
	ok = 0;
	while (get_next_line(0, &line))
	{
		if (!iscomment(line))
		{
			if ((*env)->nb_fourmis < 0)
			{
				if (!nbfourmis(line, env))
					return (0);
				ft_printf("\n%d\n", (*env)->nb_fourmis);//debug
			}
			else
			{
				if (ok == 0)
				{
					roomok = ft_room(env, line, &end, &start);
					if (roomok == 0)
						ok++;
					if (roomok == -1)
						return (0);
				}
				if (ok == 1)
				{
					if (!start_end(*env))
						return (0);
					ft_initpipe(env);
				}
				if (ok >= 1)
				{
					if (!ft_pipe(env, line))
						return (0);
					ok++;
				}
			}
		}
		free(line);
	}
	return (1);
}

void		ft_removecrossch(t_linkedlst **lstch)
{
	t_node	*tmp;
	t_node	*tmp2;
	int		y;
	int		j;
	int		ok;

	ok = 1;
	tmp = (*lstch)->head;
	while (tmp)
	{
		if (tmp->next)
			tmp2 = tmp->next;
		while (tmp2)
		{
			j = 0;
			while (ok == 1 && j < tmp->array.length)
			{
				y = 0;
				ft_printf("\nvaleur du tmp : %d\n", tmp->array.id[j]);
				while (ok == 1 && y < tmp2->array.length)
				{
					ft_printf("valeur du tmp2 : %d", tmp2->array.id[y]);
					if (tmp->array.id[j] == tmp2->array.id[y])
					{
						ft_printf("\nsuppression\n");
						ft_delone(lstch, tmp2);
						ok = 0;
					}
					y++;
				}
				j++;
			}
			ft_printf("\nchangement de tmp\n");
			tmp2 = tmp2->next;
			ok = 1;
		}
		tmp = tmp->next;
	}
}

int			main(void)
{
	t_fourmiliere	*env;
	int				start;
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
	ft_printf("\n");

	ft_removecrossch(&lstch);

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
