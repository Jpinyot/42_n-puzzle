/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateManhattanDistance.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:12:43 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/28 17:22:08 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

class StateManhattanDistance : public State
{
    private:
        virtual void    setScoreFromPrev();
        virtual void    setScore();
    
    public:
        virtual const int       singleTileDistance(int i);
	StateManhattanDistance(State* previous, const Moves& move):
		State(previous, move)
	    {
		setPuzzleFromPrev();
	    	setScoreFromPrev();

	    };

        StateManhattanDistance(const vector<char> puzzle, const Moves& move=none) :
		State(puzzle, move)
        {
            puzzle_ = puzzle;
            //itPos_ need to be initialized
            setScore();
        };

};
