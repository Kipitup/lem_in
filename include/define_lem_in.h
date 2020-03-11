/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_lem_in.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartino <amartino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 11:16:29 by amartino          #+#    #+#             */
/*   Updated: 2020/03/11 11:33:36 by amartino         ###   ########.fr       */
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
# define NO_START_OR_END	"Room start and/or end is missing"
# define DASH_IN_ROOM_NAME	"Room name cannot contain '-'"

#endif
