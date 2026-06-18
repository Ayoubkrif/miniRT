# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aykrifa <aykrifa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 20:52:04 by aykrifa           #+#    #+#              #
#    Updated: 2026/06/12 17:24:22 by aykrifa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -O3  -ffast-math -march=native -pipe
#-Wconversion -Wsign-conversion -Wfloat-conversion
INCLUDES	= -Iincludes -I$(MLX) -I$(LIBFT)

SRC_PATH	= srcs
OBJ_PATH	= objs

SRC_DIRS	= math init print key_hook mlx intersection keyhook bump_texture utils
SRC_DIRS_PATHS = $(addprefix $(SRC_PATH)/,$(SRC_DIRS))

LIBFT		= libft
MLX			= minilibx-linux

SOURCES		= main.c \
			  init/check_arguments.c \
			  init/fill_scene.c \
			  init/error.c \
			  init/constructors.c \
			  init/constructors_bonus.c \
			  init/constructors_utils.c \
			  init/constructors_base.c \
			  init/solids_set.c \
			  mlx/put_pixel.c \
			  keyhook/hook.c \
			  keyhook/hook_cam.c \
			  keyhook/hook_co.c \
			  keyhook/hook_cy.c \
			  keyhook/hook_pl.c \
			  keyhook/hook_sp.c \
			  math/math_utils.c \
			  math/vect.c math/vect2.c math/vect3.c math/vect4.c \
			  intersection/intersection.c \
			  intersection/intersection2.c \
			  intersection/ray_casting.c\
			  intersection/blinn-phong.c \
			  intersection/cast_ray_from.c \
			  print/put_string.c print/ftoa.c print/obj_print.c \
			  utils/set_cam_base.c \
			  utils/utils.c utils/utils_rt.c \
			  utils/colors_utils.c \
			  mlx/exit_minirt.c \
			  mlx/screenshot.c \
			  bump_texture/bump_normal.c \
			  bump_texture/bump_texture.c \
			  bump_texture/u_v_map.c \
			  bump_texture/u_v_map2.c \


SRCS		= $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS		= $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))
DEPS		= $(addprefix $(OBJ_PATH)/,$(OBJS:.o=.d))

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

all:
	@if ! $(MAKE) _build; then \
		printf "$(YELLOW)$(BOLD)Native build failed. Fallback sur Docker? [y/N] $(NOC)"; \
		read ans </dev/tty; \
		if [ "$$ans" = "y" ] || [ "$$ans" = "Y" ]; then \
			$(MAKE) docker-build && $(MAKE) docker-make; \
		else \
			printf "$(RED)Build annulé.$(NOC)\n"; \
			exit 1; \
		fi; \
	fi

_build: tmp lib $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -L $(LIBFT) -L $(MLX) -o $@ $(OBJS) -lft -lmlx -lXext -lX11 -lm $(INCLUDES)

-include $(DEPS)

clean:
	@echo "$(RED)Cleaning object files...$(NOC)"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "$(RED)Cleaning binary...$(NOC)"
	@rm -f $(NAME)
	@rm -rf $(MLX)
	@make fclean -C $(LIBFT)
	@rm -f fsanitize
	@docker rmi $(DOCKER_IMAGE) 2>/dev/null || true

re: fclean all

mlx: $(MLX)
	@make -C $(MLX)

$(MLX):
	@git clone https://github.com/42Paris/minilibx-linux.git $(MLX)
	@git -C $(MLX) checkout 6e7e6ef

lib: mlx
	@make -C $(LIBFT)

tmp:
	@mkdir -p $(OBJ_PATH)
	@$(foreach dir, $(SRC_DIRS), mkdir -p $(OBJ_PATH)/$(dir);)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ $(INCLUDES)
	@echo "$(BLUE)Compiling $(WHITE)$(notdir $<)$(BLUE) → $(WHITE)$(notdir $@) $(RED)[OK]$(NOC)"

bear:
	bear -- make re

DOCKER_IMAGE	= minirt

docker-build:
	docker build -t $(DOCKER_IMAGE) .

docker-run:
	docker run -it --rm -v $(PWD):/app $(DOCKER_IMAGE)

docker-make:
	docker run --rm -v $(PWD):/app $(DOCKER_IMAGE) make

.PHONY: all _build fsanitize clean fclean re docker-build docker-run docker-make

# fsanitize: tmp $(OBJS)
# 	@$(CC) $(CFLAGS) -o $@ $(OBJS) -lpthread -g3 -fsanitize=thread
# 	@echo "$(GREEN)Project compiled with ThreadSanitizer$(NOC)"

