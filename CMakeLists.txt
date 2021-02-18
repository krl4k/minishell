cmake_minimum_required(VERSION 3.17)
project(minishell_myFork C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(srcs/libft
        srcs/parser
        srcs/commands
        srcs/)
file(GLOB SOURCE_LIBFT "srcs/libft/*c") #PARSE THE DIRECTORY AND TAKE ALL FILES
file(GLOB SOURCE_SRCS "srcs/*.c") #ПРОХОДИТ ПО ПАПКЕ СОБИРАЯ ВСЕ ФАИЛЫ
file(GLOB SOURCE_COMMANDS "srcs/commands/*.c") #ПРОХОДИТ ПО ПАПКЕ СОБИРАЯ ВСЕ ФАИЛЫ
file(GLOB SOURCE_PARSER "srcs/parser/*.c") #ПРОХОДИТ ПО ПАПКЕ СОБИРАЯ ВСЕ ФАИЛЫ


add_executable(minishell_myFork
        ${SOURCE_PARSER}
        ${SOURCE_LIBFT}
        ${SOURCE_COMMANDS}
        ${SOURCE_SRCS}
        srcs/commands/pipes_normal.c)
