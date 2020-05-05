/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 10:25:32 by francis           #+#    #+#             */
/*   Updated: 2020/05/04 17:53:29 by amartinod        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reset_links(t_graph *graph)
{
	t_adj_node	*tmp;
	size_t		i;

	i = 0;
	while (i < graph->size)
	{
		tmp = graph->array[i].head;
		while (tmp != NULL)
		{
			if (tmp->available == CLOSED)
				tmp->available = OPEN;
			tmp = tmp->next;
		}
		i++;
	}
}

// [?] pas très efficient de tout reset puis de remettre les liens utilisé à CLOSED
// idée: faire un DFS (depth first search).
// mmh finalement DFS pas forcément une bonne solution. 
void		update_links(t_solution *sol)
{
	t_path		*path;
	t_path		*curr;
	t_path		*next;
	t_adj_node	*link;
	size_t		i;

	i = 0;
	reset_links(sol->graph);
	while (i <= sol->path->end)
	{
		path = sol->path->contents[i];
		if (path != NULL)
		{
			curr = path;
			while (curr->next != NULL && curr->vertex != sol->graph->size - 1)
			{
				next = curr->next;
				link = get_link(sol->graph, curr->vertex, next->vertex);
//[v] && link->available == OPEN. Évite de assigner CLOSED a un lien déjà CLOSED
				if (link != NULL && link->available == OPEN)
					link->available = CLOSED;
				curr = curr->next;
			}
		}
		i++;
	}
}

void		update_links_with_last_path(t_solution *sol, t_path *path)
{
	t_adj_node	*link;
	t_path		*current;
	t_path		*next;

	update_links(sol);
	current = path;
	while (current->next != NULL)
	{
		next = current->next;
		link = get_link(sol->graph, current->vertex, next->vertex);
		//[v] pareil que avant. Perturbant d'utiliser '!=' et '<' pour la meme chose
		if (link != NULL && link->available == OPEN)
			link->available = CLOSED;
		current = current->next;
	}
}
