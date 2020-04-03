#include "lem_in.h"

void    print_queue(t_queue *queue)
{
    t_adj_node *tmp;
    size_t i;

    i = queue->front;
    if  (queue != NULL)
    {
        ft_printf("\nQueue contains\n");
        for(i = queue->front; i < queue->size; i++)
        {
            ft_printf("links");
            tmp = queue->element[i]->head;
            while (queue->element[i]->head != NULL)
            {
                ft_printf(" -> %d", queue->element[i]->head->dest);
                queue->element[i]->head = queue->element[i]->head->next;
            }
            queue->element[i]->head = tmp;
            ft_printf("\n");
        }
    }   
    else
        ft_printf("Queue is NULL");
}
