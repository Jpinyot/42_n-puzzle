/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateShuffler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:26:40 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/05 10:23:18 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateShuffler : public State
{
	private:
		void setHeuristicScoreFromPrev() {};

		virtual void    setHeuristicScore();
		vector<unsigned char> genPuzzle(int size);

	public:
		const int singleTileDistance(int i) const {return -1;}
		StateShuffler *shuffle(int n_moves);

		StateShuffler(int size):
		State(genPuzzle(size), none)
		{
			setHeuristicScore();
		}

		StateShuffler(StateShuffler *previous, const Moves& move):
		State(previous, move)
		{
			setPuzzleFromPrev();
		}
};
