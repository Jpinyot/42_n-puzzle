/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:14:12 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 17:40:22 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>			//vector 
#include <list>
#include <unistd.h>			//write
#include <iostream>
using namespace std;

const int k_size = 3;
const char k_itValue = 4;

enum Moves
{
	N,
	E,
	S,
	W,
	none
};

class State
{
	private:
		State*	previous_;
        State*      next_;

	virtual void	setHeuristicScoreFromPrev() = 0;
        virtual void    setHeuristicScore() = 0; //seetse itPos_ and score__ TODO: better namingggg

	protected:
		int	moveCount_;
        	Moves   move_;
		int         heuristicScore_;
		vector<char>	puzzle_;
		char	    itPos_;

        void    setPuzzleFromPrev(); //sets itPos_ and puzzle_ TODO: better naming :P

	public:
		State(State* previous, const Moves& move):
			previous_(previous), next_(NULL), moveCount_(previous->getMoveCount() + 1),
			move_(move), heuristicScore_(-1), puzzle_(0), itPos_(0)
	    {
            	/* setPuzzleFromPrev(); */
	    	/* setHeuristicScoreFromPrev(); */

	    };

        State(const vector<char> puzzle, const Moves& move=none) :
            previous_(NULL), next_(NULL), moveCount_(0), move_(move), heuristicScore_(-1), puzzle_(0), itPos_(0)
        {
            puzzle_ = puzzle;
            //itPos_ need to be initialized
            /* setHeuristicScore(); */
        };

	const int	getMoveCount() {return moveCount_;}
	const int	getScore() {return heuristicScore_ + moveCount_;}
	const int	getHeuristicScore() {return heuristicScore_;}
        const vector<char> getPuzzle() {return puzzle_;}
        const int   getItPos() {return itPos_;}
        State*      getNext() {return next_;}
        void        setNext(State* next) {next_ = next;}
        State*    getPrevious() {return previous_;}
		
	const bool	isSolved() {return (heuristicScore_ == 0);}
	/* void		betterScore(const State* currState); */

	const bool	canMoveTo(const Moves& move);
		void		display();
        virtual const int       singleTileDistance(int tile) = 0;

};

/* list<int, vector<State*> > visited; */
