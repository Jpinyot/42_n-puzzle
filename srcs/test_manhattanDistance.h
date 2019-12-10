/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_manhattanDistance.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:45:06 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/10 20:56:06 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>		//vector
#include <iostream>		//cout

#define SIZE 3;

using namespace std;

enum Moves
{
	none,
	N,
	E,
	S,
	W
};

class ManhattanDistance
{
	private:
		vector<int>	puzzle_;
		int			iterator_;
		int			itPos_;
		int			size_;
		int			g_;		//number of steps taken to current state
		int			h_;		//estimated number of steps taken from current statet to goal
		int			manDist_;
		int			lastMove_;

		/* void	setIterator() {iterator_ = (3 * 3) / 2;} */
		void	setItPos();
		void	calculateManDist();
		int		manDistAfterMove(Moves nextMove = none);
		void	move();

	public:
		ManhattanDistance():
			puzzle_(0), iterator_(0), itPos_(0), size_(3), g_(0), h_(0), manDist_(0), lastMove_(none)
		{
		};
		void	solve();
};
