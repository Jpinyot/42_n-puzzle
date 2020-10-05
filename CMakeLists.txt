# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 10:17:31 by jpinyot           #+#    #+#              #
#    Updated: 2020/10/05 11:22:33 by jpinyot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

# set the project name
project(n-puzzle)

#For Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH ~/.brew/Cellar/qt/5.15.1/lib/cmake/)

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
			srcs/inputParser.cpp
			srcs/ui/puzzleWidget.cpp
			)

target_include_directories(n-puzzle PRIVATE 
			"${CMAKE_SOURCE_DIR}/includes"
			"${CMAKE_SOURCE_DIR}/includes"
			)

set(HEADER_FILES	
			includes/closedStack.h
			includes/state.h
			includes/nodes.h
			includes/stateManhattanDistance.h
			includes/openStack.h
			includes/inputParser.h
			includes/ui/puzzleWidget.h
			)

find_package(Qt5Core CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

find_package(Qt5 COMPONENTS Widgets REQIRED)
target_link_libraries(n-puzzle Qt5::Widgets)
