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
	State* currState = stack_.at(state.getScore()); //TODO:currState better name:{D
	if (currState == NULL) {
		currState[state.getScore()] = state;
	}
	else {
		while (currState != NULL) {
			/* if (currState.getPuzzle */
			/* 		} */
		}
	}
}
