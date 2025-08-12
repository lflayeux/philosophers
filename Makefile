CC = cc

CFLAGS = -Wall -Werror -Wextra -g3 

NAME = philo

SRC =	src/main.c \
		src/init.c \

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
RESET = \033[0m

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

build/pipex_modif/%.o: pipex_modif/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(SRC:.c=.o)
OBJ := $(OBJ:src/%=build/%)

$(OBJ_DIR)%.o : src/%/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Compilation successful ! ✅ $(RESET)"

all : $(NAME)

clean :
	@rm -rf build/
	@echo "$(YELLOW)All object files cleaned. 🧹$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Executable cleaned. 🧹$(RESET)"

re : fclean all

valg : re
	@valgrind --leak-check=full --show-leak-kinds=all \
	--suppressions=rl_leak.supp --trace-children=yes --track-fds=yes ./minishell

.PHONY: clean fclean re