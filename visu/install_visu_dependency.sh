# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_visu_dependency.sh                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartinod <amartino@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/23 11:42:01 by amartinod         #+#    #+#              #
#    Updated: 2020/04/23 11:43:48 by amartinod        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bahs

brew install python3
pip3 install networkx
pip3 install matplotlib
pip3 install itermplot
export MPLBACKEND="module://itermplot"
