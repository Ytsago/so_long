CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lbsd -lX11 -lm -lXext
CC = cc
AR = ar
ARFLAG = -rcs
MAKE := $(MAKE) -j

GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RED    = \033[31m
RESET  = \033[0m

FILE =	main.c	check_map.c	map_parsing.c		pathing.c	drawing.c		input.c	setting.c 			\
		event.c	loading.c	setting_change.c	

BFILE =	main_bonus.c check_map_bonus.c map_parsing_bonus.c pathing_bonus.c drawing_bonus.c input_bonus.c setting_bonus.c set_data_bonus.c camera_bonus.c movement_bonus.c\
		event_bonus.c loading_bonus.c setting_change_bonus.c game_loop_bonus.c color_util_bonus.c enemy_bonus.c collision_bonus.c animation_bonus.c utils_bonus.c

LIB_D = libft/

MLX_D = minilibx-linux/

LIB = $(LIB_D)libft.a $(MLX_D)libmlx.a $(MLX_D)libmlx_Linux.a

BDIR = bonus/

SRCDIR = src/

SRCS = $(SRCDIR)$(FILE)

BSRCS = $(BDIR)$(BFILE)

INCDIR = inc/

INC = so_long.h 

BINC = so_long_bonus.h


OBJDIR = .Obj/

OBJS = $(FILE:%.c=$(OBJDIR)%.o)

BOBJS = $(BFILE:%.c=$(OBJDIR)%.o)

NAME = so_long

BNAME = so_long_bonus

all: lib $(NAME) Makefile

$(NAME): $(OBJS)
	@echo "$(YELLOW)Creating final product : $(BLUE)$@...$(RESET)"
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(LIB) -o $@ && echo "$(GREEN)$@ Created successfully !$(RESET)"

$(BNAME): $(BOBJS)
	@echo "$(YELLOW)Creating final product : $(BLUE)$@...$(RESET)"
	@$(CC) $(CFLAGS) $(LFLAGS) $(BOBJS) $(LIB) -o $@ && echo "$(GREEN)$@ Created successfully !$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c $(LIB) $(INCDIR)$(INC) | $(OBJDIR)
	$(CC) -c $(CFLAGS) -I $(INCDIR) -I $(MLX_D) -I $(LIB_D)$(INCDIR) $< -o $@

$(OBJDIR)%.o: $(BDIR)%.c $(LIB) $(INCDIR)$(BINC) | $(OBJDIR)
	$(CC) -c $(CFLAGS) -I $(INCDIR) -I $(MLX_D) -I $(LIB_D)$(INCDIR) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling...$(RESET)"

lib:
	@$(MAKE) -C $(LIB_D) --no-print-directory MAKEOVERRIDEN=
	@$(MAKE) -C $(MLX_D) --no-print-directory MAKEOVERRIDEN=

bonus: lib $(BNAME) Makefile
	
clean:
	@echo "$(RED)Deleting object files...$(RESET)"
	@rm -rf $(OBJDIR) && echo "$(GREEN)Done !$(RESET)"
	@$(MAKE) $@ -C $(LIB_D) --no-print-directory
	@$(MAKE) $@ -C $(MLX_D) --no-print-directory
	
fclean: clean
	@echo "$(RED)Deleting executable or library $(NAME)...$(RESET)"
	@rm -f $(NAME) && echo "$(GREEN)Done !$(RESET)"
	@rm -f $(BNAME) && echo "$(GREEN)Done !$(RESET)"
	@$(MAKE) $@ -C $(LIB_D) --no-print-directory
	
re: fclean all

FORCE:

.PHONY: clean fclean re all bonus lib