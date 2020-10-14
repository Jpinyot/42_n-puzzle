/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:14:12 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/14 15:27:57 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>			//vector 
#include <list>
#include <unistd.h>			//write
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int k_size = 3;
const unsigned char k_itValue = 4;

enum Heuristic {
	mandist,
	linconf,
	unicost,
};

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
	static int statesCreated_;
	static int currentStatesActive_;
	static int maxStatesActive_;

	private:
		State*	previous_;
        State*      next_;

	virtual void	setHeuristicScoreFromPrev() = 0;
        virtual void    setHeuristicScore() = 0; //seetse itPos_ and score__ TODO: better namingggg

	protected:
		int	moveCount_;
        	Moves   move_;
		int         heuristicScore_;
		vector<unsigned char>	puzzle_;
		unsigned char	    itPos_;

        void    setPuzzleFromPrev(); //sets itPos_ and puzzle_ TODO: better naming :P

	public:
		State(State* previous, const Moves& move):
			previous_(previous), next_(NULL), moveCount_(previous->getMoveCount() + 1),
			move_(move), heuristicScore_(previous_->heuristicScore_), puzzle_(0), itPos_(0)
	    {
			++statesCreated_;
			++currentStatesActive_;
			if (currentStatesActive_ > maxStatesActive_) {
				maxStatesActive_ = currentStatesActive_;
			}
            	/* setPuzzleFromPrev(); */
	    	/* setHeuristicScoreFromPrev(); */

	    };

        State(const vector<unsigned char> puzzle, const Moves& move=none) :
            previous_(NULL), next_(NULL), moveCount_(0), move_(move), heuristicScore_(-1), puzzle_(puzzle), itPos_(0)
        {
			++statesCreated_;
			++currentStatesActive_;
			if (currentStatesActive_ > maxStatesActive_) {
				maxStatesActive_ = currentStatesActive_;
			}
        };

		virtual ~State()
		{
			--currentStatesActive_;
		}

	const int	getMoveCount() const {return moveCount_;}
	const int	getScore() const {return heuristicScore_ + moveCount_;}
	const int	getHeuristicScore() const {return heuristicScore_;}
        const vector<unsigned char> getPuzzle() const {return puzzle_;}
        const int   getItPos() const {return itPos_;}
        State*      getNext() const {return next_;}
        void        setNext(State* next) {next_ = next;}
        State*    getPrevious() const {return previous_;}
		static int getStatesCreated() {return statesCreated_;}
		static int getMaxStatesActive() {return maxStatesActive_;}
		
	const bool	isSolved() const {return (heuristicScore_ == 0);}
	const bool	isSolvable() const;

	const bool	canMoveTo(const Moves& move) const;
	void		display() const;
	void		displaySteps(const bool disp=false, const bool isFirst=true) const;
        virtual const int       singleTileDistance(int tile) const = 0;
		virtual State	*moveTo(Moves &move) {return NULL;}
		virtual const bool isSolution() const {return getHeuristicScore() == 0;}

};
