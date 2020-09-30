/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:55:50 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 18:10:21 by jpinyot          ###   ########.fr       */
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

    /* puzzle_ = vector<char>(previous_->getPuzzle()); */
    for (auto & tile : previous_->getPuzzle()) {
	    puzzle_.push_back(tile);
    }
    /* if (nextItPos < puzzle_.size()) { */
    /*     puzzle_.at(prevItPos) = puzzle_.at(nextItPos); */
    /*     puzzle_.at(nextItPos) = k_itValue; */

    /*     itPos_ = nextItPos; */
    /* } */

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

int		maxWidth(int val, int out)
{
	if (val == 0)
		return out;
	return maxWidth(val / 10, out + 1);
}

void State::display()
{
	/* cout << puzzle_; */
	char move;
	switch(move_)
	{
		case N :
			move = 'n';
			break;
		case E :
			move = 'e';
			break;
		case W :
			move = 'w';
			break;
		case S :
			move = 's';
			break;
		default :
			move = '-';
	}
	cout << "--" << move << "--\n";
	/* cout << "b--\n" << "<<" << puzzle_.size() << ">>\n"; */
	/* for(auto &tile : puzzle_) { */
	for(int i = 0; i < puzzle_.size(); i++) {
		cout << static_cast<int>(puzzle_[i]) << ' ';
		if ((i+1) % k_size == 0) {
			cout << '\n';
		}
	}
	cout << "\n\n";
	/* int spacing = maxWidth(k_size * k_size - 1, 1); */
	/* for (int i = 0; i < k_size; i++) { */
	/* 	for (int j = 0; j < k_size; j++) { */
	/* 		char c = puzzle_[i*k_size + j]; */
	/* 		printf("%*d", spacing, c); */
	/* 	} */
	/* 	printf("\n"); */
	/* } */
}

