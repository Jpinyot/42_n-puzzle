/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:43:55 by jpinyot           #+#    #+#             */
/*   Updated: 2019/12/12 23:03:17 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>			//vector
#include <unistd.h>			//write
using namespace std;

enum Moves
{
	none,
	N,
	E,
	S,
	W
};

class	Nodes
{
	private:
		int			manDist_;
		int			h_;
		int			g_;
		int			itPos_;
		int			lastMove_;		//need some work

	public:
		Nodes():
			manDist_(0), h_(0), g_(0), itPos_(0), lastMove_(0), puzzle_(0), n_(0), e_(0), s_(0), w_(0), origin_(0), best_(0) 
		{

		}
		Nodes(Nodes* base):
			manDist_(base->manDist()), h_(base->h()), g_(base->g()), itPos_(base->itPos()), lastMove_(0), puzzle_(base->puzzle()), n_(0), e_(0), s_(0), w_(0), origin_(base), best_(0) 
		{
			/* write(1, "$", 1); */
			/* vector<int> newVec(base->puzzle_); */
			/* puzzle_ = newVec; */
		}

		vector<int>	puzzle_;
		Nodes*		n_;
		Nodes*		e_;
		Nodes*		s_;
		Nodes*		w_;
		Nodes*		origin_;
		Nodes*		best_;

		vector<int>	puzzle() {return puzzle_;}
		int			manDist() {return manDist_;}
		int			h() {return h_;}
		int			g() {return g_;}
		int			itPos() {return itPos_;}
		int			lastMove() {return lastMove_;}

		void		setPuzzle(vector<int> puzzle) {puzzle_ = puzzle;}
		void		setManDist(int manDist) {manDist_ = manDist;}
		void		setH(int h) {manDist_ += h - h_; h_ = h;}
		void		setG(int g) {manDist_ += g - g_; g_ = g;}
		void		increaseG() {manDist_ += 1; g_ += 1;}
		void		setItPos(int itPos) {itPos_ = itPos;}
		void		setBest(Nodes* best) {best_ = best;}
		void		setOrigin(Nodes* origin) {origin_ = origin;}
		void		setN(Nodes* n) {n_ = n;}
		void		setE(Nodes* e) {e_ = e;}
		void		setS(Nodes* s) {s_ = s;}
		void		setW(Nodes* w) {w_ = w;}
		void		setLastMove(Moves lastMove) {lastMove_ = lastMove;} 
};
