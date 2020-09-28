/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:14:12 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/28 15:43:56 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>			//vector 
#include <list>
#include <unistd.h>			//write
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

		virtual void	setScoreFromPrev() = 0;
        virtual void    setScore() = 0;
        void    setPuzzleFromPrev(); //sets itPos_ and puzzle_ TODO: better naming :P

	protected:
		int	moveCount_;
        Moves   move_;
		int         score_;
		vector<char>	puzzle_;
		char	    itPos_;

	public:
		State(State* previous, const Moves& move):
			previous_(previous), next_(NULL), moveCount_(previous->getMoveCount() + 1), move_(move), score_(-1), puzzle_(NULL), itPos_(0)
	    {
            setPuzzleFromPrev();
	    	setScoreFromPrev();

	    };

        State(const vector<char> puzzle, const Moves& move=none) :
            previous_(NULL), next_(NULL), moveCount_(0), move_(move), score_(-1), puzzle_(NULL), itPos_(0)
        {
            puzzle_ = puzzle;
            //itPos_ need to be initialized
            setScore();
        };

		const int	getMoveCount() {return moveCount_;}
		const int	getScore() {return score_;}
        vector<char> getPuzzle() {return puzzle_;}
        const int   getItPos() {return itPos_;}
        State*      getNext() {return next_;}
        void        setNext(State* next) {next_ = next;}
		
		const bool	isSolved() {return (score_ == 0);}
		/* void		betterScore(const State* currState); */

		const bool	canMoveTo(const Moves& move);

};

list<int, vector<State*> > visited;
