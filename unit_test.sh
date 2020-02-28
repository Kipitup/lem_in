# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    unit_test.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartino <amartino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/27 17:38:05 by amartino          #+#    #+#              #
#    Updated: 2020/02/28 15:45:53 by amartino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#!/bin/bash

#====ARGV=====#
# '-z' : true if the string is null / empty
continue=false
verbose=false
if [ -n "$1" ]
then
	if [[ $1 == *"c"* ]]
	then
		continue=true
	fi
	if [[ $1 == *"v"* ]]
	then
		verbose=true
	fi
	if [[ $1 == "--help" ]]
	then
		printf "usage: ./unit_test [-c v] \n"
		exit
	fi
fi

#====EDIT PATH=====#
EXEC=./lem-in
MAP_DIR=maps/map_unit_test
INCORRECT_MAP_DIR=incorrect_map
CORRECT_MAP_DIR=correct_map
LOG_MAKE=/tmp/log_exec.txt
LOG_EXEC=/tmp/log_exec.txt
LOG_LEAK="/tmp/leaks.txt"
VALGRIND="valgrind --log-file=${LOG_LEAK} --quiet "
SHOW_LEAK="--track-origins=yes --leak-check=full --show-leak-kinds=definite,indirect"


#======COLORS======#
EOC="\033[0m";
RED="\033[31m";
GREEN="\033[32m";
LIGHT_GREEN="\033[92m";
YELLOW="\033[33m"
BLUE="\033[34m"
MAGENTA="\033[35m"
CYAN="\033[36m"
WHITE="\033[37m"
HIGH="\033[1m";
UNDERLINE="\033[4m";
END_C="\033[0m";


#======START TEST======#
# Beautifulllll message
printf "\n----> ${CYAN}U ${MAGENTA}N ${YELLOW}I ${WHITE}T  ${RED}T ${GREEN}E ${YELLOW}S ${MAGENTA}T ${END_C} ${HIGH}LEM-IN${END_C} <----\n\n"


#======MAKE======#
# redirige la sortie d'erreur (2) et la sortie standard (1) dans un fichier
# '#?': return value of the last executed command
# '-ne': not equal to
echo "----> ${GREEN}Makefile running${END_C}\n"

make > $LOG_MAKE 2>&1
if [ "$?" -ne 0 ]
then
   printf "${RED}Makefile failed${END_C} \n"
   cat $LOG_MAKE
   exit
fi

#======MAIN_FUNC======#
# The grep is done because, sometime, after a test is leaking, the next one
# throw a comment even though there is no leak. So I make sure there is no
# comment before throwing an error. If you know why, please fix it.
check_leak () # $1 is the test file
{
	if [ -s $LOG_LEAK ]
	then
		grep -q "run: /usr/bin/dsymutil" "$LOG_LEAK"
		if [ "$?" -eq 1 ]
		then
			printf "      ${RED}LEAK ERROR: ${WHITE}$1${END_C}\n"
			if [ "$verbose" = true ]
			then
				cat $LOG_LEAK
			fi
			if [ "$continue" = false ]
			then
				exit
			fi
		fi
	fi
}

check_output_incorrect_map () # $1 is the test file
{
	OUTPUT="$(printf $1 | cut -d '/' -f 4)"
	OUTPUT+=":"
	printf "      ${WHITE}%-35s ${END_C}" $OUTPUT
	if grep -q "error" "$LOG_EXEC"
	then
		printf "${LIGHT_GREEN}✓${END_C}\n"
	else
		printf "${RED}✖${END_C}\n"
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
		fi
		if [ "$continue" = false ]
		then
			exit
		fi
	fi
}

check_output_correct_map () # $1 is the test file
{
	OUTPUT="$(printf $1 | cut -d '/' -f 4)"
	OUTPUT+=":"
	printf "      ${WHITE}%-35s ${END_C}" $OUTPUT
	if grep -q "error" "$LOG_EXEC"
	then
		printf "${RED}✖${END_C}\n"
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
		fi
		if [ "$continue" = false ]
		then
			exit
		fi
	else
		printf "${LIGHT_GREEN}✓${END_C}\n"
	fi
}

#======TEST======#
# '-f': vrai si le fichier existe dans le répertoire courant
# '-s': vrai si le fichier existe dans le répertoire courant et si sa taille est supérieure à zéro
echo "----> ${GREEN}Running unit tests:${END_C}\n"

printf "      ${UNDERLINE}${YELLOW}incorrect map:${END_C}\n\n"

for MAP in ${MAP_DIR}/${INCORRECT_MAP_DIR}/*.map
do
	if test -f $MAP
	then
		$VALGRIND $SHOW_LEAK $EXEC < $MAP > $LOG_EXEC
		check_leak $MAP
		check_output_incorrect_map $MAP
	fi
done

printf "\n      ${UNDERLINE}${YELLOW}correct map:${END_C}\n\n"

for MAP in ${MAP_DIR}/${CORRECT_MAP_DIR}/*.map
do
	if test -f $MAP
	then
		$VALGRIND $SHOW_LEAK $EXEC < $MAP > $LOG_EXEC
		check_leak $MAP
		check_output_correct_map $MAP
	fi
done

#======THE END======#
printf "\n\n----> ${GREEN}Unit test complete!${END_C}\n"
