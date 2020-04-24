#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_visu_dependency.sh                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/23 11:42:01 by amartinod         #+#    #+#              #
#    Updated: 2020/04/23 17:01:05 by francis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

sudo apt-get update
sudo apt-get install python3
sudo apt-get install pip3
pip3 install networkx
pip3 install matplotlib
pip3 install itermplot
export MPLBACKEND="module://itermplot"
