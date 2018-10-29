# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 12:22:35 by barbara           #+#    #+#              #
#    Updated: 2018/10/29 20:09:28 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CFLAGS = -Wall -Wextra -Werror -Weverything -g

SRC = main.c\
	  parsing.c\
	  pars_file.c\
	  list_files.c\
	  display.c\
	  free_data.c\
	  def_padding.c\
	  error.c\
	  get_files.c\
	  rights.c\
	  display_col.c\
	  sort_time.c\
	  sort_size.c

OBJ = $(addprefix obj/, $(SRC:.c=.o))

LIBFT = libft/libft.a

all : $(NAME)

lib :
	@make -C libft

obj :
	@mkdir obj

obj/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@ -I libft/includes -I includes

$(NAME) : lib obj $(LIBFT) $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LIBFT)

clean : clean_libft
	rm -f $(OBJ)

clean_libft :
	@make -C libft clean

fclean_libft : clean_libft
	@rm -f $(LIBFT)

fclean : clean fclean_libft
	@rm -f $(NAME)
	@echo "exe deleted"

re : fclean all
	
.PHONY : all lib clean clean_libft fclean_libft fclean re