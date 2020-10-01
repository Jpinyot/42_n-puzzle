/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stateShuffler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:26:40 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/01 16:44:09 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

class StateShuffler : public State
{
	private:
		virtual void    setHeuristicScoreFromPrev();
		virtual void    setHeuristicScore();
		vector<unsigned char> genPuzzle(int size);

	public:
		virtual const int singleTileDistance(int i) const;

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