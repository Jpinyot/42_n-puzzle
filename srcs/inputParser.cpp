/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:44 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 12:43:52 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> /* ifstream */
#include <sstream> /* geline */
#include <iostream> /* cout */
/* #include <string> */
#include "inputParser.h"

void		InputParser::parseLine(const string& line)
{
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == k_commentChar) {
			break ;
		}
		/* if (size_ == -1) { */
		/* 	size_ = stoi(line); */
		/* 	/1* sizeLine = true; *1/ */
		/* } */
	}
}

void		InputParser::parseLine(const string& line)
{
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == k_commentChar) {
			break ;
		}
		else if (isDigit(line[i])) {
			size_ = satoi();
		}
	}
}

void	InputParser::puzzleFromFile(const char* fileName)
{
	ifstream infile(fileName);
	string line;

	/* if (fileName. */
	while (getline(infile, line)) {
		if (size_ == k_invalidSize) {
			parseSize(line);
		}
		parseLine(line);
		cout << line << '\n';
	}
}
