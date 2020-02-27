# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unit_test.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartino <amartino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 17:38:05 by amartino          #+#    #+#              #
#    Updated: 2020/02/27 20:00:34 by amartino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#====EDIT PATH=====#

EXEC=./lem-in
LEAK_FILE="leaks.txt"
VALGRIND="valgrind --log-file=${LEAK_FILE}"
SHOW_LEAK=" --track-origins=yes --leak-check=full --show-leak-kinds=definite,indirect"
#======COLORS======#

EOC="\033[0m";
RED="\033[31m";
GREEN="\033[32m";
YELLOW="\033[33m"
BLUE="\033[34m"
PINK="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
HIGH="\033[1m";
END_C="\033[0m";

printf "\n----> ${CYAN}U ${PINK}N ${YELLOW}I ${WHITE}T  ${RED}T ${GREEN}E ${YELLOW}S ${PINK}T ${END_C} ${HIGH}LEM_IN${END_C} <----\n\n"


# $EXEC < maps/for_parsing.map

$VALGRIND $EXEC < maps/for_parsing.map

grep -A 1 "definitely lost" ${LEAK_FILE} | cut -d : -f 2

#======TEST======#

# echo "Running unit tests:"
# for i in tests/*_tests
# do
# 	if test -f $i
# 	then
# 		if $VALGRIND $NAME < $i 2>> tests/tests.log
# 		then
# 			echo $i PASS
# 		else
# 			echo "ERROR in test $i: here's tests/tests.log"
# 			echo "------"
# 			tail tests/tests.log
# 			exit 1
# 		fi
# 	fi
# done
# echo ""
