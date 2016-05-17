/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kvignau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 13:38:06 by kvignau           #+#    #+#             */
/*   Updated: 2016/04/12 13:39:06 by kvignau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "ft_printf/ft_printf.h"
# define MAXINT "2147483647"
# define LSTROOMS (*env)->rooms
# define HROOMS (*env)->rooms->head
# define TROOMS (*env)->rooms->tail
# define NBROOMS (*env)->rooms->nb_rooms

typedef struct		s_rooms
{
	char			*name_room;
	int				x;
	int				y;
	int				start;
	int				end;
	int				id;
	// int				visite;
	struct s_rooms	*prev;
	struct s_rooms	*next;
}					t_rooms;

typedef struct		s_lstrooms
{
	size_t			nb_rooms;
	t_rooms			*head;
	t_rooms			*tail;
}					t_lstrooms;

typedef struct		s_fourmiliere
{
	int				nb_fourmis;
	t_lstrooms		*rooms;
	//rajouter liste des tubes
	int				**tubes;
	int				*visite;
	// int				id_start;
	// int				id_end;
}					t_fourmiliere;


typedef struct		s_chemin
{
	int				*id;
	int				*dispo;
	int				length;
	int				length_malloc;
}					t_chemin;

//liste de liste de chemin
typedef struct		s_node
{
	t_chemin		array;
	struct s_node	*prev;
	struct s_node	*next;
}					t_node;

typedef struct		s_linkedlst
{
	size_t			len;
	t_node			*head;
	t_node			*tail;
}					t_linkedlst;

//liste fourmis
typedef struct		s_ant
{
	int				id_ant;
	int				id_room;
	int				move;
	struct s_ant	*prev;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_lstant
{
	size_t			len;
	t_ant			*head;
	t_ant			*tail;
}					t_lstant;

//action liste, structure
void				initlstrooms(t_fourmiliere **env);
void				initenv(t_fourmiliere **env);
void				ft_newroom(t_rooms **room, char *name, int x, int y);
void				ft_addroomfront(t_fourmiliere **env, t_rooms *new_elem);
void				ft_delrooms(t_fourmiliere **env);

//fonction lemin.c
int					iscomment(char *line);
int					nbfourmis(char *line, t_fourmiliere **env);
int					test_room(char *line);
void				ft_initpipe(t_fourmiliere **env);
int					split_space(char *line);
int					ft_room(t_fourmiliere **env, char *line, int *end, int *start);
int					parsing_fourmiliere(t_fourmiliere **env);
int					split_minus(char *line);
int					ft_pipe(t_fourmiliere **env, char *line);
int					start_end(t_fourmiliere *env);

//chemin
void				initlstchemin(t_linkedlst **lstchemin);
int					ft_newchemin(t_chemin *ch);
void				ft_addchfront(t_linkedlst **lst, t_chemin *new_elem);
void				ft_delone(t_linkedlst **lst, t_node *delnode);
void				ft_removecrossch(t_linkedlst **lstch);
void				ft_remove(t_linkedlst **lstch, int nb_supp);
void				nb_chemin(t_fourmiliere *env, t_linkedlst **lstch);
int					nb_chemin_hant(int res, t_fourmiliere *env, t_linkedlst *lstch);

//reso
int					lemin(int start, t_fourmiliere *env, t_linkedlst **lstch, t_chemin *ch);

void				ft_deltab(char **recup);

//creation fourmis
void				initlstant(t_lstant **lst);
void				ft_newant(t_ant **ant, int id_ant);
void				create_ant(t_lstant	**lst_ant, t_fourmiliere *env);

//move ant
int					finish(t_lstant *lst);
void				check_dispo(t_linkedlst *lst_ch, t_fourmiliere *env);

void				ajout_dispo(t_linkedlst **lstch);
void				display(int id_ant, int id_room, t_fourmiliere *env, int first);
void				debutfin(t_lstant *lst_ant, t_fourmiliere *env);

#endif
