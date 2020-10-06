/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateLinearConflict.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:23:42 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/06 09:48:22 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateLinearConflict : public State
{
    private:
        virtual void    setHeuristicScoreFromPrev();
        virtual void    setHeuristicScore();
    
    public:
        virtual const int       singleTileDistance(int i) const;

    	StateLinearConflict(State* previous, const Moves& move):
		State(previous, move)
	    {
		    setPuzzleFromPrev();
	    	setHeuristicScoreFromPrev();
	    };

        StateLinearConflict(const vector<unsigned char> puzzle, const Moves& move=none) :
		State(puzzle, move)
        {
            puzzle_ = puzzle;
            setHeuristicScore();
        };

        ~StateLinearConflict() {;}

		State	*moveTo(Moves &move) {return new StateLinearConflict(this, move);}
};
