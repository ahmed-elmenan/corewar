# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahel-men <ahel-men@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/08 00:20:23 by ahel-men          #+#    #+#              #
#    Updated: 2020/02/03 15:55:55 by ahel-men         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC	=	ft_afflst.c\
		ft_atoi.c \
		ft_bzero.c  \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlen.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_newtab.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_voidlst.c \
		ft_words_count.c \
		ft_lsterase.c\
		ft_atoi_base.c

CFLAGS	= -Wall -Wextra -Werror
NAME	= libft.a
OBJECT	=	$(SRC:.c=.o)
CC = gcc
HEADER	=	libft.h

all : $(NAME)

$(OBJECT): %.o: %.c $(HEADER)
	$(CC) -g -c $(CFLAGS) -o $@ $<

$(NAME): $(OBJECT) 
	ar rc $(NAME) $^
	@echo "\033[1;34m--> libft files were created\033[1;34m"

clean :
	@rm -f $(OBJECT)
	@echo "\033[1;34m--x libft object files were deleted\033[1;34m"
fclean : clean
	@rm -f $(NAME)
	@echo "\033[1;34m--x libft files were deleted\033[1;34m"
re : fclean all
