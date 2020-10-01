/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateShuffler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:25:21 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/01 16:45:18 by mfiguera         ###   ########.fr       */
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


void StateShuffler::setHeuristicScoreFromPrev() {int i;}
const int StateShuffler::singleTileDistance(int i) const {return -1;}