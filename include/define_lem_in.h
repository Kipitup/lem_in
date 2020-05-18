/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/05/19 00:12:02 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_LEM_IN_H
# define DEFINE_LEM_IN_H

# define LEMIN_BUFF_SIZE	262144

# define FALSE				0
# define TRUE				1
# define SUCCESS			0
# define FAILURE			-1
# define NO_PATH_FOUND		-2
# define FAILED_INIT_QUEUE	-3
# define START				0
# define END				1
# define VISITED			1
# define UNVISITED			-1
# define OPEN				0
# define CLOSED				1
# define USED_MULTIPLE		2

# define ADD_NEW_LINE		0
# define ADD_NO_NEW_LINE	1
# define PRINT				2
# define NOT_SET			-1
# define VISU				1

/*
**	lem-in won't necessarily stop if an error is found. It'll try to work with
**	what he has. This mean that the error can't be output directly. The error
**	code will be store in the state. If state <= FAILURE ; an error was found
*/
# define MALLOC_ERR			-2
# define VECTOR_FAIL		-3
# define ADJ_LIST_MALLOC	-4
# define LEMIN_UNITIALIZED	-5
# define ADD_EDGE_FAILED	-6
# define GRAPH_NULL        	-7

# define ERR_FROM_MALLOC	-7

# define NO_START			-8
# define NO_END				-9
# define NO_LINK_TO_START	-10
# define NO_LINK_TO_END		-11
# define EMPTY_FILE			-12
# define MANY_START_OR_END	-13
# define COORD_NOT_INT		-14
# define ANT_NOT_INT		-15
# define NO_ROOM_AFTER_CMD	-16
# define DASH_IN_ROOM_NAME	-17
# define ROOM_START_WITH_L	-18
# define NO_VALID_LINK		-19
# define ROOM_DUPLICATE		-20
# define NO_PRINTABLE_CHAR	-21
# define NO_ROOM			-22

# define ERR_STOP_LEMIN 	-22

# define WRONG_LINK_FORMAT	-23
# define READ_LINE_ERR		-24
# define ROOM_DONT_EXIST	-25
# define STD_OUT_CLOSE		-26

#endif
