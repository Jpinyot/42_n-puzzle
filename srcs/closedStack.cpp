/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closedStack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:30:32 by jpinyot           #+#    #+#             */
/*   Updated: 2020/09/28 18:47:32 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "closedStack.h"

void	ClosedStack::addState(State& state)
{
	if (state.getScore() > stack_.size()) {
		for(int i = stack_.size(); i < state.getScore(); i++) {
			stack_.push_back(NULL);
		}
	}

	state.setNext(stack_.at(state.getScore()));
	stack_[state.getScore()] = &state;
}

bool	ClosedStack::stateIsClosed(State& state)
{
	if (state.getScore() > stack_.size()) {
		return false;
	}
	else {
		State* currState = stack_.at(state.getScore());
		while (currState != NULL)
		{
			if (currState->getPuzzle() == state.getPuzzle()) {
				return true;
			}
			currState = currState->getNext();
		}
		return false;
	}
}
