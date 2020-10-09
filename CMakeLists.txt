# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 10:17:31 by jpinyot           #+#    #+#              #
#    Updated: 2020/10/09 10:57:26 by mfiguera         ###   ########.fr        #
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
			srcs/stack.cpp
			srcs/stateLinearConflict.cpp
			srcs/shuffler.cpp
			srcs/inputParser.cpp
			srcs/algorithms.cpp
			srcs/argparse.cpp
			)

target_include_directories(n-puzzle PRIVATE 
			"${CMAKE_SOURCE_DIR}/includes"
			)

set(HEADER_FILES	
			includes/closedStack.h
			includes/state.h
			includes/nodes.h
			includes/stateManhattanDistance.h
			includes/stack.h
			includes/stateLinearConflict.h
			includes/shuffler.h
			includes/inputParser.h
			includes/algorithms.h
			includes/argparse.h
			)
