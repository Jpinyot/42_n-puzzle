/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateShuffler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:26:40 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/05 10:56:14 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateSolution : public State
{
	private:
		void setHeuristicScoreFromPrev() {};

		virtual void    setHeuristicScore();
		vector<unsigned char> genPuzzle(int size);
		StateSolution *next_;

	public:
		const int singleTileDistance(int i) const {return -1;}
		StateSolution *getNext() const {return next_;}

		StateSolution(int size):
		State(genPuzzle(size), none)
		{
			setHeuristicScore();
		}

		StateSolution(StateSolution *previous, const Moves& move):
		State(previous, move)
		{
			setPuzzleFromPrev();
		}

		~StateSolution()
		{;}
};

class Shuffler{
	private:
		StateSolution	*solution_;
	
	public:
		Shuffler(int size):
		solution_(new StateSolution(size))
		{;}

		~Shuffler()
		{
			StateSolution *currState = solution_;
			StateSolution *nextState;
			while (currState) {
				nextState = currState->getNext();
				delete currState;
				currState = nextState;
			}
		}

		void shuffle(int n_moves);
		void display() const {solution_->display();}
		const vector<unsigned char> getPuzzle() const {return solution_->getPuzzle();}
};
