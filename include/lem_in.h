/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/03/10 15:14:26 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "ft_printf.h"
# include "define_lem_in.h"
# include "hashmap.h"

enum	e_states
{
	E_ANT,
	E_ROOM,
	E_LINK,
	E_COMMAND,
	E_ERROR,
	E_END
};

typedef struct	s_lemin
{
	t_vector		*output;
	t_hashmap		*room;
	t_vector		*link;
	t_vector		*start;
	t_vector		*end;
	size_t			nb_ants;

}				t_lemin;

typedef struct	s_st_machine
{
	t_lemin			*lemin;
	enum e_states	state;
}				t_st_machine;

typedef uint8_t		(*t_state_func)(t_st_machine *sm, t_vector *line);

/*
** ############################# ADJACENCY LIST ###############################
*/
typedef struct	s_adj_node
{
	size_t				dest;
	struct s_adj_node	*next;
}				t_adj_node;

typedef struct	s_adj_list
{
	t_adj_node			*head;
}				t_adj_list;

typedef struct	s_graph
{
	t_adj_list			*array;
	size_t				size;
}				t_graph;

/*
** ############################################################################
** ################################# INIT #####################################
** ############################################################################
*/
t_lemin			*init(void);
void			parse(t_st_machine *sm);
uint8_t			ant(t_st_machine *sm, t_vector *line);
uint8_t			room(t_st_machine *sm, t_vector *line);
uint8_t			room_link(t_st_machine *sm, t_vector *line);
uint8_t			command(t_st_machine *sm, t_vector *line);
int8_t 			get_room(t_st_machine *sm, t_vector *line);
uint8_t			is_it_all_digit(t_vector *line);
uint8_t			check_for_comment_or_command(t_st_machine *sm, t_vector *line);
void			add_line_to_output(t_st_machine *sm, t_vector *line, uint8_t type);

/*
** ############################################################################
** ################################# TOOL #####################################
** ############################################################################
*/
void			get_second_coord(t_vector *coord, char *second_coord);
char			*get_coord(t_st_machine *sm, t_vector *line);
t_vector	 	*get_room_name(t_st_machine *sm, t_vector *dup);

/*
** ############################################################################
** ################################# LIST #####################################
** ############################################################################
*/
t_adj_node		*new_adj_list_node(size_t dest);
t_graph			*init_graph(size_t size);
int8_t			add_edge(t_graph *graph, size_t src, size_t dest);
void			print_link(t_graph *graph);
void			clean_recurse(t_adj_node **node);
void			clean_graph(t_graph **graph);

/*
** ############################################################################
** ################################# CLEAN ####################################
** ############################################################################
*/
void			clean_lemin(t_lemin **lemin);
void			clean_state_machine(t_st_machine **sm);

#endif
