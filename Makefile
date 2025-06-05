# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 20:52:04 by aykrifa           #+#    #+#              #
#    Updated: 2025/06/05 15:20:51 by aykrifa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -Iincludes -I$(MLX) -I$(LIBFT)

SRC_PATH	= srcs
OBJ_PATH	= objs

SRC_DIRS	= 
SRC_DIRS_PATHS = $(addprefix $(SRC_PATH)/,$(SRC_DIRS))

LIBFT		= libft
MLX			= minilibx-linux

SOURCES		= main.c \
			  check_arguments.c fill_scene.c\
			  utils.c

SRCS		= $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS		= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

all: $(NAME)

$(NAME): tmp lib $(OBJS)
	@$(CC) $(CFLAGS) -L $(LIBFT) -L $(MLX) -o $@ $(OBJS) -lft -lmlx -lXext -lX11 -lm $(INCLUDES)
	@echo "$(GREEN)Project successfully compiled$(NOC)"

clean:
	@echo "$(RED)Cleaning object files...$(NOC)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)Cleaning binary...$(NOC)"
	@rm -f $(NAME)
	@rm -rf $(MLX)
	@make fclean -C $(LIBFT)
	@rm -f fsanitize

re: fclean all

mlx: $(MLX)
	@echo "$(GREEN)Compiling mlx ...$(CYAN)"
	@make -C $(MLX) -s
	@echo "$(GREEN)mlx compiled !$(CYAN)"

$(MLX):
	@echo "$(GREEN)Cloning mlx ...$(CYAN)"
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX)
	@echo "$(GREEN)Mlx cloned !$(CYAN)"

lib: mlx
	@echo "$(GREEN)Creating lib files...$(CYAN)"
	@make bonus -C $(LIBFT) -s
	@echo "$(GREEN)libft compiled !$(CYAN)"

tmp:
	@mkdir -p $(OBJ_PATH)
	@$(foreach dir, $(SRC_DIRS), mkdir -p $(OBJ_PATH)/$(dir);)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(BLUE)Compiling $(WHITE)$(notdir $<)$(BLUE) → $(WHITE)$(notdir $@) $(RED)[OK]$(NOC)"

bear:
	bear -- make re

.PHONY: all fsanitize clean fclean re

# fsanitize: tmp $(OBJS)
# 	@$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread -g3 -fsanitize=thread
# 	@echo "$(GREEN)Project compiled with ThreadSanitizer$(NOC)"

