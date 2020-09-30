/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateManhattanDistance.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:17:54 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 18:12:54 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stateManhattanDistance.h"

const int StateManhattanDistance::singleTileDistance(int tile)
{
    int xAxis = abs(( puzzle_[tile] - ((puzzle_[tile] / k_size) * k_size)) - (tile -((tile / k_size) * k_size)));
	int	yAxis = abs(puzzle_[tile] / k_size - tile / k_size);
	return (xAxis + yAxis);
};


void StateManhattanDistance::setHeuristicScoreFromPrev()
{
    State* previous = getPrevious();
    display();
    if (previous != NULL) {
        const int prevScore = previous->singleTileDistance(itPos_);
        const int currScore = singleTileDistance(previous->getItPos());
        heuristicScore_ += currScore - prevScore;
    }
};


void StateManhattanDistance::setHeuristicScore()
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
