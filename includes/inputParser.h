/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:46:13 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/28 13:03:13 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"
#include <vector>
#include <math.h>

const char k_commentChar = '#';
const int k_invalidSize = 0;
const int k_minSize = 3;
const int k_maxSize = 16;
const int k_minValue = 0;

using namespace std;

enum InputErrors
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
		InputErrors		errors_;
		unsigned char		size_;
		unsigned char		maxValidTile_;
		vector<bool>		tileChecker_;

		void		setTileChecker();
		const bool	tileIsValid(const unsigned char& tile) const {return (tile < maxValidTile_ && !tileChecker_[tile]);}
		void		setTileAsChecked(const unsigned char& pos) {tileChecker_.at(pos) = true;}


		void		puzzleFromFile(const char* string);
		InputErrors	parseLine(const string& line);
		InputErrors	parseSize(const string& line);
		bool		errorsInFormat(const string& line, int pos);
		bool		sizeIsValid() {return (size_ >= k_minSize && size_ <= k_maxSize);};
	public :
		InputParser(const char* string) :
			puzzle_(0), errors_(noFile), size_(k_invalidSize), maxValidTile_(k_invalidSize), tileChecker_(0)
		{
			puzzleFromFile(string);
		};
		~InputParser() {};

		vector<unsigned char>	getTranslatedPuzzle() const;
		vector<unsigned char>	getPuzzle() const {return puzzle_;};
		static vector<unsigned char>	translatePuzzleBack(const vector<unsigned char>& puzzlei, const unsigned char& size);
		const InputErrors	getErrors() const {return errors_;}
		const char		getSize() const {return size_;}
};
