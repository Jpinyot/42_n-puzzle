/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:55:50 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/01 18:31:08 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

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

const bool	State::canMoveTo(const Moves& move) const
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

void State::display() const
{
	char move;
	switch(move_)
	{
		case N :
			move = 'N';
			break;
		case E :
			move = 'E';
			break;
		case W :
			move = 'W';
			break;
		case S :
			move = 'S';
			break;
		default :
			move = '-';
	}
	cout << "--" << move << "--\n";
	for(int i = 0; i < puzzle_.size(); i++) {
		cout << static_cast<int>(puzzle_[i]) << ' ';
		if ((i+1) % k_size == 0) {
			cout << '\n';
		}
	}
	cout << "\n";
}

void State::displaySteps(const bool disp, const bool isFirst) const
{
	if (previous_ != NULL) {
		previous_->displaySteps(disp, false);
		if (previous_->previous_ != NULL && !disp) {
			cout << "-";
		}
	}

	if (disp) {
		display();
	} else {
		switch (move_) {
			case N:
				cout << "N";
				break;

			case E:
				cout << "E";
				break;

			case S:
				cout << "S";
				break;

			case W:
				cout << "W";
				break;

			default:
				cout << "Steps: ";
				break;
		}

		if (isFirst) {
			cout << "\n";
		}
	}
}
