/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateHamming.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 09:48:20 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/19 10:01:38 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateHamming : public State
{
    private:
        virtual void    setHeuristicScoreFromPrev();
        virtual void    setHeuristicScore();
    
    public:
        virtual const int       singleTileDistance(int i) const;
	StateHamming(State* previous, const Moves& move):
		State(previous, move)
	    {
		setPuzzleFromPrev();
	    	setHeuristicScoreFromPrev();

	    };

        StateHamming(const vector<unsigned char> puzzle, const Moves& move=none) :
		State(puzzle, move)
        {
            puzzle_ = puzzle;
            setHeuristicScore();
        };

        ~StateHamming() {;}

		State	*moveTo(Moves &move) {return new StateHamming(this, move);}
};
