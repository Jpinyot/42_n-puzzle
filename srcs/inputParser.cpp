/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:55:44 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/16 17:51:57 by mfiguera         ###   ########.fr       */
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

const vector<unsigned char> getTranslationStr(unsigned char size)
{
	enum Directions {R, D, L, U};
	vector<unsigned char> retStr(size*size);
	int i = 0, j = 0;
	int i_max = size - 1, j_max = size - 1;
	int i_min = 0, j_min = 1;
	int c = 1;
	int itPos = floor(size * size / 2) + (size - 1) % 2 * 1;

	Directions currMove = R;

	retStr[0] = itPos;

	while (!(i == itPos % size && j == itPos / size)) {
		retStr[c++] = j*size + i;
		switch (currMove)
		{
		case R:
			i++;
			if (i >= i_max) {
				currMove = D;
				i_max--;
			}
			break;
		case D:
			j++;
			if (j >= j_max) {
				currMove = L;
				j_max--;
			}
			break;
		case L:
			i--;
			if (i <= i_min) {
				currMove = U;
				i_min++;
			}
			break;
		case U:
			j--;
			if (j <= j_min) {
				currMove = R;
				j_min++;
			}
			break;
		}
	}

	return retStr;
}

vector<unsigned char>	inverse(vector<unsigned char>vec) {
	vector<unsigned char> ret(vec.size());
	for (int i; i < vec.size(); i++) {
		ret[vec[i]] = i;
	}
	return ret;
}

vector<unsigned char>	InputParser::getTranslatedPuzzle() const
{
	vector<unsigned char> translateStr = getTranslationStr(size_);
	vector<unsigned char> retPuzzle;

	for(auto &tile : puzzle_) {
		retPuzzle.emplace_back(translateStr[tile]);
	}
	return (retPuzzle);
}

vector<unsigned char>	InputParser::translatePuzzleBack(const vector<unsigned char>& puzzle, const unsigned char& size)
{
	if ( puzzle.size() != size * size) {
		return (vector<unsigned char>(0));
	}
	
	vector<unsigned char> translateStr = inverse(getTranslationStr(size));
	vector<unsigned char> retPuzzle(puzzle.size());

	for (int i = 0; i < puzzle.size(); i++) {
		retPuzzle[i] = translateStr[puzzle[i]];
	}
	return (retPuzzle);
}
