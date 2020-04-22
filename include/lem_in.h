/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/04/22 14:12:21 by amartinod        ###   ########.fr       */
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

typedef struct	s_flow
{
	size_t			len;
	size_t			capacity;
}				t_flow;

typedef struct	s_network
{
	t_darray		*all_path;
	t_flow			*flow;
	size_t			nb_of_flow;
}				t_network;

typedef struct	s_path
{
	char			*name;	
	size_t			vertex;
	size_t			len;
	size_t			ant_nb;
	struct s_path	*next;
}				t_path;

typedef struct	s_solution
{
	t_darray			*path;
	t_graph				*graph;
	struct s_solution	*prev;
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
** ################################ LEMIN #####################################
** ############################################################################
*/
void			lem_in(t_lemin *lemin);

/*
** ############################################################################
** ################################# INIT #####################################
** ############################################################################
*/
t_lemin			*init(void);
void			init_solution(t_lemin *lemin);
void			init_file_for_visu(t_graph *graph);
t_solution		*init_new_solution(t_lemin *lemin);
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
void			rewind_solution(t_lemin *lemin);
uint8_t			is_it_all_digit(t_vector *line);
uint8_t			check_for_comment_or_command(t_st_machine *sm, t_vector *line);
uint8_t			is_it_special_room(t_st_machine *sm, t_hashnode *src,
								t_hashnode *dest);
t_network		*choose_best_solution(t_solution *result, size_t nb_ants);

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

/*
** ############################################################################
** ################################## BFS #####################################
** ############################################################################
*/
int8_t			bfs(t_solution *sol);
t_graph			*init_queue(t_graph *graph_orig);
t_adj_list		next_vertex(t_graph *graph, t_graph *queue);
void			add_step(t_adj_list *node, size_t step);
uint8_t			end_room_visited(t_graph *graph);
void			update_links(t_solution *sol);
void			update_links_with_last_wrong_path(t_solution *sol, t_path *pa);
int8_t			store_valid_path_and_reset(t_solution *sol);
void			handle_link_used_both_way(t_lemin *lemin);
uint8_t			link_used_both_ways(t_graph *graph);
uint8_t			is_path_valid(t_graph *graph, t_path *path);
uint8_t			check_vertex_used(t_solution *sol);

/*
** ############################################################################
** ################################# CLEAN ####################################
** ############################################################################
*/
void			clean_lemin(t_lemin **lemin);
void			clean_path(void *path);
void			clean_state_machine(t_st_machine **sm);
void			clean_network(t_network **net);
void			clean_all_solution(t_lemin **lemin);
void			clean_lst_path(void *path);

/*
** ############################################################################
** ################################# PRINT ####################################
** ############################################################################
*/
void			print_all_links(t_graph *graph);
void			print_link_available(t_adj_list node);
void			print_queue(t_graph *queue);
void			print_path(t_path *path);
void			print_all_path(t_lemin *lemin);
void			print_final_output(t_lemin *lemin);

#endif
