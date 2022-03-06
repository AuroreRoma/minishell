NAME := minishell

MAKEFLAGS := --no-print-directory

CC = gcc
FSAN := -fsanitize=address
CFLAGS := -Wall -Wextra -Werror $(FSAN) -g
IFLAGS := -I./incs -MMD -MP
LFLAGS := -lreadline libft/libft.a
LIBFT := libft/libft.a

SRCS_DIR  := srcs
BUILD_DIR := build

SRCS := \
	main.c \
	env/parse_env.c \
	env/env_to_str.c \
	env/destroy_env.c \
	env/expand_var.c \
	executor/executor.c \
	lexer/lexer.c \
	lexer/lexer_utils.c \
	lexer/tokens.c \
	lexer/check_error.c \
	parser/handle_quote.c \
	parser/handle_redirection.c \
	parser/parser.c \
	parser/parser_handler.c \
	signals/signals.c \
	utils/cmd_utils.c \
	utils/cmd_utils_2.c \
	utils/str_insert.c \
	utils/gnl.c

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

$(NAME):	$(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS)
	@printf "\t$(PPL)$(NAME) created\n$(END)"

$(LIBFT):
	@$(MAKE) -C libft all
	@printf "\t$(PPL)libft.a compiled\n$(END)"

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
	@$(MAKE) -C libft fclean
	@$(MAKE) $(NAME)

-include $(DEPS)
