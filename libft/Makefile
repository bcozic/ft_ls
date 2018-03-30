# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcozic <bcozic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 18:10:54 by bcozic            #+#    #+#              #
#    Updated: 2018/03/30 14:36:12 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -Weverything -g

SRC = ft_abs.c\
	  ft_nbrlen.c\
	  ft_isint.c\
	  ft_memset.c\
	  ft_bzero.c\
	  ft_memcpy.c\
	  ft_memccpy.c\
	  ft_memmove.c\
	  ft_memchr.c\
	  ft_memcmp.c\
	  ft_strlen.c\
	  ft_tab_strlen.c\
	  ft_strdup.c\
	  ft_strcpy.c\
	  ft_strncpy.c\
	  ft_strcat.c\
	  ft_strncat.c\
	  ft_strlcat.c\
	  ft_strchr.c\
	  ft_strrchr.c\
	  ft_strstr.c\
	  ft_strnstr.c\
	  ft_strcmp.c\
	  ft_strncmp.c\
	  ft_atoi.c\
	  ft_atoi_unsigned.c\
	  ft_isalpha.c\
	  ft_isdigit.c\
	  ft_issignnb.c\
	  ft_isalnum.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_isspace.c\
	  ft_isnum.c\
	  ft_toupper.c\
	  ft_tolower.c\
	  ft_isstr_f.c\
	  ft_isstr_forf.c\
	  ft_memalloc.c\
	  ft_memdel.c\
	  ft_strnew.c\
	  ft_strdel.c\
	  ft_strclr.c\
	  ft_striter.c\
	  ft_striteri.c\
	  ft_strmap.c\
	  ft_strmapi.c\
	  ft_strequ.c\
	  ft_strnequ.c\
	  ft_strsub.c\
	  ft_strjoin.c\
	  ft_strjoinflush.c\
	  ft_strnjoinflush.c\
	  ft_strtrim.c\
	  ft_strsplit.c\
	  ft_itoa.c\
	  ft_putchar.c\
	  ft_putstr.c\
	  ft_putendl.c\
	  ft_putnbr.c\
	  ft_putchar_fd.c\
	  ft_putstr_fd.c\
	  ft_putendl_fd.c\
	  ft_putnbr_fd.c\
	  ft_lstnew.c\
	  ft_lstdelone.c\
	  ft_lstdel.c\
	  ft_lstadd.c\
	  ft_lstiter.c\
	  ft_lstmap.c\
	  ft_lstlen.c\
	  ft_realloc.c\
	  ft_strup.c\
	  get_next_line.c

SRC_PRINTF = ft_printf.c\
			 chrflags.c\
			 add_arg.c\
			 apply_flag.c\
			 convert_nb.c\
			 flag_cara.c\
			 llitoa_base_mod.c\
			 ullitoa_base_mod.c\
			 unicode.c\

OBJ = $(addprefix obj/, $(SRC:.c=.o))

OBJ_PRINTF = $(addprefix ft_printf/obj/, $(SRC_PRINTF:.c=.o))

all : $(NAME)

obj :
	mkdir obj

ft_printf/obj :
	mkdir ft_printf/obj

ft_printf/obj/%.o: ft_printf/src/%.c
	gcc $(CFLAGS) -c $< -o $@ -I includes

obj/%.o: src/%.c
	gcc $(CFLAGS) -c $< -o $@ -I includes

$(NAME) : obj ft_printf/obj $(OBJ) $(OBJ_PRINTF)
	ar rc $(NAME) $(OBJ) $(OBJ_PRINTF)
	ranlib $(NAME)
	@echo "Compile OK"

clean :
	rm -f $(OBJ) $(OBJ_PRINTF)
	@echo "Obj Deleted"

fclean : clean
	rm -f $(NAME)
	@echo "Program Deleted"

re : fclean all

.PHONY : re all clean fclean