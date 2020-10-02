/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateLinearConflict.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:23:55 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/02 12:44:47 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stateLinearConflict.h"

const int StateLinearConflict::singleTileDistance(int tile) const
{
    int xAxis = abs(( puzzle_[tile] - ((puzzle_[tile] / k_size) * k_size)) - (tile -((tile / k_size) * k_size)));
	int	yAxis = abs(puzzle_[tile] / k_size - tile / k_size);
	return (xAxis + yAxis);
};

static const int destRow(vector<unsigned char> puzzle, int pos){return puzzle[pos] / k_size;}
static const int destCol(vector<unsigned char> puzzle, int pos){return puzzle[pos] % k_size;}

const int StateLinearConflict::singleTileConflicts(int tile) const{
    int conflictCount = 0;
    int row = tile / k_size; //TODO row_tile is being compared with row_i
    int col = tile % k_size;
    const bool isDestRow = destRow(puzzle_, tile) == row;
    const bool isDestCol = destCol(puzzle_, tile) == col;
    if (!(isDestCol || isDestRow) || puzzle_[tile] == k_itValue) {
        return 0;
    }
    for (int i = 0; i < k_size * k_size; i++) {
        if (((isDestRow && i / k_size == row) || (isDestCol && i % k_size == col)) && puzzle_[i] != k_itValue) {
            const bool isDestRowForI = (destRow(puzzle_, i) == row) && isDestRow;
            const bool isDestColForI = (destCol(puzzle_, i) == col) && isDestCol;
            if ((isDestColForI || isDestRowForI) && ((i > tile) ^ (puzzle_[i] > puzzle_[tile]))){
                cout << "<" << (int)puzzle_[i]<< "> |" << isDestRow << isDestCol << isDestRowForI << isDestColForI << "| ";
                conflictCount++;
            }
        }
    }
    return conflictCount;
}

void StateLinearConflict::setHeuristicScoreFromPrev()
{
    State* previous = getPrevious();
    if (previous != NULL) {
        const int prevScore = previous->singleTileDistance(itPos_);
        const int currScore = singleTileDistance(previous->getItPos());
        heuristicScore_ += currScore - prevScore;
    }
};


void StateLinearConflict::setHeuristicScore()
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
