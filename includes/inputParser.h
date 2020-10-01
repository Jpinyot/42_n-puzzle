/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:46:13 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 16:08:48 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma one
#include <vector>

const char k_commentChar = '#';
const int k_invalidSize = -1;
const int k_minSize = 3;
const int k_maxSize = 12;
const int k_minValue = 0;

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
		char			size_;

		/* const bool fileIsValid( */
		void		puzzleFromFile(const char* string);
		void		parseLine(const string& line);
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
			puzzle_(0), errors_(noFile), size_(k_invalidSize)
		{
			puzzleFromFile(string);
		};

		vector<unsigned char>	getPuzzle() {return vector<unsigned char>(puzzle_);}
		const InputErros	getErrors() const {return errors_;}
		const char		getSize() const {return size_;}
};
