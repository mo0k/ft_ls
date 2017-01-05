# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <jmoucade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by jmoucade          #+#    #+#              #
#    Updated: 2016/12/11 23:35:20 by jmoucade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INC_PATH = includes

SRC_PATH = sources

SRC =	$(SRC_PATH)/ft_ls.c				\
		$(SRC_PATH)/input.c				\
		$(SRC_PATH)/options.c			\
		$(SRC_PATH)/lst.c				\
		$(SRC_PATH)/lst_utils.c			\
		$(SRC_PATH)/filestat.c			\
		$(SRC_PATH)/browse.c 			\
		$(SRC_PATH)/recurs.c 			\
		$(SRC_PATH)/time.c				\
		$(SRC_PATH)/sort.c				\
		$(SRC_PATH)/merge.c				\
		$(SRC_PATH)/padding.c			\
		$(SRC_PATH)/padding_utils.c		\
		$(SRC_PATH)/print.c				\
		$(SRC_PATH)/print_stream.c		\
		$(SRC_PATH)/print_longform.c	\
		$(SRC_PATH)/print_singleform.c	\
		$(SRC_PATH)/longform.c			\
		$(SRC_PATH)/colors.c			\

OSRC = $(SRC:.c=.o)

LIB_PATH = libft
LIB = libft/libft.a

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m

all: $(NAME)

$(NAME): $(LIB) $(OSRC)
	@echo "Compiling..."
	@$(CC) $(CFLAGS) $(OSRC) -o $@ -L $(LIB_PATH) -lft
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

$(LIB):
	@echo "Compiling libft..."
	@make -C $(LIB_PATH)
	@echo "Librairy compiled."

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_PATH)/$(INC_PATH) -I $(INC_PATH) -c -o $@ $?
	@echo "Linking file $@"

clean:
	@make clean -C $(LIB_PATH)
	@/bin/rm -f $(OSRC)
	@echo "Cleaning temporary files."

fclean: clean
	@make fclean -C $(LIB_PATH)
	@/bin/rm -f $(NAME)
	@echo "Delete $(NAME) file."

re: fclean all
