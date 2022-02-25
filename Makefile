NAME := minishell

MAKEFLAGS := --no-print-directory

CC = gcc
FSAN := -fsanitize=address
CFLAGS := -Wall -Wextra -Werror $(FSAN) -g
IFLAGS := -I./incs -MMD -MP
LFLAGS := -lreadline libft/libft.a

SRCS_DIR  := srcs
BUILD_DIR := build

SRCS := \
	main.c \
	env/parse_env.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/tokens.c \
	parser/handle_quote.c \
	parser/parser.c \
	parser/parser_handler.c \
	utils/cmd_utils.c \
	utils/cmd_utils_2.c \
	utils/str_insert.c \
	utils/ft_calloc.c \
	utils/ft_strlen.c \
	utils/ft_strcmp.c \
	utils/ft_substr.c \
	utils/ft_lstadd_back.c

_SRC =	$(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS =	$(patsubst $(SRCS_DIR)%.c, $(BUILD_DIR)/%.o, $(_SRC))
DEPS :=	$(OBJS:.o=.d)

BLK =	\e[30m
RED	=	\e[31m
GRN =	\e[32m
YLW =	\e[33m
BLU	=	\e[34m
PPL	=	\e[35m
CYA	=	\e[36m
END	=	\e[0m

$(NAME):	$(OBJS) libft
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS)
	@printf "\t$(PPL)$(NAME) created\n$(END)"

libft:
	@$(MAKE) -C libft all

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "\t$(GRN)compiling [$(END)$(CYA)$(notdir $<)$(GRN)]$(END)\n"

.PHONY: all clean fclean re

all:	$(NAME)

clean:
	@$(MAKE) -C libft clean
	@if [ -d $(BUILD_DIR) ]; \
		then \
		printf "\t$(YLW)$(BUILD_DIR) successfully deleted\n$(END)"; \
		rm -r $(BUILD_DIR); \
		fi;

fclean:	clean
	@$(MAKE) -C libft fclean
	@if [ -e $(NAME) ]; \
		then \
		printf "\t$(YLW)$(NAME) successfully deleted\n$(END)"; \
		rm $(NAME); \
		fi;

re:		fclean
	@$(MAKE) -C libft re
	@$(MAKE) $(NAME)

-include $(DEPS)
