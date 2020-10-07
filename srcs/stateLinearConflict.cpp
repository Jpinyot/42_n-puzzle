/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateLinearConflict.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:23:55 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/03 19:15:26 by mfiguera         ###   ########.fr       */
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

const int singleTileConflicts(const vector<unsigned char> puzzle, int tile){
    int conflictCount = 0;
    int row = tile / k_size;
    int col = tile % k_size;
    const bool isDestRow = destRow(puzzle, tile) == row;
    const bool isDestCol = destCol(puzzle, tile) == col;
    if (!(isDestCol || isDestRow) || puzzle[tile] == k_itValue) {
        return 0;
    }
    for (int i = 0; i < k_size * k_size; i++) {
        int rowForI = i / k_size;
        int colForI = i % k_size;
        if (((isDestRow && rowForI == row) || (isDestCol && colForI == col)) && puzzle[i] != k_itValue) {
            const bool isDestRowForI = (destRow(puzzle, i) == rowForI) && isDestRow && row == rowForI;
            const bool isDestColForI = (destCol(puzzle, i) == colForI) && isDestCol && col == colForI;
            if ((isDestColForI || isDestRowForI) && ((i > tile) ^ (puzzle[i] > puzzle[tile]))){
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
        const int prevConflicts = singleTileConflicts(previous->getPuzzle(), itPos_);
        const int currConflicts = singleTileConflicts(getPuzzle(), previous->getItPos());
        heuristicScore_ += currScore - prevScore + 2 * (currConflicts - prevConflicts);
    }
};


void StateLinearConflict::setHeuristicScore()
{
    int	h = 0;
    int c = 0;
	for (int i = 0; i < puzzle_.size(); i++) {
		if (puzzle_[i] != k_itValue){
            h += singleTileDistance(i);
            c += singleTileConflicts(puzzle_, i);
		}
        else {
            itPos_ = i;
        }
	}
    heuristicScore_ = h + c;
};
