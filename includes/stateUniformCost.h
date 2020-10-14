/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateUniformCost.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:02:16 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/14 11:59:56 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateUniformCost : public State
{
    private:
        virtual void    setHeuristicScoreFromPrev();
        virtual void    setHeuristicScore();
        int             actualHeuristicScore_;
    
    public:
        virtual const int       singleTileDistance(int i) const;

    	StateUniformCost(StateUniformCost* previous, const Moves& move):
        actualHeuristicScore_(previous->getActualHeuristicScore()),
		State(previous, move)
	    {
		    setPuzzleFromPrev();
	    	setHeuristicScoreFromPrev();
	    };

        StateUniformCost(const vector<unsigned char> puzzle, const Moves& move=none) :
        actualHeuristicScore_(0),
		State(puzzle, move)
        {
            puzzle_ = puzzle;
            setHeuristicScore();
        };

        ~StateUniformCost() {;}

		State	*moveTo(Moves &move) {return new StateUniformCost(this, move);}
        int     getActualHeuristicScore() const {return actualHeuristicScore_;}
};
