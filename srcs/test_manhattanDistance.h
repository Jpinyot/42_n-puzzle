/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:45:06 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/14 00:29:08 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>		//vector
#include <iostream>		//cout
#include <unistd.h>		//write
#include "nodes.h"

#define	SIZE 3;
#define	ITERATOR 4;

using namespace std;

class	ManhattanDistance
{
	private:
		/* vector<int>	puzzle_; */
		int						iterator_;
		Nodes*					root_;
		Nodes*					actual_;
		int						size_;
		vector<vector<Nodes*> >	nodes_;
		vector<int>				nodesCost_;
		int						costIt_;
//		int			itPos_;
//		int			g_;		//number of steps taken to current state
//		int			h_;		//estimated number of steps taken from current statet to goal
//		int			manDist_;
//		int			lastMove_;

		/* void	setIterator() {iterator_ = (3 * 3) / 2;} */
		void	setItPos();
		void	calculateManDist();
		int		manDistAfterMove(Moves nextMove = none);
		void	move();
		void	newNode(int nodeCost, Moves lastMove);

	public:
		ManhattanDistance():
			/* puzzle_(0), iterator_(0), itPos_(0), size_(3), g_(0), h_(0), manDist_(0), lastMove_(none) */
			iterator_(4), root_(), actual_(), size_(3), nodes_(0), nodesCost_(0), costIt_(0)
		{
		};
		void	solve();
};
