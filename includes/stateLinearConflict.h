/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateLinearConflict.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:23:42 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/03 19:15:18 by mfiguera         ###   ########.fr       */
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
};
