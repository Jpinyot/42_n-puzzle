/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateUniformCost.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 11:03:50 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/14 11:14:00 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stateUniformCost.h"

const int StateUniformCost::singleTileDistance(int tile) const
{
    int xAxis = abs(( puzzle_[tile] - ((puzzle_[tile] / k_size) * k_size)) - (tile -((tile / k_size) * k_size)));
	int	yAxis = abs(puzzle_[tile] / k_size - tile / k_size);
	return (xAxis + yAxis);
};


void StateUniformCost::setHeuristicScoreFromPrev()
{
    State* previous = getPrevious();
    if (previous != NULL) {
        const int prevScore = previous->singleTileDistance(itPos_);
        const int currScore = singleTileDistance(previous->getItPos());
        actualHeuristicScore_ += currScore - prevScore;
    }
    if (actualHeuristicScore_ == 0) {
        heuristicScore_ = 0;
    } else {
        heuristicScore_ = 1;
    }
};


void StateUniformCost::setHeuristicScore()
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
    actualHeuristicScore_ = h;
    if (actualHeuristicScore_ == 0) {
        heuristicScore_ = 0;
    } else {
        heuristicScore_ = 1;
    }
};
