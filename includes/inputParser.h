/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:46:13 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/02 10:08:51 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma one
#include <vector>

const char k_commentChar = '#';
const int k_invalidSize = 0;
const int k_minSize = 3;
const int k_maxSize = 5;
const int k_minValue = 0;

/* const char k_translateThree[9]{1,2,3,8,0,4,7,6,5}; */
const char k_translateThree[9]{4,0,1,2,5,8,7,6,3};
/* const char k_translateFour[16]{1,2,3,4,12,13,14,5,11,0,15,6,10,8,8,7}; */
const char k_translateFour[16]{9,0,1,2,3,7,11,15,14,13,12,8,4,5,6,10};
const char k_translateFive[25]{12,0,1,2,3,4,9,14,19,24,23,22,21,20,15,10,5,6,7,8,13,18,17,16,11};

using namespace std;

enum InputErros
{
	badFormat = 00001,
	noFile = 00010,
	invalidSize = 00100,
	noError = 0
};

class InputParser
{
	private:
		vector<unsigned char>	puzzle_;
		/* vector<vector<unsigned char> >	vect; */
		InputErros		errors_;
		unsigned char		size_;
		unsigned char		maxValidTile_;
		vector<bool>		tileChecker_;

		void		setTileChecker();
		/* const bool	tileExist(const &unsigned char pos) const {return (tileChecker_[pos]);} */
		const bool	tileIsValid(const unsigned char& tile) const {return (tile < maxValidTile_ && !tileChecker_[tile]);}
		void		setTileAsChecket(const unsigned char& pos) {tileChecker_.at(pos) = true;}


		/* const bool fileIsValid( */
		void		puzzleFromFile(const char* string);
		InputErros	parseLine(const string& line);
		InputErros	parseSize(const string& line);
		bool		errorsInFormat(const string& line, int pos);
		bool		sizeIsValid() {return (size_ >= k_minSize && size_ <= k_maxSize);};
	public :
		/* InputParser(const char* string): */
		/* 	puzzle_(0) */
		/* { */
		/* }; */
		InputParser(const char* string) : /* File descriptor */
		/* InputParser(const char* string, const int& size) : /1* File descriptor *1/ */
			puzzle_(0), errors_(noFile), size_(k_invalidSize), maxValidTile_(k_invalidSize), tileChecker_(0)
		{
			puzzleFromFile(string);
		};

		const vector<unsigned char>	getPuzzle() const;
		/* vector<unsigned char>	getPuzzle() {return vector<unsigned char>(puzzle_);} */
		const InputErros	getErrors() const {return errors_;}
		const char		getSize() const {return size_;}
};
