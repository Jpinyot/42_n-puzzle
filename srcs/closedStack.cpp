/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closedStack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:30:32 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 10:20:56 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "closedStack.h"

void	ClosedStack::addState(State* state)
{
	if (state->getHeuristicScore() > stack_.size()) {
		for(int i = stack_.size(); i < state->getHeuristicScore(); i++) {
			stack_.push_back(NULL);
		}
	}

	state->setNext(stack_.at(state->getHeuristicScore()));
	stack_[state->getHeuristicScore()] = state;
}

const bool	ClosedStack::stateIsClosed(State* state) const
{
	if (state->getHeuristicScore() > stack_.size()) {
		return false;
	}
	else {
		State* currState = stack_.at(state->getHeuristicScore());
		while (currState != NULL)
		{
			if (currState->getPuzzle() == state->getPuzzle()) {
				return true;
			}
			currState = currState->getNext();
		}
		return false;
	}
}
