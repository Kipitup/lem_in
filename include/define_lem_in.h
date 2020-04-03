/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/03/12 11:21:47 by amartino         ###   ########.fr       */
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
# define OPEN                           0

# define COMMENT			0
# define COMMAND			1
# define ANT				2
# define ROOM				3
# define ROOM_LINK			4
# define SPECIAL_ROOM		5
# define NOT_SET			-1

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
# define QUEUE_FULL	        "Queue Overflow, too many elements"
# define QUEUE_EMPTY	        "Queue is empty"

#endif
