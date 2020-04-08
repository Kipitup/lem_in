/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/04/08 17:44:43 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "define_lem_in.h"

enum	e_states
{
	E_ERROR = FAILURE,
	E_ANT = 0,
	E_ROOM = 1,
	E_LINK = 2,
	E_COMMAND = 3,
	E_END = 4
};

typedef struct	s_solution
{
	t_darray			*path;
	t_graph				*graph;
	struct s_solution	*next;
}				t_solution;

typedef struct	s_lemin
{
	t_vector			*output;
	t_hashmap			*room;
	t_graph				*link;
	t_solution			*result;
	t_vector			*start;
	t_vector			*end;
	size_t				nb_ants;
}				t_lemin;

typedef struct	s_st_machine
{
	t_lemin				*lemin;
	enum e_states		state;
	char				padding[4];			
}				t_st_machine;

typedef uint8_t		(*t_state_func)(t_st_machine *sm, t_vector *line);

/*
** ############################################################################
** ################################# INIT #####################################
** ############################################################################
*/
t_lemin			*init(void);
void			init_adjacency_list(t_st_machine *sm);
void			parse(t_st_machine *sm);
uint8_t			ant(t_st_machine *sm, t_vector *line);
uint8_t			room(t_st_machine *sm, t_vector *line);
int8_t			get_room(t_st_machine *sm, t_vector *line);
uint8_t			room_link(t_st_machine *sm, t_vector *line);
uint8_t			command(t_st_machine *sm, t_vector *line);

/*
** ############################################################################
** ################################# TOOL #####################################
** ############################################################################
*/
void			add_line_to_output(t_st_machine *sm, t_vector *line, uint8_t type);
uint8_t			is_it_all_digit(t_vector *line);
uint8_t			check_for_comment_or_command(t_st_machine *sm, t_vector *line);
uint8_t			is_it_special_room(t_st_machine *sm, t_hashnode *src,
								t_hashnode *dest);

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
