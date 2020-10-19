/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateHamming.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 09:48:13 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/19 10:03:57 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stateHamming.h"

const int StateHamming::singleTileDistance(int tile) const
{
	return (int)(puzzle_[tile] != tile);
};


void StateHamming::setHeuristicScoreFromPrev()
{
    State* previous = getPrevious();
    if (previous != NULL) {
        const int prevScore = previous->singleTileDistance(itPos_);
        const int currScore = singleTileDistance(previous->getItPos());
        heuristicScore_ += currScore - prevScore;
    }
};


void StateHamming::setHeuristicScore()
{
    int	h = 0;
	for (int i = 0; i < puzzle_.size(); i++) {
		if (puzzle_[i] != k_itValue){
            h += singleTileDistance(i);
		}
        else {
            itPos_ = i;
        }
	}
    heuristicScore_ = h;
};
