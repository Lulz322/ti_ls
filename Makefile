NAME := ft_ls
NPWD := $(CURDIR)/$(NAME)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ECHO := echo -e
endif
ifeq ($(UNAME_S),Darwin)
	ECHO := echo
endif

#-march=native -mtune=native -flto -Ofast
CC := gcc -g3
CFLAGS := -Wall -Wextra -Werror
IFLAGS := -I $(CURDIR)/includes/

SRC := $(abspath $(wildcard srcs/*.c))
SRC += $(abspath $(wildcard srcs/*/*.c))
OBJ := $(SRC:.c=.o)

LIBFT := $(CURDIR)/libft/libft.a
LMAKE := make -C libft

WHITE := \033[0m
BGREEN := \033[42m
GREEN := \033[32m
RED := \033[31m
INVERT := \033[7m

SUCCESS = [$(GREEN)✓$(WHITE)]

DEL := rm -rf

all: $(NAME)

$(OBJ): %.o: %.c
	@$(ECHO) -n ' $@: '
	@$(CC) -c $(CFLAGS) $(LIBSINC) $(IFLAGS) $< -o $@
	@$(ECHO) "$(SUCCESS)"

$(LIBFT):
	@$(LMAKE)

$(NAME): $(LIBFT) $(OBJ)
	@$(ECHO) -n '$(NPWD): '
	@$(CC) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)
	@$(ECHO) "[$(INVERT)$(GREEN)✓$(WHITE)]"

del:
	@$(DEL) $(OBJ)

clean:
	@$(DEL) $(OBJ)
	@$(LMAKE) clean

fclean: clean
	@$(LMAKE) fclean
	@$(DEL) $(NAME)
	@$(ECHO) "$(INVERT)$(RED)deleted$(WHITE)$(INVERT): $(NPWD)$(WHITE)"

re: fclean all

.PHONY: all fclean clean re
