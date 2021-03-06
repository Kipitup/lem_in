#!/bin/bash

#====ARGV=====#
parsing=false
gen=false
full_check=false
nb_cycle=false
path_to_map=false
continue=false
verbose=false
sanitize=false

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

#eak=false

usage () #
{
	printf "Usage: ./unit_test [-c | v | l | s] [parsing | path_to_map | gen nb_of_test]\n\n"
	printf "You must specify the type of test you want to do:\n"
	printf "\t${MAGENTA}parsing     ${END_C}: test all incorrect or incomplete map\n"
	printf "\t${MAGENTA}path_to_map ${END_C}: launch the program with a specific map to test\n"
	printf "\t${MAGENTA}gen         ${END_C}: launch the generator.\n\n"
	printf "optional flag:\n"
	printf "\t-c: if error, continue\n"
	printf "\t-v: verbose\n"
	printf "\t-s: compile with fsanitize\n"
	printf "\t-l: check leaks\n"
	printf "\t-f: for full check on the generator\n"
	printf "\t--help: show this help message and exit\n\n"
	printf "For multiple flags, put everything in the same argument:\n"
	printf "\texample :-cvl\n\n"
	exit
}

# '-z' : true if the lenght of the string is 0
# '-n' : true if the lenght of the string is nonzero
if [ -n "$1" ]
then
	if [[ $1 == "--help" ]]
	then
		usage
		exit
	fi
	if [[ $1 == "-"*"c"* ]]
	then
		continue=true
	fi
	if [[ $1 == "-"*"v"* ]]
	then
		verbose=true
	fi
	if [[ $1 == "-"*"f"* ]]
	then
		full_check=true
	fi
	if [[ $1 == "-"*"l"* ]]
	then
		leak=true
	elif [[ $1 == "-"*"s"* ]]
	then
		sanitize=true
	fi
	if [[ $1 == "parsing" ]] || [[ $2 == "parsing" ]]
	then
		parsing=true
	elif [[ $1 == "gen" ]] || [[ $2 == "gen" ]]
	then
		gen=true
		if [[ $1 == "gen" ]]
		then
			if [ -n "$2" ]
			then
				nb_cycle=$2
			else
				nb_cycle=10
			fi
		elif [[ $2 == "gen" ]]
		then
			if [ -n "$3" ]
			then
				nb_cycle=$3
			else
				nb_cycle=10
			fi
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
MAP_DIR=maps
PARSING_DIR=parsing
INCORRECT_MAP_DIR=incorrect_map
INCOMPLETE_MAP_DIR=incomplete_map
GEN_DIR=generator
LOG_MAKE=/tmp/log_makefile.txt
LOG_EXEC=/tmp/log_exec.txt
LOG_LEAK="/tmp/leaks.txt"
VALGRIND="valgrind --log-file=${LOG_LEAK} --quiet "
SHOW_LEAK="--track-origins=yes --leak-check=full --show-leak-kinds=definite,indirect"

#======START TEST======#
best=0
equal=0
worse=0
error=0
loop=0
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
elif [ "$sanitize" = true ]
then
	make re debug=1 -j8 > $LOG_MAKE 2>&1
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
	OUTPUT="$(printf $1 | cut -d '/' -f 4 | cut -d '.' -f1):"
	printf "      ${WHITE}%-35s ${END_C}" $OUTPUT
	incorrect=false
	incomplete=false
	if [ $2 == "false" ]
	then
		if grep -q "Error" "$LOG_EXEC"
		then
			incorrect=true
		else
			incorrect=false
		fi
	elif [ $2 == "true" ]
	then
		if grep -q "Error" "$LOG_EXEC"
		then
			incomplete=false
		else
			incomplete=true
		fi
	fi
	if [[ $incorrect == "true" || $incomplete == "true" ]]
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

output_result () #
{
	total_good=$(($best+$equal+$worse))
	pourc_error=$(($error * 100 / $total_nb_test))
	pourc_loop=$(($loop * 100 / $total_nb_test))
	pourc_good=$(($total_good * 100 / $total_nb_test))
	#pourc_error=$(($pourc_error/$total_nb_test))
	printf "\n\n________________________________________________\n"
	printf "|\t\t  ${GREEN}${UNDERLINE}${HIGH}R E S U L T S${END_C}  \t\t|\n"
	printf "|\t\t\t\t\t\t|\n"
	printf "|\t\t\t\t\t\t|\n"
	printf "|\t${CYAN}Total:   ${END_C}${HIGH}$total_nb_test${END_C} \t\t\t\t|\n"
	printf "|\t------------------------------\t\t|\n"
	printf "|\t${YELLOW}Error:${END_C}   ${HIGH}$error${END_C} ($pourc_error %%)\t\t\t|\n"
	printf "|\t\t\t\t\t\t|\n"
	printf "|\t${YELLOW}Loop:${END_C}    ${HIGH}$loop${END_C} ($pourc_loop %%)\t\t\t|\n"
	printf "|\t\t\t\t\t\t|\n"
	printf "|\t${YELLOW}Correct:${END_C} ${HIGH}$total_good${END_C} ($pourc_good %%)\t\t\t|\n"
	printf "|\t   with: - Better: ${HIGH}$best${END_C}\t\t\t|\n"
	printf "|\t\t - Equal:  ${HIGH}$equal${END_C}\t\t\t|\n"
	printf "|\t\t - Worse:  ${HIGH}$worse${END_C}\t\t\t|\n"
	printf "________________________________________________\n"
}



legend_generator () #
{
	printf "\t${YELLOW}Legend:${END_C}\n"
	printf "\t${RED}✖${END_C} => error, program output an error\n"
	printf "\t${MAGENTA}∞${END_C} => loop, program was killed\n"
	printf "\t${LIGHT_GREEN}✓${END_C} => correct, less moves than require\n"
	printf "\t${GREEN}✓${END_C} => correct, as many moves as require\n"
	printf "\t${YELLOW}✓${END_C} => correct, more moves than require\n\n\n"
}

# -e test if file exist
store_result_in_new_file () # $1 is the name of the file
{
	name=$1
	if [[ -e $name.map ]]
	then
    	i=0
    	while [[ -e $name-$i.map ]]
		do
			let i++
		done
		name=$name-$i
	fi
	mv ${MAP_DIR}/${GEN_DIR}/random.map "$name".map
}

# Bash's indirection feature ${!k} to get the parameter k
# ${room1  <-- from variable romm1
# ##   <-- greedy front trim
# *    <-- matches anything
# -    <-- until the last '-'
check_if_room_are_used_only_once () #
{
	end_room=L
	argc=$#
	j=1
	while [[ $j -le $argc ]]
	do
		room1=${!j}
		room1=${room1##*-}
		k=$(($j + 1))
		while [[ $k -le $argc ]]
		do
			room2=${!k}
			room2=${room2##*-}
			if [[ $room1 == $room2 ]]
			then
				if [ "$end_room" == "L" ]
				then
	#				echo ${!j} " and " ${!k}
					end_room=$room1
				elif [ "$room1" != "$end_room" ]
				then
					printf "\n\n${RED}✖${END_C}\n"
					mkdir ${MAP_DIR}/${GEN_DIR}/error_map/ 2>/dev/null
					name=${MAP_DIR}/${GEN_DIR}/error_map/$end_room-or$room1-room-collision
					store_result_in_new_file $name
					printf "The room ${RED}$room1${END_C} is used more than once on the same line\nfile: ${YELLOW}$name${END_C}\n"
					exit
				fi
			fi
			let k++
		done
		let j++
	done
}

# -c for count | '^' for pattern a the beginning only
# sed -n do not echo the output. 2p print the second line 
full_check_output () #
{
	i=1
	p=p
	count=$(grep -c "^L" $LOG_EXEC)
	while [[ $i -le $count ]]
	do
		line=$(grep "^L" $LOG_EXEC | sed -n $i$p)
		check_if_room_are_used_only_once $line
		let i++
	done
}

# grep -c -> count number of match
# grep -m1 -> stop after first match
# sed is here to eliminate the color pattern
# One difference is that [ does not do arithmetic evaluation but [[ does
check_map () # $1 is the test file
{
	if grep -q "Error" "$LOG_EXEC"
	then
		printf "${RED}✖${END_C} "
		mkdir ${MAP_DIR}/${GEN_DIR}/error_map 2>/dev/null
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
		fi
		let error++
		name=${MAP_DIR}/${GEN_DIR}/error_map/$1-ants-error	
		store_result_in_new_file $name
	else
		mkdir ${MAP_DIR}/${GEN_DIR}/correct_map 2>/dev/null
		if [ "$verbose" = true ]
		then
			cat $LOG_EXEC
		fi
		if [ "$full_check" = true ]
		then
			full_check_output $1
		fi
		nb_line=$(grep -c "^L" ${LOG_EXEC})
		limit=$(grep -m1 "#Here is the number of lines required:" ${LOG_EXEC} | sed 's/\[0m//g' | tr -dc "0-9")
		if [[ "$nb_line" -lt "$limit" ]]
		then
			printf "${LIGHT_GREEN}✓${END_C} "
			mkdir ${MAP_DIR}/${GEN_DIR}/correct_map/better 2>/dev/null
			let best++
			name=${MAP_DIR}/${GEN_DIR}/correct_map/better/$1-ants-better
			name=$name-$nb_line-$limit
		elif [[ "$nb_line" -gt "$limit" ]]
		then
			printf "${YELLOW}✓${END_C} "
			mkdir ${MAP_DIR}/${GEN_DIR}/correct_map/worse 2>/dev/null
			let worse++
			name=${MAP_DIR}/${GEN_DIR}/correct_map/worse/$1-ants-worse
			name=$name-$nb_line-$limit
		else
			printf "${GREEN}✓${END_C} "
			mkdir ${MAP_DIR}/${GEN_DIR}/correct_map/equal 2>/dev/null
			let equal++
			name=${MAP_DIR}/${GEN_DIR}/correct_map/equal/$1-ants-equal
			name=$name-$nb_line-$limit
		fi
		store_result_in_new_file $name
	fi
}

handle_map_loop () #
{
	printf "${MAGENTA}∞${END_C} "
	mkdir ${MAP_DIR}/${GEN_DIR}/loop_map 2>/dev/null
	let loop++
	name=${MAP_DIR}/${GEN_DIR}/loop_map/$1-ants-loop	
	store_result_in_new_file $name
}

# $! expands to the last backgrounded process (through the use of &)
# lsof => list open file | -p is for the processus id.
# '#?': return value of the last executed command
# '-eq': equal to
# Bash itself asynchronously, after the kill command has completed, outputs a
# status message about the killed job, which you cannot suppress directly,
# unless you use wait
check_output_generator_map () #
{
	lemin_pid=$!
	j=500
	while [[ $j -gt 0 ]]
	do
		lsof -p $lemin_pid &>/dev/null
		ret=$?
		if [[ $ret -eq 0 ]]
		then
			sleep 0.1
		else
			break
		fi
		j=$(( $j - 1 ))
	done

	if [ $ret -eq 0 ]
	then
		kill $lemin_pid 2>&-
		wait $lemin_pid 2>&-
		handle_map_loop $1
	else
		check_map $1
	fi
}

# time format to gee only the real time not the sys or user time
# time output go directly to STD ERR so you need to redirect it to STD OUT so we
# can store the STD OUT result in a shell variable
mesure_time() #
{
	./generator $1 > $MAP
	TIMEFORMAT='%R'
	time=$( time ( $EXEC < $MAP > $LOG_EXEC 2>&1) 2>&1)
}


generate_big_map_and_test () #
{
	tmp=$3
	while [[ $tmp -gt 0 ]]
	do
		MAP=${MAP_DIR}/${GEN_DIR}/random.map
		./generator $1 > $MAP
		if [ "$leak" = true ]
		then
			TIMEFORMAT='%R'
			time=$( time ( $VALGRIND $SHOW_LEAK $EXEC < $MAP > $LOG_EXEC 2>&1) 2>&1 &)
			check_leak $MAP
		else
			TIMEFORMAT='%R'
			time=$( time ( $EXEC < $MAP > $LOG_EXEC 2>&1) 2>&1 &)
		fi
		check_output_generator_map $2
		printf "${RED}$time s${END_C} | "
		tmp=$(( $tmp - 1 ))
	done
}

generate_map_and_test () #
{
	tmp=$3
	while [[ $tmp -gt 0 ]]
	do
		MAP=${MAP_DIR}/${GEN_DIR}/random.map
		./generator $1 > $MAP
		if [ "$leak" = true ]
		then
			$VALGRIND $SHOW_LEAK $EXEC < $MAP > $LOG_EXEC 2>&1 &
			check_leak $MAP
		else
			$EXEC < $MAP > $LOG_EXEC 2>&1 &
		fi
		check_output_generator_map $2
		tmp=$(( $tmp - 1 ))
	done
	mesure_time $1
}

#======TEST======#
# '-f': vrai si le fichier existe dans le répertoire courant
# '-s': vrai si le fichier existe dans le répertoire courant et si sa taille est supérieure à zéro
# '&' indicate that what follow is a file descriptor
printf "\n----> ${GREEN}Running unit tests:${END_C}\n"

if [ "$parsing" = true ]
then
	printf "      ${UNDERLINE}${YELLOW}incorrect map:${END_C}\n\n"
	
	for MAP in ${MAP_DIR}/${PARSING_DIR}/${INCORRECT_MAP_DIR}/*.map
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
			check_output_parsing_map $MAP false
		fi
	done
	printf "\n      ${UNDERLINE}${YELLOW}incomplete map, should still work:${END_C}\n\n"
	
	for MAP in ${MAP_DIR}/${PARSING_DIR}/${INCOMPLETE_MAP_DIR}/*.map
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
			check_output_parsing_map $MAP true
		fi
	done
elif [ "$gen" = true ]
then
	printf "\n      ${UNDERLINE}${YELLOW}generate a random map:${END_C}\n\n"

	nb_test_big=$(( $nb_cycle / 2 ))
	total_nb_test=$(( $nb_cycle * 3 + $nb_test_big + $nb_test_big))

	legend_generator
	
	mkdir ${MAP_DIR} 2>/dev/null
	mkdir ${MAP_DIR}/${GEN_DIR} 2>/dev/null

	printf "${UNDERLINE}1 ant, map with distinctive path:${END_C}\n"
	generate_map_and_test "--flow-one" "1" $nb_cycle
	printf "\n\n${RED}time: $time s${END_C}"

	printf "\n\n${UNDERLINE}~10 ant, map with distinctive path:${END_C}\n"
	generate_map_and_test "--flow-ten" "10" $nb_cycle
	printf "\n\n${RED}time: $time s${END_C}"
	
	printf "\n\n${UNDERLINE}~100 ant, map with distinctive path:${END_C}\n"
	generate_map_and_test "--flow-thousand" "100" $nb_cycle
	printf "\n\n${RED}time: $time s${END_C}"
   
	printf "\n\n${UNDERLINE}Big map (~1000 rooms) and a lot of ants to test time complexity:${END_C}\n"
	generate_big_map_and_test "--big" "big" $nb_test_big
	
	printf "\n\n${UNDERLINE}Big map with overlapping paths and a lots of ants :${END_C}\n"
	generate_big_map_and_test "--big-superposition" "big-superposition" $nb_test_big

	output_result
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
