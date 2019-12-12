/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:57:58 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/12 22:31:41 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_manhattanDistance.h"

void	ManhattanDistance::solve()
{
	/* need some work */
	/* int			arr[9] = {1, 4, 3, */
						  /* 2, 5, 0, */
						  /* 8, 7, 6}; */
	/* int			arr[9] = {0, 1, 5,			//IRRESOLUBLE */
	/* 					  4, 3, 2, */
	/* 					  6, 7, 8}; */
	/* int			arr[9] = {8, 7, 6, */
	/* 					  5, 4, 3, */
						  /* 2, 1, 0}; */
	/* int			arr[9] = {8, 7, 6, */
	/* 					  5, 4, 3, */
						  /* 0, 2, 1}; */
	/* int				arr[16] = {12, 14, 9, 2, */
	/* 						   4, 0, 15, 3, */
	/* 						   1, 10, 11, 8, */
	/* 						   13, 6, 7, 5}; */
	/* int				arr[9] = {1,   5,   0,  	//IRRESAOLUBLE?? */
							  /* 7,   6,   4, */ 
							  /* 2,   3,   8}; */
	int				arr[9] = {4, 5, 6,
							  1, 2, 3,
							  7, 8, 0};
	/* int				arr[9] = {7, 1, 8,				//HARD */
	/* 						  5, 2, 6, */
	/* 						  3, 4, 0}; */
	vector<int> test(arr, arr + 9);
	iterator_ = 4;		//need to work for difference size
	Nodes rootNode;
	/* write(1, "#", 1); */
	root_ = &rootNode;
	root_->setPuzzle(test);
	setItPos();
	actual_ = root_;
	calculateManDist();

	int count = 0;
	/* end of need some work */
	while (actual_->h()){
		/* cout << '\t'; */
		/* cout << actual_->h() << "\n"; */


		move();
		actual_ = root_->best_;			//tmp to check if all ok

		cout << count << '\n';
		count += 1;
		cout << actual_->g() << '\n';
		if (actual_->n_ || actual_->e_ || actual_->s_ || actual_->w_)
			write(1, "%", 1);
		for (int i = 0; i < actual_->puzzle_.size(); i++){
			cout << actual_->puzzle_[i] << ' ';
			if ((i + 1) % 3 == 0)
				cout << '\n';
		}
		cout << '\n';

	}

	/* PRINT */
	cout << '\n';
	cout << actual_->g() << "\n\n";
	for (int i = 0; i < actual_->puzzle_.size(); i++){
		cout << actual_->puzzle_[i] << ' ';
		if ((i + 1) % 3 == 0)
			cout << '\n';
	}
}

void	ManhattanDistance::calculateManDist()				//something wrong with changing iterator
{
	int	h = 0;
	for (int i = 0; i < root_->puzzle_.size(); i++){
		if (root_->puzzle_[i] != iterator_){
			int xAxis = abs(( root_->puzzle_[i] - ((root_->puzzle_[i] / size_) * size_)) - (i -((i / size_) * size_)));
			int	yAxis = abs(root_->puzzle_[i] / size_ - i / size_);
			h += xAxis + yAxis;
		}		
	}
	root_->setH(h);
}

int		ManhattanDistance::manDistAfterMove(Moves lastMove)
{
	int		tempH = actual_->h();
	int		pos = 0;
	switch (lastMove){
		case N:
			pos = actual_->itPos() - size_;
			if (pos < 0){
				return (-1);
			}
			break;
		case E:
			pos = actual_->itPos() + 1;
			if (pos / size_ != actual_->itPos() / size_){
				return (-1);
			}
			break;
		case S:
			pos = actual_->itPos() + size_;
			if (pos >= size_ * size_){
				return (-1);
			}
			break;
		case W:
			pos = actual_->itPos() - 1;
			if (pos < 0 || pos / size_ != actual_->itPos() / size_){
				return (-1);
			}
			break;
		default:
			cout << "$";
			return (-1);
	}
	int	oldXAxis = abs(( actual_->puzzle_[pos] - ((actual_->puzzle_[pos] / size_) * size_)) - (pos -((pos / size_) * size_)));
	int	oldYAxis = abs(actual_->puzzle_[pos] / size_ - pos / size_);
	int	newXAxis = abs(( actual_->puzzle_[pos] - ((actual_->puzzle_[pos] / size_) * size_)) - (actual_->itPos() -((actual_->itPos() / size_) * size_)));
	int	newYAxis = abs(actual_->puzzle_[pos] / size_ - actual_->itPos() / size_);
	tempH += (newXAxis + newYAxis) - (oldXAxis + oldYAxis);
	return tempH;
}

void	ManhattanDistance::move()
{
	Moves	nextMove = none;
	int		nextMoveH = -1;
	if (actual_->lastMove() != S){				//NORTH
		int moveN = manDistAfterMove(N);
		if (moveN != -1){
			Nodes* nodeN = new Nodes(actual_);
			int	nextItPos = nodeN->itPos() - size_;
			nodeN->puzzle_[nodeN->itPos()] = nodeN->puzzle_[nextItPos];
			nodeN->puzzle_[nextItPos] = iterator_;
			nodeN->setH(moveN);
			nodeN->increaseG();
			nodeN->setLastMove(N);
			nodeN->setItPos(nextItPos);
			nodeN->setBest(nodeN);
			actual_->setN(nodeN);

			nextMove = N;			//set as best
			nextMoveH = moveN;
		}
	}
	if (actual_->lastMove() != W){			//EST
		int moveE = manDistAfterMove(E);
		if (moveE != -1){
			Nodes* nodeE = new Nodes(actual_);
			int	nextItPos = nodeE->itPos() + 1;
			nodeE->puzzle_[nodeE->itPos()] = nodeE->puzzle_[nextItPos];
			nodeE->puzzle_[nextItPos] = iterator_;
			nodeE->setH(moveE);
			nodeE->increaseG();
			nodeE->setLastMove(E);
			nodeE->setItPos(nextItPos);
			nodeE->setBest(nodeE);
			actual_->setE(nodeE);
			if (nextMove == none || nextMoveH > moveE){
				nextMove = E;
				nextMoveH = moveE;
			}
		}
	}
	if (actual_->lastMove() != N){		//SOUTH
		int moveS = manDistAfterMove(S);
		if (moveS != -1){
			Nodes* nodeS = new Nodes(actual_);
			int	nextItPos = nodeS->itPos() + size_;
			nodeS->puzzle_[nodeS->itPos()] = nodeS->puzzle_[nextItPos];
			nodeS->puzzle_[nextItPos] = iterator_;
			nodeS->setH(moveS);
			nodeS->increaseG();
			nodeS->setLastMove(S);
			nodeS->setItPos(nextItPos);
			nodeS->setBest(nodeS);
			actual_->setS(nodeS);
			if (nextMove == none || nextMoveH > moveS){
				nextMove = S;
				nextMoveH = moveS;
			}
		}
	}
	if (actual_->lastMove() != E){		//WEST
		int moveW = manDistAfterMove(W);
		if (moveW != -1){
			Nodes* nodeW = new Nodes(actual_);
			int	nextItPos = nodeW->itPos() - 1;
			nodeW->puzzle_[nodeW->itPos()] = nodeW->puzzle_[nextItPos];
			nodeW->puzzle_[nextItPos] = iterator_;
			nodeW->setH(moveW);
			nodeW->increaseG();
			nodeW->setLastMove(W);
			nodeW->setItPos(nextItPos);
			nodeW->setBest(nodeW);
			actual_->setW(nodeW);
			if (nextMove == none || nextMoveH > moveW){
				nextMove = W;
				nextMoveH = moveW;
			}
		}
	}
	switch (nextMove){
		case N:
			actual_->setBest(actual_->n_);
			break;
		case E:
			actual_->setBest(actual_->e_);
			break;
		case S:
			actual_->setBest(actual_->s_);
			break;
		case W:
			actual_->setBest(actual_->w_);
			break;
		default:
			actual_->setBest(0);
			cout << "$";
			break;
	}
	Nodes* best = actual_->best_;
	for (Nodes* it = actual_->origin_; it; it = it->origin_){
		/* write(1, "&", 1); */
		
		/* if ((it->n_ && it->best_->manDist() > actual_->n_->manDist()) && */
		/* 		(it->e_ && it->best_->manDist() > actual_->e_->manDist()) && */
		/* 		(it->s_ && it->best_->manDist() > actual_->s_->manDist()) && */
		/* 		(it->w_ && it->best_->manDist() > actual_->w_->manDist())){ */
		/* 	it->best_ = actual_->best_; */
		/* } */
		if (it->n_ && it->n_->best_ && it->n_->best_->manDist() < best->manDist()){
			best = it->n_->best_;
		}
		if (it->e_ && it->e_->best_ && it->e_->best_->manDist() < best->manDist()){
			best = it->e_->best_;
		}
		if (it->s_ && it->s_->best_ && it->s_->best_->manDist() < best->manDist()){
			best = it->s_->best_;
		}
		if (it->w_ && it->w_->best_ && it->w_->best_->manDist() < best->manDist()){
			best = it->w_->best_;
		}
		it->best_ = best;
		/* else { */
		/* 	it->best_ = actual_->best_; */
		/* } */
	}
		/* for (int i = 0; i < actual_->e_->puzzle_.size(); i++){ */
		/* 	cout << actual_->e_->puzzle_[i] << ' '; */
		/* 	if ((i + 1) % 3 == 0) */
		/* 		cout << '\n'; */
		/* } */
}

void	ManhattanDistance::setItPos()
{
	for (int i = 0; i < root_->puzzle_.size(); i++){
		if (root_->puzzle_[i] == iterator_){
			root_->setItPos(i);;
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
