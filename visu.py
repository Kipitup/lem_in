# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    visu.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 11:00:06 by amartinod         #+#    #+#              #
#    Updated: 2020/04/22 15:00:03 by amartinod        ###   ########.fr        #
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
       G.add_edge(data[0], data[1], color='red')
       line = fp.readline()

nx.draw(G, with_labels=True, font_weight='bold')
plt.show()
