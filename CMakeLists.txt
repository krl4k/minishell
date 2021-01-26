cmake_minimum_required(VERSION 3.17)
project(minishell1 C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(srcs/libft)

add_executable(minishell1
        tests/test_signals.c tester1.c)
