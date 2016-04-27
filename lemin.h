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
}					t_fourmiliere;


//liste de liste de chemin
typedef struct		s_chemin
{
	int				id;
	// int				visite;
	struct s_chemin	*prev;
	struct s_chemin	*next;
}					t_chemin;

typedef struct		s_lstchemin
{
	size_t			nb_chemin;
	t_chemin		*head;
	t_chemin		*tail;
}					t_lstchemin;

typedef struct			s_listech
{
	t_lstchemin			list_id;
	// int				visite;
	struct s_listech	*prev;
	struct s_listech	*next;
}						t_listech;

typedef struct		s_alllstch
{
	size_t			nb_listechemin;
	t_listech		*head;
	t_listech		*tail;
}					t_alllstch;

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
int					ft_room(t_fourmiliere **env, char *line, int *end, int *start);
int					parsing_fourmiliere(t_fourmiliere **env);
int					ft_pipe(t_fourmiliere **env, char *line);
int					start_end(t_fourmiliere *env);

//reso
int				lemin(int start, int end, int **matrice, int longueur);

#endif