cmake_minimum_required(VERSION 3.17)
project(minishell_myFork C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(srcs/libft)

add_executable(minishell_myFork
        includes/minishell.h
        srcs/libft/ft_atoi.c
        srcs/libft/ft_bzero.c
        srcs/libft/ft_calloc.c
        srcs/libft/ft_isalnum.c
        srcs/libft/ft_isalpha.c
        srcs/libft/ft_isascii.c
        srcs/libft/ft_isdigit.c
        srcs/libft/ft_isprint.c
        srcs/libft/ft_itoa.c
        srcs/libft/ft_lennbr.c
        srcs/libft/ft_lstadd_back.c
        srcs/libft/ft_lstadd_front.c
        srcs/libft/ft_lstclear.c
        srcs/libft/ft_lstdelone.c
        srcs/libft/ft_lstfree_cont.c
        srcs/libft/ft_lstiter.c
        srcs/libft/ft_lstlast.c
        srcs/libft/ft_lstmap.c
        srcs/libft/ft_lstnew.c
        srcs/libft/ft_lstsize.c
        srcs/libft/ft_memccpy.c
        srcs/libft/ft_memchr.c
        srcs/libft/ft_memcmp.c
        srcs/libft/ft_memcpy.c
        srcs/libft/ft_memmove.c
        srcs/libft/ft_memset.c
        srcs/libft/ft_putchar_fd.c
        srcs/libft/ft_putendl_fd.c
        srcs/libft/ft_putnbr_fd.c
        srcs/libft/ft_putstr_fd.c
        srcs/libft/ft_setsplit.c
        srcs/libft/ft_split.c
        srcs/libft/ft_strchr.c
        srcs/libft/ft_strcpy.c
        srcs/libft/ft_strjoin.c
        srcs/libft/ft_strlcat.c
        srcs/libft/ft_strlcpy.c
        srcs/libft/ft_strmapi.c
        srcs/libft/ft_strncmp.c
        srcs/libft/ft_strnstr.c
        srcs/libft/ft_strrchr.c
        srcs/libft/ft_strtrim.c
        srcs/libft/ft_substr.c
        srcs/libft/ft_tolower.c
        srcs/libft/ft_toupper.c
        srcs/libft/get_next_line.c
        srcs/libft/libft.h
        srcs/execute.c
        srcs/init_all.c
        srcs/main.c
        tests/execv_test.c
        tests/flags.c
        tests/start.c
        tests/test2.c
        tests/test_signals.c
        srcs/parser/ft_split_echo.c srcs/parser/parser_q.c)
