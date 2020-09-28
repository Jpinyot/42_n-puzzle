/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:55:50 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/28 15:03:14 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

void State::setScoreFromPrev()
{

}

void State::setPuzzleFromPrev()
{
	int nextItPos = 0;
    int prevItPos = previous_->getItPos();
	switch (move_){
		case N:
			nextItPos = prevItPos - k_size;
			break;
		case E:
			nextItPos = prevItPos + 1;
			break;
		case S:
			nextItPos = prevItPos + k_size;
			break;
		case W:
			nextItPos = prevItPos - 1;
			break;
		default:
			break;
	}

    puzzle_ = previous_->getPuzzle();
    if (nextItPos < puzzle_.size()) {
        puzzle_.at(prevItPos) = puzzle_.at(nextItPos);
        puzzle_.at(nextItPos) = k_itValue;

        itPos_ = nextItPos;
    }

}

const bool	State::canMoveTo(const Moves& move)
{
	int		pos = 0;
	switch (move){
		case N:
			pos = itPos_ - k_size;
			return !(pos < 0) && move_ != S;
			break;
		case E:
			pos = itPos_ + 1;
			return !(pos / k_size != itPos_ / k_size) && move_ != W;
			break;
		case S:
			pos = itPos_ + k_size;
			return !(pos >= k_size * k_size) && move_ != N;
			break;
		case W:
			pos = itPos_ - 1;
			return !(pos < 0 || pos / k_size != itPos_ / k_size) && move_ != E;
			break;
		default:
			return (false);
	}
}



