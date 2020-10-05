/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:44 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 09:22:49 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream> /* ifstream */
#include <sstream> /* geline */
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

InputErrors	InputParser::parseLine(const string& line)
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
			setTileAsChecked(tile);
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

InputErrors	InputParser::parseSize(const string& line)
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

	while (getline(infile, line)) {
		if (size_ == k_invalidSize) {
			if ((errors_ = parseSize(line)) != noError) {
				break ;
			}
		}
		else if ((errors_ = parseLine(line)) != noError) {
			break ;
		}
	}
	if (puzzle_.size() != size_) {
		errors_ = invalidSize;
	}
}

vector<unsigned char>	InputParser::getTranslatedPuzzle() const
{
	const char* translateStr;
	vector<unsigned char> retPuzzle(puzzle_.size());

	switch (size_)
	{
		case 3:
			translateStr = k_translateThree;
			break ;
		case 4:
			translateStr = k_translateFour;
			break ;
		case 5:
			translateStr = k_translateFive;
			break ;
		default:
			return (retPuzzle);
	}
	for(auto &tile : puzzle_) {
		retPuzzle.emplace_back(translateStr[tile]);
	}
	return (retPuzzle);
}

vector<unsigned char>	InputParser::translatePuzzleBack(const vector<unsigned char>& puzzle, const unsigned char& size) const
{
	if ( puzzle.size() != size * size) {
		return (vector<unsigned char>(0));
	}
	const char* translateStr;
	vector<unsigned char> retPuzzle(puzzle.size());

	switch (size)
	{
		case 3:
			translateStr = k_translateThree;
			break ;
		case 4:
			translateStr = k_translateFour;
			break ;
		case 5:
			translateStr = k_translateFive;
			break ;
		default:
			return (vector<unsigned char>(0));
	}
	for (auto &tile : puzzle) {
		retPuzzle[translateStr[tile]] = tile;
	}
	return (retPuzzle);
}
