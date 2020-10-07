/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shuffler.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:25:21 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/06 18:46:58 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shuffler.h"

const vector<unsigned char>  StateSolution::genPuzzle(int size)
{
    vector<unsigned char> puzzle;

    for (int i = 0; i < size * size; i++) {
        puzzle.emplace_back(i);
    }
    return puzzle;
}

void	StateSolution::setHeuristicScore()
{
	for (int i = 0; i < puzzle_.size(); i++) {
		if (puzzle_[i] == k_itValue){
            itPos_ = i;
		}
	}
    heuristicScore_ = 0;
};

void	Shuffler::shuffle(int n_moves)
{
    int i = 0;
    while (i < n_moves) {
        Moves move = static_cast<Moves>(rand() % (Moves::none));
        if (solution_->canMoveTo(move)) {
			solution_  = solution_->moveTo(move);
            i++;
        }
    }
}
