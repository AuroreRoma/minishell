NAME := prototype_shell

MAKEFLAGS := --no-print-directory

CC = gcc
FSAN := -fsanitize=address
CFLAGS := -Wall -Wextra -Werror $(FSAN) -g
IFLAGS := -I./incs -MMD -MP
LFLAGS := -lreadline

SRCS_DIR  := srcs
BUILD_DIR := build

SRCS := \
	main.c \
	lexer.c \
	parser.c \
	parser_handler.c

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

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $@ $(LFLAGS)
	@printf "\t$(PPL)$(NAME) created\n$(END)"

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "\t$(GRN)compiling [$(END)$(CYA)$(notdir $<)$(GRN)]$(END)\n"

.PHONY: all clean fclean re

all:	$(NAME)

clean:
	@if [ -d $(BUILD_DIR) ]; \
		then \
		printf "\t$(YLW)$(BUILD_DIR) successfully deleted\n$(END)"; \
		rm -r $(BUILD_DIR); \
		fi;

fclean:	clean
	@if [ -e $(NAME) ]; \
		then \
		printf "\t$(YLW)$(NAME) successfully deleted\n$(END)"; \
		rm $(NAME); \
		fi;

re:		fclean
	@$(MAKE) $(NAME)

-include $(DEPS)
