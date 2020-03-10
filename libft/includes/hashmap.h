/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkante <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 10:19:29 by fkante            #+#    #+#             */
/*   Updated: 2020/03/10 14:49:21 by fkante           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	HASHMAP_H
# define HASHMAP_H

# include <stdlib.h>
# include <inttypes.h>

# define DJB_HASH_CONSTANT		5381
# define DEFAULT_NB_OF_BUCKETS	4999	

typedef uint8_t 		(*t_hash_comp)(void *, void *);
typedef uint32_t 		(*t_hash_func)(void *, size_t);

/*
** If no compare and hash functions are given, we'll use the default one.
*/
typedef struct	s_hashmap
{
	void			**bucket;
	t_hash_comp		compare;
	t_hash_func		hash;
	size_t			size;
	size_t			nb_of_elem;
	size_t			nb_collision;
}				t_hashmap;

/*
** Work like a dictionnary. You can associate a key with a data.
** For exemple, name could be the key, and 42 the value. 'name' will be hash and
** placed in the array at index: (hash % NB_OF_BUCKETS). At the index, you will
** find the data '42'
*/
typedef struct	s_hashnode
{
	void			*key;
	void			*data;
	uint32_t		hash;
}				t_hashnode;

/*
** ############################################################################
** ################################## HASH ####################################
** ############################################################################
*/
t_hashmap			*hashmap_create(t_hash_comp compare, t_hash_func hash);
t_hashnode			*hash_node_create(void *key, void *data, uint32_t hash);
int8_t				hashmap_set(t_hashmap *map, void *key, void *data);
void				*hashmap_get(t_hashmap *map, void *key);
int8_t				hashmap_resize(t_hashmap *map);
void				del_map(t_hashmap **map);

/*
** ############################################################################
** ############################## TOOLS FUNCTION ##############################
** ############################################################################
*/
uint32_t			ft_hash_void_data(void *data, size_t len);
uint8_t				default_compare(void *a, void *b);
void				print_node(t_hashnode *node, size_t index);
void				print_hashmap(t_hashmap *map);

/*
** ********************************  ERRORS ************************************
*/
# define BUCKET_ALLOC_FAIL	"Malloc fail when trying to create bucket"
# define RESIZE_FAIL		"Malloc fail when trying to resize the hashmap"
# define NO_BUCKET			"No bucket at the specified index"
# define ARRAY_KEY_NULL		"array or key was null while looking for node"
# define NODE_SEARCH_NULL	"Failed to get node"
# define MAP_ALLOC_FAIL		"Malloc fail when trying to create map"
# define MAP_NULL			"Map is null"
# define NODE_NULL			"Node is null"

#endif
