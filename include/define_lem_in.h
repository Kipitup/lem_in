/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/04/22 11:39:14 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_LEM_IN_H
# define DEFINE_LEM_IN_H

# define FALSE				0
# define TRUE				1
# define SUCCESS			0
# define FAILURE			-1
# define START				0
# define END				1
# define VISITED			1
# define UNVISITED			-1
# define OPEN				0
# define CLOSED				1
# define USED_MULTIPLE		2

# define COMMENT			0
# define COMMAND			1
# define ANT				2
# define ROOM				3
# define ROOM_LINK			4
# define SPECIAL_ROOM		5
# define NOT_SET			-1
# define VISU				1

# define MALLOC_ERR			"memory allocation failed"
# define ROOM_DONT_EXIST	"You're trying to link a room that doesn't exist"
# define WRONG_LINK_FORMAT	"Wrong input format"
# define ADJ_LIST_MALLOC	"Fail to init the adjacency list"
# define VECTOR_FAIL		"Vector allocation failed"
# define EMPTY_FILE			"Empty file"
# define NO_START			"Room start is missing"
# define NO_END				"Room end is missing"
# define NO_LINK_TO_START	"Missing a link to the start room"
# define NO_LINK_TO_END		"Missing a link to the end room"
# define DASH_IN_ROOM_NAME	"Room name cannot contain '-'"
# define ROOM_START_WITH_L	"Room name cannot start with an 'L'"
# define MANY_START_OR_END	"There is more than one room start or/and room end"
# define COORD_NOT_INT		"Coordinates should be a positive integer"
# define ANT_NOT_INT		"Ant should be a positive integer"
# define NO_ROOM_AFTER_CMD	"No room specified after the command start or end"
# define READ_LINE_ERR		"Reading the the standard input failed"
# define ADD_EDGE_FAILED	"Adding an edge to the adjacency list failed"
# define QUEUE_FULL	        "Queue Overflow, too many elements"
# define QUEUE_EMPTY        "Queue is empty"

#endif
