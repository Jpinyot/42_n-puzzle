# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 10:17:31 by jpinyot           #+#    #+#              #
#    Updated: 2020/10/01 09:48:03 by jpinyot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

# set the project name
project(n-puzzle)

# for YCM vim
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set definitions
#add_definitions(-O2)

# add the executable
# DSLR
add_executable(n-puzzle
			srcs/main.cpp
			srcs/state.cpp
			srcs/stateManhattanDistance.cpp
			srcs/closedStack.cpp
			srcs/openStack.cpp
			)

target_include_directories(n-puzzle PRIVATE 
			"${CMAKE_SOURCE_DIR}/includes"
			)

set(HEADER_FILES	
			includes/closedStack.h
			includes/state.h
			includes/nodes.h
			includes/stateManhattanDistance.h
			includes/openStack.h
			)
