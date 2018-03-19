# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcozic <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 18:10:54 by bcozic            #+#    #+#              #
#    Updated: 2018/02/01 10:13:08 by bcozic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

SRC = ft_abs.c\
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
	  get_next_line.c

SSRC = $(addprefix src/, $(SRC))

OBJ = $(SRC:.c=.o)

SOBJ = $(addprefix obj/, $(OBJ))

all : $(NAME)

obj :
	@mkdir obj

obj/%.o: src/%.c
	@gcc $(CFLAGS) -c $< -o $@ -I includes

$(NAME) : obj $(SOBJ)
	@ar rc $(NAME) $(SOBJ)
	@ranlib $(NAME)
	@echo "Compile OK"

clean :
	@rm -f $(SOBJ)
	@echo "Obj Deleted"

fclean : clean
	@rm -f $(NAME)
	@echo "Program Deleted"

re : fclean all

