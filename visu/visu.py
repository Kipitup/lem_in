# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    visu.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/22 11:00:06 by amartinod         #+#    #+#              #
#    Updated: 2020/04/24 09:42:59 by amartinod        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import networkx as nx
import matplotlib.pyplot as plt

paths = []

def getEdge(line):
    data = line.split('-') #split string into a list
    G.add_edge(int(data[0]), int(data[1]))

def getPath(line):
    data = line.split(' ')
    for i in range(len(data) - 2):
        paths.append((int(data[i]), int(data[i + 1])))
        i += 1

def initGraph():
    filepath = '/tmp/visu_lemin.txt'
    with open(filepath) as fp:
        line = fp.readline()
        while line:
            line = line.rstrip('\n')
            if line.find('-') != -1:
                getEdge(line)
            else:
                getPath(line)
            line = fp.readline()

def drawNetwork():
    nodes = list(G.nodes)
    firstNode = nodes.pop(0)
    max_value = max(nodes)
    max_index = nodes.index(max_value)
    lastNode = nodes.pop(max_index)
    
    nx.draw_networkx_nodes(G, pos, nodes, node_color='b')
    nx.draw_networkx_nodes(G, pos, nodelist=[firstNode], node_color='g')
    nx.draw_networkx_nodes(G, pos, nodelist=[lastNode], node_color='r')

def drawEdge():
    nx.draw_networkx_edges(G, pos, list(G.edges), edge_color='w')
    edges = list(G.edges)
    nx.draw_networkx_edges(G, pos, paths, edge_color='y')

G = nx.Graph()

# init graph and all position
initGraph()
pos=nx.spring_layout(G)

# draw the graph
drawNetwork()
drawEdge()
nx.draw_networkx_labels(G, pos, font_size=10)

# print the graph
plt.axis('off')
plt.show()
