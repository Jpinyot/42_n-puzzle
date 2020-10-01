/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputParser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 11:46:13 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 12:44:39 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma one
#include <vector>

const char k_commentChar = '#';
const int k_invalidSize = -1;

using namespace std;

enum InputErros
{
	badIdent = 00001,
	noFile = 00010,
	biggerSize = 00100,
	smallerSize = 01000,
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
		void		parseSize(const string& line);
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
