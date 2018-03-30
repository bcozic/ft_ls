# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 12:22:35 by barbara           #+#    #+#              #
#    Updated: 2018/03/30 19:50:03 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = #-Wall -Wextra -Werror -Weverything -g

SRC = main.c\
	  parsing.c\
	  pars_file.c\
	  list_files.c\
	  display.c\
	  free_data.c\
	  def_padding.c\
	  error.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

LIBFT = libft/libft.a

all : lib obj $(LIBFT) $(NAME)

lib :
	@make -C libft

obj :
	@mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@ -I libft/includes -I includes

$(NAME) : $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBFT)

clean :
	rm -f $(OBJ)

clean_libft :
	@make -C libft clean

clean_printf :
	@make -C ft_printf clean

fclean_libft : clean_libft
	@rm -f $(LIBFT)

fclean : clean
	@rm -f $(NAME)
	@echo "exe deleted"

re : fclean all
	
.PHONY : all lib clean clean_libft fclean_libft fclean re