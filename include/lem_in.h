/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/02/28 10:46:30 by amartino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "define_lem_in.h"

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
	t_vector		*room;
	t_vector		*link;
	size_t			nb_ants;
}				t_lemin;

typedef struct	s_st_machine
{
	t_lemin			*lemin;
	enum e_states	state;
}				t_st_machine;

typedef uint8_t		(*t_state_func)(t_st_machine *sm, t_vector *line);

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
uint8_t			is_it_all_digit(t_vector *line);
uint8_t			check_for_comment_or_command(t_st_machine *sm, t_vector *line);
void			add_line_to_output(t_st_machine *sm, t_vector *line, uint8_t type);

/*
** ############################################################################
** ################################# TOOL #####################################
** ############################################################################
*/

/*
** ############################################################################
** ################################# CLEAN ####################################
** ############################################################################
*/
void			clean_lemin(t_lemin **lemin);
void			clean_state_machine(t_st_machine **sm);

#endif
