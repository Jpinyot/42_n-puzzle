/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:57:58 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/14 00:30:28 by jpinyot          ###   ########.fr       */
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
	int			arr[9] = {8, 7, 6,
						  5, 4, 3,
						  2, 1, 0};
	/* int			arr[9] = {8, 7, 6, */
	/* 					  5, 4, 3, */
	/* 					  0, 2, 1}; */
	/* int				arr[16] = {12, 14, 9, 2, */
	/* 						   4, 0, 15, 3, */
	/* 						   1, 10, 11, 8, */
	/* 						   13, 6, 7, 5}; */
	/* int				arr[9] = {1,   5,   0,  	//IRRESAOLUBLE?? */
							  /* 7,   6,   4, */ 
							  /* 2,   3,   8}; */
	/* int				arr[9] = {4, 5, 6, */
	/* 						  1, 2, 3, */
							  /* 7, 8, 0}; */
	/* int				arr[9] = {7, 1, 8,				//HARD */
	/* 						  5, 2, 6, */
	/* 						  3, 4, 0}; */
	vector<int> test(arr, arr + 9);
	Nodes rootNode;
	/* write(1, "#", 1); */
	root_ = &rootNode;
	root_->setPuzzle(test);
	setItPos();
	actual_ = root_;
	calculateManDist();
	vector<Nodes*> tmp;
	tmp.push_back(root_);
	nodes_.push_back(tmp);

	/* end of need some work */
	for (costIt_ = 0; costIt_ < nodes_.size(); costIt_++){
	/* for (costIt_ = 0; costIt_ < 9; costIt_++){ */
			/* write(1, "@", 1); */
		for (int j = 0; j < nodes_[costIt_].size(); j++){
			/* write(1, "#", 1); */
			actual_ = nodes_[costIt_][j];
			move();
			/* write(1, "$", 1); */
			if (actual_->h() == 0){
				return ;
			}
			/* for (int i = 0; i < actual_->puzzle_.size(); i++){ */
			/* 	cout << actual_->puzzle_[i] << ' '; */
			/* 	if ((i + 1) % 3 == 0) */
			/* 		cout << '\n'; */
			/* } */
			/* cout << '\n'; */
		}
		/* cout << '\t'; */
		/* cout << actual_->h() << "\n"; */


		/* actual_ = root_->best_;			//tmp to check if all ok */

		cout << costIt_ << "---s\n";
		/* cout << actual_->g() << '\n'; */
		for (int i = 0; i < nodes_[costIt_ + 1].size(); i++){
			for (int j = 0; j < actual_->puzzle_.size(); j++){
				cout << nodes_[costIt_ + 1][i]->puzzle_[j] << ' ';
				if ((j + 1) % 3 == 0)
					cout << "\n";
			}
			cout << "\n";
		}
		cout << costIt_ << "---end\n\n";

	}

	/* PRINT */
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

void	ManhattanDistance::newNode(int nodeCost, Moves lastMove)
{
	int nextItPos = 0;
	switch (lastMove){
		case N:
			nextItPos = actual_->itPos() - size_;
			break;
		case E:
			nextItPos = actual_->itPos() + 1;
			break;
		case S:
			nextItPos = actual_->itPos() + size_;
			break;
		case W:
			nextItPos = actual_->itPos() - 1;
			break;
		default:
			break;
	}
	if (costIt_ + 1 > nodesCost_.size()){
		nodesCost_.push_back(nodeCost);
		vector<Nodes*> tmp;
		nodes_.push_back(tmp);

	}
	if (nodeCost < nodesCost_[costIt_ + 1]){
		nodesCost_[costIt_ + 1] = nodeCost;
		nodes_.erase(nodes_.begin() + costIt_);
		vector<Nodes*> tmp;
		nodes_.push_back(tmp);
	}
	Nodes* node = new Nodes(actual_);
	node->puzzle_[node->itPos()] = node->puzzle_[nextItPos];
	node->puzzle_[nextItPos] = iterator_;
	node->setH(nodeCost);
	node->increaseG();
	node->setLastMove(lastMove);
	node->setItPos(nextItPos);

	write(1, "%", 1);
	nodes_[costIt_ + 1].push_back(node);
}

void	ManhattanDistance::move()
{
	if (actual_->lastMove() != S){				//NORTH
		int moveN = manDistAfterMove(N);
		if (moveN != -1 && (nodesCost_.size() < costIt_ + 1 || moveN <= nodesCost_[costIt_ + 1])){
			/* write(1, "*", 1); */
			newNode(moveN, N);
		}
	}
	if (actual_->lastMove() != W){			//EST
		int moveE = manDistAfterMove(E);
		if (moveE != -1 && (nodesCost_.size() < costIt_ + 1 || moveE <= nodesCost_[costIt_ + 1])){
			newNode(moveE, E);
		}
	}
	if (actual_->lastMove() != N){		//SOUTH
		int moveS = manDistAfterMove(S);
		if (moveS != -1 && (nodesCost_.size() < costIt_ + 1 || moveS <= nodesCost_[costIt_ + 1])){
			newNode(moveS,S);
		}
	}
	if (actual_->lastMove() != E){		//WEST
		int moveW = manDistAfterMove(W);
		if (moveW != -1 && (nodesCost_.size() < costIt_ + 1 || moveW <= nodesCost_[costIt_ + 1])){
			newNode(moveW, W);
		}
	}
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
