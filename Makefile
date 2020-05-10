# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amartino <amartino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/26 11:56:39 by amartino          #+#    #+#              #
#    Updated: 2020/05/09 12:41:09 by amartinod        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
                     ####################################
                     #                   				#
                     #       	MAIN VARIABLES 			#
                     #                   				#
                     ####################################
NAME = lem-in
LIB_DIR = ./libft
LIB = libft.a
CC = gcc
CFLAGS += -Wall -Wextra -Werror
INCLUDES += -I./include
INCLUDES += -I./libft/includes
INCLUDES += -I./libft/ft_printf/includes
HEAD += ./include/define_lem_in.h
HEAD += ./include/lem_in.h


                     ####################################
                     #                   				#
                     #       	  	IFEQ	   			#
                     #                   				#
                     ####################################
# FLAGS
ifeq ($(debug), 0)
	CFLAGS += -g3
else ifeq ($(debug), 1)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
else ifeq ($(debug), 2)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -pedantic
else ifeq ($(debug), 3)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -g3
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -pedantic
	CFLAGS += -Wpadded
	CFLAGS += -Weverything
endif

                     ####################################
                     #                   				#
                     #       		PATHS     			#
                     #                   				#
                     ####################################
# LIB
LIB_PATH = $(LIB_DIR)/$(LIB)

# SRCS
PATH_SRC += srcs
PATH_SRC += srcs/init
PATH_SRC += srcs/solve
PATH_SRC += srcs/solve/bfs
PATH_SRC += srcs/print
PATH_SRC += srcs/clean

vpath %.c $(PATH_SRC)

                     ####################################
                     #                   				#
                     #       	   SOURCE      			#
                     #                   				#
                     ####################################
# main
SRCS += main

# init
SRCS += init
SRCS += init_solution
SRCS += init_file_for_visu
SRCS += parse
SRCS += parse_ant
SRCS += parse_room
SRCS += parse_room_link
SRCS += parse_command
SRCS += parse_tools
SRCS += error_management

# solve
SRCS += lem_in
SRCS += init_and_set_network
SRCS += smart_ant_management

# bfs
SRCS += bfs

# tools 
SRCS += bfs_tools 
SRCS += bfs_second_tools 
SRCS += bfs_store_and_repath 
SRCS += update_links
SRCS += is_path_valid 
SRCS += handle_link_used_both_way
SRCS += output
SRCS += check_vertex_used

# print
SRCS += print_queue 
SRCS += buffer 
SRCS += print_path 
SRCS += print_path_second 

# clean
SRCS += clean
                     ####################################
                     #                   				#
                     #       	  VARIABLES    			#
                     #                   				#
                     ####################################
nb ?= 50
T ?= sample
VAL ?= no
REQUEST = 'read -p "Enter a commit message:" pwd; echo $$pwd'
COMMIT_MESSAGE ?= $(shell bash -c $(REQUEST))

                     ####################################
                     #                   				#
                     #              OBJS	   			#
                     #                   				#
                     ####################################
BUILD_DIR = objs/

OBJS = $(patsubst %, $(BUILD_DIR)%.o, $(SRCS))

                     ####################################
                     #                   				#
                     #       	   RULES      			#
                     #                   				#
                     ####################################
all: $(NAME)
	echo "\n$(CYAN)MAKE COMPLETE$(END)"

fast:
	$(MAKE) re -j8

$(NAME): $(OBJS) $(LIB_PATH)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB_PATH) $(INCLUDES)

$(OBJS): $(BUILD_DIR)%.o: %.c $(HEAD) Makefile
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	echo "$(CFLAGS) \t\t $(GREEN)$<$(END)"

$(LIB_PATH): FORCE
	make -C $(LIB_DIR)

unit_test:
	@echo "\n | Unitest |"
	./unit_test.sh

run:
	$(MAKE) unit_test

clean:
	rm -f $(OBJS)
	rm -rf ./$(BUILD_DIR)
	echo "$(YELLOW)OBJS$(END) \t\t were \t\t $(GREEN)clean$(END)\n"
	$(MAKE) clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	echo "$(YELLOW)$(NAME)$(END) \t\t was \t\t $(GREEN)clean$(END)\n"
	$(MAKE) fclean -C $(LIB_DIR)

re: fclean
	$(MAKE)

FORCE:

.PHONY: clean fclean all re t FORCE git
.SILENT: $(NAME) $(OBJS) $(BUILD_DIR) $(MAIN_OBJ_PS) $(MAIN_OBJ_C) all re t \
			$(LIB_PATH) $(NAME_PUSH_SWP) $(NAME_CHECKER) clean fclean run

                     ####################################
                     #                   				#
                     #        		GIT       			#
                     #                   				#
                     ####################################
git:
	@git add -f -A
	@git commit -m "$(COMMIT_MESSAGE)"
	@git push

                     ####################################
                     #                   				#
                     #       		COLOR     			#
                     #                  				#
                     ####################################
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
END = \033[0m
