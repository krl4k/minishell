NAME = minishell
#CC = /usr/bin/clang-10
CC = gcc
FLAGS = -Wall -Werror -Wextra -g

SRCS_DIR = ./srcs/
LIBFT_DIR   = $(SRCS_DIR)libft/
PARSER_DIR   = $(SRCS_DIR)parser/
COMMANDS_DIR   = $(SRCS_DIR)commands/

HEADERS = ./includes/

SRCS_ALL = $(addprefix $(SRCS_DIR), execute.c init_all.c main.c dynamic_array.c )#ADD ALL FILES IN ./srcs/
SRC_PARSER = $(addprefix $(PARSER_DIR), )#ADD ALL FILES IN ./srcs/parser/
SRC_COMMANDS = $(addprefix $(COMMANDS_DIR), error_handler.c bin_commands.c\
				ft_cd.c ft_env.c ft_echo.c ft_export.c ft_export_print_sort_env.c \
				ft_unset.c pipes2.c pipes_utils.c pipes_utils2.c signals_handler.c)#ADD ALL FILES IN ./srcs/parser/

OBJ_ALL = $(SRCS_ALL:.c=.o)
OBJ_PARSER = $(SRC_PARSER:.c=.o)
OBJ_COMMANDS = $(SRC_COMMANDS:.c=.o)

SRCS = $(SRCS_ALL) $(SRC_PARSER) $(SRC_COMMANDS)

OBJS = $(OBJ_ALL) $(OBJ_PARSER) $(OBJ_COMMANDS)

all:$(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(CFLAGS) -I$(HEADERS) $(OBJS) $(FLAGS) $(LIBFT_DIR)/libft.a -o $(NAME)
												#$(LIBFT_DIR)/
$(OBJ_PARSER): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@

$(OBJ_ALL): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(LIBFT_DIR) -c $< -o $@


$(OBJ_COMMANDS): %.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -I$(HEADERS) -I $(LIBFT_DIR) -c $< -o $@


%.o:%.c%$(HEADERS)
	$(CC) $(FLAGS) -o I$(HEADER)  $@ -c $<

clean:
	@rm -rf *.o
	@rm -f $(PARSER_DIR)/*.o
	@rm -f $(SRCS_DIR)/*.o
	@rm -f $(COMMANDS_DIR)/*.o
	@make -C $(LIBFT_DIR) clean
	@echo Objects files deleted!

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

start:
	./minishell

norme:
	norminette ./engine/*.c ./includes/libft.h includes/cub3d.h includes/parser.h \
	./mlx_helper/*.c parser/*.c libft/*.c libft/*.h

forbidden:
	cat ./engine/*.c ./includes/libft.h includes/cub3d.h includes/parser.h \
        	./mlx_helper/*.c parser/*.c libft/*.c libft/*.h | grep "printf"

re: fclean all

.PHONY: all objs clean fclean re
