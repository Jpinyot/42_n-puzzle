/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateManhattanDistance.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:12:43 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/01 10:26:21 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateManhattanDistance : public State
{
    private:
        virtual void    setHeuristicScoreFromPrev();
        virtual void    setHeuristicScore();
    
    public:
        virtual const int       singleTileDistance(int i) const;
	StateManhattanDistance(State* previous, const Moves& move):
		State(previous, move)
	    {
		setPuzzleFromPrev();
	    	setHeuristicScoreFromPrev();
    		/* display(); */

	    };

        StateManhattanDistance(const vector<unsigned char> puzzle, const Moves& move=none) :
		State(puzzle, move)
        {
            puzzle_ = puzzle;
            //itPos_ need to be initialized
            setHeuristicScore();
        };

};
