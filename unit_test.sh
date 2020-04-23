#!/bin/bash

#====ARGV=====#
# '-z' : true if the lenght of the string is 0
# '-n' : true if the lenght of the string is nonzero
parsing=false
gen=false
gen_option=false
path_to_map=false
continue=false
verbose=false
leak=false

usage () #
{
	printf "Usage: ./unit_test [-c | v | l] [parsing | path_to_map | gen [generator option]]\n\n"
	printf "You must specify the type of test you want to do:\n"
	printf "\tparsing : test all incorrect map\n"
	printf "\tpath_to_map : launch the program with a specific map to test\n"
	printf "\tgen : launch the generator.\n\n"
	printf "optional flag:\n"
	printf "\t-c: if error, continue\n"
	printf "\t-v: verbose\n"
	printf "\t-l: check leaks\n"
	printf "\t--help: show this help message and exit\n"
	printf "For multiple flags, put everything in the same argument:\n"
	printf "\texample :-cvl\n\n"
	exit
}

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
	if [[ $1 == *"l"* ]]
	then
		leak=true
	fi
	if [[ $1 == "--help" ]]
	then
		usage
		exit
	fi
	if [[ $1 == "parsing" ]] || [[ $2 == "parsing" ]]
	then
		parsing=true
	elif [[ $1 == "gen" ]] || [[ $2 == "gen" ]]
	then
		gen=true
		if [[ $2 == *"--"* ]]
		then
			gen_option=$2
		elif [[ $3 == *"--"* ]]
		then
			gen_option=$3
		else
			gen_option="--help"
		fi
	else
		if [ -n "$2" ]
		then
			path_to_map=$2
		else
			path_to_map=$1
		fi
	fi
else
	usage
	exit
fi

#====EDIT PATH=====#
EXEC=./lem-in
MAP_DIR=maps/
INCORRECT_MAP_DIR=incorrect_map
CORRECT_MAP_DIR=correct_map
LOG_MAKE=/tmp/log_makefile.txt
LOG_EXEC=/tmp/log_exec.txt
LOG_LEAK="/tmp/leaks.txt"
VALGRIND="valgrind --log-file=${LOG_LEAK} --quiet "
SHOW_LEAK="--track-origins=yes --leak-check=full --show-leak-kinds=definite,indirect"


#======COLORS======#
EOC="\e[0m";
RED="\e[31m";
GREEN="\e[32m";
LIGHT_GREEN="\e[92m";
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
WHITE="\e[37m"
HIGH="\e[1m";
UNDERLINE="\e[4m";
END_C="\e[0m";


#======START TEST======#
# Beautifulllll message
printf "\n----> ${CYAN}U ${MAGENTA}N ${YELLOW}I ${WHITE}T  ${RED}T ${GREEN}E ${YELLOW}S ${MAGENTA}T ${END_C} ${HIGH}LEM-IN${END_C} <----\n"


#======MAKE======#
printf "\n----> ${GREEN}Makefile running${END_C}\n"

# redirige la sortie d'erreur (2) et la sortie standard (1) dans un fichier
# '#?': return value of the last executed command
# '-ne': not equal to
if [ "$leak" = true ]
then
	make re debug=0 -j8 > $LOG_MAKE 2>&1
else
	make -j8 > $LOG_MAKE 2>&1
fi
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
				printf "\n"
			fi
			if [ "$continue" = false ]
			then
				exit
			fi
		fi
	fi
}

check_output_parsing_map () # $1 is the test file
{
	OUTPUT="$(printf $1 | cut -d '/' -f 4):"
	printf "      ${WHITE}%-35s ${END_C}" $OUTPUT
	if grep -q "Error" "$LOG_EXEC"
	then
		printf "${LIGHT_GREEN}✓${END_C}\n"
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
			printf "\n"
		fi
	else
		printf "${RED}✖${END_C}\n"
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
			printf "\n"
		fi
		if [ "$continue" = false ]
		then
			exit
		fi
	fi
}

check_output_correct_map () # $1 is the test file
{
	OUTPUT="$(printf $1 | cut -d '/' -f 4):"
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
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
		fi
	fi
}

#======TEST======#
# '-f': vrai si le fichier existe dans le répertoire courant
# '-s': vrai si le fichier existe dans le répertoire courant et si sa taille est supérieure à zéro
# '&' indicate that what follow is a file descriptor
printf "\n----> ${GREEN}Running unit tests:${END_C}\n"

if [ "$parsing" = true ]
then
	printf "      ${UNDERLINE}${YELLOW}incorrect map:${END_C}\n\n"
	
	for MAP in ${MAP_DIR}/${INCORRECT_MAP_DIR}/*.map
	do
		if test -f $MAP
		then
			if [ "$leak" = true ]
			then
				$VALGRIND $SHOW_LEAK $EXEC < $MAP > $LOG_EXEC 2>&1
				check_leak $MAP
			else
				$EXEC < $MAP > $LOG_EXEC 2>&1
			fi
			check_output_parsing_map $MAP
		fi
	done
elif [ "$gen" = true ]
then
	printf "\n      ${UNDERLINE}${YELLOW}generate a random map:${END_C}\n\n"

	if [[ $gen_option == "--help" ]]
	then
		./generator $gen_option
	else
		./generator $gen_option > maps/generator/random.map
		if [ "$leak" = true ]
		then
			$VALGRIND $SHOW_LEAK $EXEC < maps/generator/random.map
		else
			$EXEC < maps/generator/random.map
		fi
	fi
else
	printf "\n      ${UNDERLINE}${YELLOW}manual mode:${END_C}\n\n"
	if [ "$leak" = true ]
	then
		$VALGRIND $SHOW_LEAK $EXEC < $path_to_map
	else
		$EXEC < $path_to_map
	fi
fi

#======THE END======#
printf "\n----> ${GREEN}Unit test complete!${END_C}\n"
