/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:57:58 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/10 00:22:43 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_manhattanDistance.h"

	/* int		a1[3] = {1, 4, 3}; */
	/* int		a2[3] = {2, 5, 0}; */
	/* int		a3[3] = {8, 7, 6}; */
	/* vector<int>	v1(a1, a1 + 3); */
	/* vector<int>	v2(a2, a2 + 3); */
	/* vector<int>	v3(a3, a3 + 3); */
	/* puzzle_.push_back(v1); */
	/* puzzle_.push_back(v2); */
	/* puzzle_.push_back(v3); */

	/* for (int i = 0; i < puzzle_.size(); i++) */
	/* { */
	/* 	for (int j = 0; j < puzzle_[i].size(); j++){ */
	/* 		cout << puzzle_[i][j] << ' '; */
	/* 	} */
	/* 	cout << '\n'; */
	/* } */

void	ManhattanDistance::solve()
{
	/* need some work */
	/* int			arr[9] = {1, 4, 3, */
	/* 					  2, 5, 0, */
	/* 					  8, 7, 6}; */
	int			arr[9] = {0, 1, 2,
						  3, 4, 5,
						  6, 7, 8};
	vector<int> test(arr, arr+ 9);
	puzzle_ = test;
	iterator_ = 5;		//need to work for difference size
	getItPos();
	calculateManDist();
	cout << h_ << "\n\n";

	/* end of need some work */
//	while (1){		//not work when sorted
		
//	}

	/* PRINT */
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

void	ManhattanDistance::manDistAfterMove(Moves lastMove)
{
	if (lastMove == none){
		for (int i = 0; i < puzzle_.size(); i++){
			if (puzzle_[i] != iterator_){
				int xAxis = abs(( puzzle_[i] - ((puzzle_[i] / size_) * size_)) - (i -((i / size_) * size_)));
				int	yAxis = abs(puzzle_[i] / size_ - i / size_);
				h_ += xAxis + yAxis;
			}		
		}
		manDist_ = h_ + g_;
	}
	int		tempH = h_;
	switch (lastMove){
		case N:
			int pos = itPos - size_;
			
			break;
		case E:
			int pos = itPos + 1;
			break;
		case S:
			int pos = itPos + size_;
			break;
		case W:
			int pos = itPos - 1;
			break;
		default:
			break;
		}
	return tempH;
}

void	ManhattanDistance::getItPos()
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
