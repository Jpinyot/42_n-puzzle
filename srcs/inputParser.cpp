/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:44 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 18:31:30 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> /* ifstream */
#include <sstream> /* geline */
#include <iostream> /* cout */
#include <string>
#include "inputParser.h"

const string k_validChar = "0123456789";

static int	findLastDigit(const string& line, int i)
{
	while (i < line.size() && k_validChar.find(line[i]) != string::npos) {
		i++;
	}
	return (i);
}

void		InputParser::setTileChecker()
{
	maxValidTile_ = size_ * size_;
	tileChecker_ = vector<bool>(maxValidTile_, false);
}

InputErros	InputParser::parseLine(const string& line)
{
	int count = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line.at(i) == k_commentChar) {
			break ;
		}
		else if (line.at(i) != ' ' && line.at(i) != '\t') {
			int tile = stoi(line.substr(i));
			if (!tileIsValid(tile)) {
				return (badFormat);
			}
			setTileAsChecket(tile);
			puzzle_.emplace_back(tile);
			i = findLastDigit(line, i);
			count += 1;
		}
	}
	if (count == size_ || count == 0) {
		return (noError);
	}
	return (badFormat);
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
			else if (errorsInFormat(line, findLastDigit(line, i))) {
				return (badFormat);
			}
			else {
				setTileChecker();
				return (noError);
			}
		}
	}
	return (noError);
}

bool		InputParser::errorsInFormat(const string& line, int pos)
{
	if (pos != string::npos) {
		while (++pos < line.size()) {
			if (line.at(pos) == k_commentChar) {
				return (noError);
			}
			else if (line.at(pos) != ' ' && line.at(pos) != '\t') {
				/* cout << "<<" << line << ">>"; */
				return (badFormat);
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
				cout << "ERROR PARSING SIZE " << errors_;
				break ;
			}
		}
		else if ((errors_ = parseLine(line)) != noError) {
		/* cout << line; */
			cout << "<<ERROR PARSING LINE>>";
			break ;
		}
	}
	for (auto &tile : puzzle_) {
		cout << static_cast<int>(tile) << "-";
	}
	cout << '\n';
}
