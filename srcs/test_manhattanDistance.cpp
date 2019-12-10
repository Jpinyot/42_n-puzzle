/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:57:58 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/10 22:37:02 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_manhattanDistance.h"

void	ManhattanDistance::solve()
{
	/* need some work */
	/* int			arr[9] = {1, 4, 3, */
	/* 					  2, 5, 0, */
	/* 					  8, 7, 6}; */
	int			arr[9] = {0, 1, 5,			//IRRESOLUBLE
						  4, 3, 2,
						  6, 7, 8};
	/* int			arr[9] = {8, 7, 6, */
	/* 					  5, 4, 3, */
	/* 					  2, 1, 0}; */
	/* int			arr[9] = {8, 7, 6, */
	/* 					  5, 4, 3, */
	/* 					  0, 2, 1}; */
	vector<int> test(arr, arr+ 9);
	puzzle_ = test;
	iterator_ = 5;		//need to work for difference size
	setItPos();
	calculateManDist();
	cout << h_ << "\n\n";

	/* end of need some work */
	while (h_){
		for (int i = 0; i < puzzle_.size(); i++){
			cout << puzzle_[i] << ' ';
			if ((i + 1) % 3 == 0)
				cout << '\n';
		}
		cout << '\t';
		cout << lastMove_ << "\n";

		move();
		g_ += 1;
	}

	/* PRINT */
	cout << '\n';
	/* cout << h_ << "\n\n"; */
	for (int i = 0; i < puzzle_.size(); i++){
		cout << puzzle_[i] << ' ';
		if ((i + 1) % 3 == 0)
			cout << '\n';
	}
}

void	ManhattanDistance::calculateManDist()
{
	for (int i = 0; i < puzzle_.size(); i++){
		if (puzzle_[i] != iterator_){
			int xAxis = abs(( puzzle_[i] - ((puzzle_[i] / size_) * size_)) - (i -((i / size_) * size_)));
			int	yAxis = abs(puzzle_[i] / size_ - i / size_);
			h_ += xAxis + yAxis;
		}		
	}
	manDist_ = h_ + g_;
}

int		ManhattanDistance::manDistAfterMove(Moves lastMove)
{
	int		tempH = h_;
	int		pos = 0;
	switch (lastMove){
		case N:
			pos = itPos_ - size_;
			if (pos < 0){
				return (-1);
			}
			break;
		case E:
			pos = itPos_ + 1;
			if (pos / size_ != itPos_ / size_){
				return (-1);
			}
			break;
		case S:
			pos = itPos_ + size_;
			if (pos >= size_ * size_){
				return (-1);
			}
			break;
		case W:
			pos = itPos_ - 1;
			if (pos < 0 || pos / size_ != itPos_ / size_){
				return (-1);
			}
			break;
		default:
			cout << "$";
			return (-1);
	}
	int	oldXAxis = abs(( puzzle_[pos] - ((puzzle_[pos] / size_) * size_)) - (pos -((pos / size_) * size_)));
	int	oldYAxis = abs(puzzle_[pos] / size_ - pos / size_);
	int	newXAxis = abs(( puzzle_[pos] - ((puzzle_[pos] / size_) * size_)) - (itPos_ -((itPos_ / size_) * size_)));
	int	newYAxis = abs(puzzle_[pos] / size_ - itPos_ / size_);
	tempH += (newXAxis + newYAxis) - (oldXAxis + oldYAxis);
	return tempH;
}

void	ManhattanDistance::move()
{
	Moves	nextMove = none;
	int		nextMoveH = -1;
	if (lastMove_ != S){
		int moveN = manDistAfterMove(N);
		if (moveN != -1){
			nextMove = N;
			nextMoveH = moveN;
		}
	}
	if (lastMove_ != W){
		int moveE = manDistAfterMove(E);
		if (moveE != -1 && (nextMove == none || nextMoveH > moveE)){
			nextMove = E;
			nextMoveH = moveE;
		}
	}
	if (lastMove_ != N){
		int moveS = manDistAfterMove(S);
		if (moveS != -1 && (nextMove == none || nextMoveH > moveS)){
			nextMove = S;
			nextMoveH = moveS;
		}
	}
	if (lastMove_ != E){
		int moveW = manDistAfterMove(W);
		if (moveW != -1 && (nextMove == none || nextMoveH > moveW)){
			nextMove = W;
			nextMoveH = moveW;
		}
	}
	switch (nextMove){
		case N:
			puzzle_[itPos_] = puzzle_[itPos_ - size_];
			puzzle_[itPos_ - size_] = iterator_;
			h_ = nextMoveH;
			lastMove_ = N;
			itPos_ -= size_; 
			break;
		case E:
			puzzle_[itPos_] = puzzle_[itPos_ + 1];
			puzzle_[itPos_ + 1] = iterator_;
			h_ = nextMoveH;
			lastMove_ = E;
			itPos_ += 1; 
			break;
		case S:
			puzzle_[itPos_] = puzzle_[itPos_ + size_];
			puzzle_[itPos_ + size_] = iterator_;
			h_ = nextMoveH;
			lastMove_ = S;
			itPos_ += size_; 
			break;
		case W:
			puzzle_[itPos_] = puzzle_[itPos_ - 1];
			puzzle_[itPos_ - 1] = iterator_;
			h_ = nextMoveH;
			lastMove_ = W;
			itPos_ -= 1; 
			break;
		default:
			cout << "$";
			break;
	}
}

void	ManhattanDistance::setItPos()
{
	for (int i = 0; i < puzzle_.size(); i++){
		if (puzzle_[i] == iterator_){
			itPos_ = i;
			return ;
		}
	}
	iterator_ = -1;
}

int		main(void)
{
	ManhattanDistance manDist;
	manDist.solve();
	//	num/size fila que ha de anar
	//	num/pos fila que esta
	//	abs(1 / 3 - 7 / 3)		calculate y-axis
	/* cout << '\n' << (3 / 3 - 2 / 3) +  (3 % 3 - 2 % 3) << '\n'; */
	/* cout << '\n' << abs(( 3 - ((3 / 3) * 3)) - (2 -((2 / 3) * 3)))  << '\n'; */
	return (0);
}
