/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:14:12 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/28 11:54:46 by mfiguera         ###   ########.fr       */
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
	protected:
		int	moveCount_;
		State*	previous_;
        Moves   move_;
	private:
		int		score_;
		vector<char>	puzzle_;
		char		itPos_;

		void	setScoreFromPrev();
        void setPuzzleFromPrev(); //sets itPos_ and puzzle_ TODO: better naming :P

	public:
		State(State* previous, const Moves& move):
			previous_(previous), moveCount_(previous->getMoveCount() + 1), move_(move)
	{
        setPuzzleFromPrev();
		setScoreFromPrev();

	};
        State(const vector<char> puzzle, const Moves& move=none) :
            previous_(NULL), moveCount_(0), move_(move), next_(NULL)
        {
            puzzle_ = puzzle;
            //itPos_ need to be initialized
            setScore();
        };

		const int	getMoveCount() {return moveCount_;}
		const int	getScore() {return score_;}
        vector<char> getPuzzle() {return puzzle_;}
        const int   getItPos() {return itPos_;}
		
		const bool	isSolved() {return (score_ == 0);}
		/* void		betterScore(const State* currState); */

		const bool	canMoveTo(const Moves& move);

};

list<int, vector<State*> > visited;
