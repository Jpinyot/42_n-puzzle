/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateShuffler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:25:21 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/05 10:24:08 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stateShuffler.h"

vector<unsigned char>  StateShuffler::genPuzzle(int size)
{
    vector<unsigned char> puzzle;

    for (int i = 0; i < size * size; i++) {
        puzzle.emplace_back(i);
    }
    return puzzle;
}

void	StateShuffler::setHeuristicScore()
{
	for (int i = 0; i < puzzle_.size(); i++) {
		if (puzzle_[i] == k_itValue){
            itPos_ = i;
		}
	}
    heuristicScore_ = 0;
};

StateShuffler *StateShuffler::shuffle(int n_moves)
{
    int i = 0;
	StateShuffler *currState = this;
    while (i < n_moves) {
        Moves move = static_cast<Moves>(rand() % (Moves::none));
        if (currState->canMoveTo(move)) {
			currState = new StateShuffler(currState, move);
            i++;
        }
    }
	return currState;
}
