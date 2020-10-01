/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:44 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 16:24:11 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> /* ifstream */
#include <sstream> /* geline */
#include <iostream> /* cout */
#include <string>
#include "inputParser.h"

const string k_validChar = "0123456789";

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

bool		InputParser::errorsInFormat(const string& line, int pos)
{
	if (pos != string::npos) {
		while (++pos < line.size()) {
			if (line.at(pos) == k_commentChar) {
				return (noError);
			}
			else if (line.at(pos) != ' ' && line.at(pos) != '\t') {
				return (badFormat);
			}
		}
	}
	return (noError);
}

InputErros	InputParser::parseSize(const string& line)
{
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == k_commentChar) {
			return (noError);
		}
		else if (line.at(i) != ' ' && line.at(i) != '\t') {
			size_ = stoi(line);
			if (!sizeIsValid()) {
				return (invalidSize);
			}
			else if (errorsInFormat(line, line.substr(i)
						.find_last_not_of(k_validChar) + i)) {
				return (badFormat);
			}
			else {
				return (noError);
			}
		}
	}
	return (noError);
}

void	InputParser::puzzleFromFile(const char* fileName)
{
	ifstream infile(fileName);
	string line;

	/* if (fileName. */
	while (getline(infile, line)) {
		if (size_ == k_invalidSize) {
			
			if ((errors_ = parseSize(line)) != noError) {
				break ;
				cout << "ERROR PARSING SIZE";
			}
		}
		parseLine(line);
	}
}
