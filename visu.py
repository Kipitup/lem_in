# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    visu.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 11:00:06 by amartinod         #+#    #+#              #
#    Updated: 2020/04/22 16:08:30 by amartinod        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()

filepath = '/tmp/visu_lemin.txt'
with open(filepath) as fp:
   line = fp.readline()
   while line:
       line = line.rstrip('\n')
       data = line.split('-') #split string into a list
       G.add_edge(int(data[0]), int(data[1]))
       line = fp.readline()

pos=nx.spring_layout(G) # positions for all nodes

nodes = list(G.nodes)

firstNode = nodes.pop(0)

max_value = max(nodes)
max_index = nodes.index(max_value)
lastNode = nodes.pop(max_index)

nx.draw_networkx_nodes(G, pos, nodes, node_color='b')
nx.draw_networkx_nodes(G, pos, nodelist=[firstNode], node_color='g')
nx.draw_networkx_nodes(G, pos, nodelist=[lastNode], node_color='r')

nx.draw_networkx_edges(G, pos, list(G.edges))

nx.draw_networkx_labels(G, pos, font_size=10)

plt.axis('off')
plt.show()
