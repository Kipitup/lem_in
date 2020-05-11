/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 14:59:02 by amartinod         #+#    #+#             */
/*   Updated: 2020/05/11 09:57:22 by francis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int8_t	err_wont_stop_lemin(int8_t error)
{
	if (error == WRONG_LINK_FORMAT)
		ft_perror("Wrong input format", NULL, 0);
	else if (error == READ_LINE_ERR)
		ft_perror("reading the the standard input failed", NULL, 0);
	else if (error == ROOM_DONT_EXIST)
		ft_perror("You're trying to link a room that doesn't exist", NULL, 0);
	else if (error == STD_OUT_CLOSE)
		ft_perror("STD OUT is close. THe output cannot be print", NULL, 0);
	return (SUCCESS);
}

static int8_t	err_from_malloc(int8_t error)
{
	if (error == MALLOC_ERR)
		ft_perror("memory allocation failed", NULL, 0);
	else if (error == LEMIN_UNITIALIZED)
		ft_perror("Lemin struct was not initialized properly", NULL, 0);
	else if (error == ADJ_LIST_MALLOC)
		ft_perror("Fail to init the adjacency list", NULL, 0);
	else if (error == VECTOR_FAIL)
		ft_perror("Vector allocation failed", NULL, 0);
	else if (error == ADD_EDGE_FAILED)
		ft_perror("Adding an edge to the adjacency list failed", NULL, 0);
	else if (error == GRAPH_NULL)
		ft_perror("Graph is NULL", NULL, 0);
	return (FAILURE);
}

static void		err_will_stop_lemin_next(int8_t error)
{
	if (error == DASH_IN_ROOM_NAME)
		ft_perror("Room name cannot contain '-'", NULL, 0);
	else if (error == ROOM_START_WITH_L)
		ft_perror("Room name cannot start with an 'L'", NULL, 0);
	else if (error == NO_VALID_LINK)
		ft_perror("No valid link", NULL, 0);
	else if (error == ROOM_DUPLICATE)
		ft_perror("There can’t be two rooms with the same name", NULL, 0);
}

static int8_t	err_will_stop_lemin(int8_t error)
{
	if (error == EMPTY_FILE)
		ft_perror("Empty file", NULL, 0);
	else if (error == NO_START)
		ft_perror("Room start is missing", NULL, 0);
	else if (error == NO_END)
		ft_perror("Room end is missing", NULL, 0);
	else if (error == NO_LINK_TO_START)
		ft_perror("Missing a link to the start room", NULL, 0);
	else if (error == NO_LINK_TO_END)
		ft_perror("Missing a link to the end room", NULL, 0);
	else if (error == MANY_START_OR_END)
		ft_perror("There is more than one room start or/and room end", NULL, 0);
	else if (error == COORD_NOT_INT)
		ft_perror("Coordinates should be a positive integer", NULL, 0);
	else if (error == ANT_NOT_INT)
		ft_perror("Ant should be a positive integer", NULL, 0);
	else if (error == NO_ROOM_AFTER_CMD)
		ft_perror("No room specified after the command start or end", NULL, 0);
	else
		err_will_stop_lemin_next(error);
	return (FAILURE);
}

int8_t		error_management(int8_t error)
{
	int8_t		ret;

	if (error == FAILURE)
		ret = ft_perror_failure("error not specified", NULL, 0);
	else if (error >= ERR_FROM_MALLOC)
		ret = err_from_malloc(error);
	else if (error >= ERR_STOP_LEMIN)
		ret = err_will_stop_lemin(error);
	else
		ret = err_wont_stop_lemin(error);
	return (ret);
}
