# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pblagoje <pblagoje@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 14:39:35 by pblagoje          #+#    #+#              #
#    Updated: 2022/03/06 13:23:12 by pblagoje         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= $(addprefix ft_, strtoll.c memset.c bzero.c memcpy.c memccpy.c memmove.c memchr.c memcmp.c strlen.c isalpha.c isdigit.c isalnum.c isascii.c isprint.c toupper.c tolower.c strchr.c strrchr.c strcmp.c strncmp.c strlcpy.c strlcat.c strnstr.c atoi.c calloc.c strdup.c substr.c strjoin.c strtrim.c split.c itoa.c strmapi.c putchar_fd.c putstr_fd.c putendl_fd.c putnbr_fd.c)

SRCS_B	= $(addprefix ft_, lstnew.c lstadd_front.c lstsize.c lstlast.c lstadd_back.c lstdelone.c lstclear.c lstiter.c)

OBJS	= $(SRCS:.c=.o)

OBJS_B	= $(SRCS_B:.c=.o)

CC		= gcc

AR		= ar rcs

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

%.o: %.c
			@$(CC) $(CFLAGS) -c $< -o $@

bonus:		all $(OBJS_B)
			$(AR) $(NAME) $(OBJS_B)

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(AR) $@ $^

clean:
			@$(RM) $(OBJS) $(OBJS_B)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
