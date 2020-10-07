/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:06:13 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/07 16:48:48 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithms.h"

static void outputSolution(State *solution) {
	cout << "Solved in " << solution->getMoveCount() << " steps.\n";
	solution->displaySteps();
	cout << "Total opened states: " << State::getStatesCreated() << ".\n";
	cout << "Max active states at once: " << State::getMaxStatesActive() << ".\n";
}

int astar(State *firstState)
{
	OpenStack openStack = OpenStack(firstState);
	ClosedStack closedStack = ClosedStack();

	while (openStack.getTop() != NULL) {
		State *state = openStack.getTop();
		if (state->getHeuristicScore() == 0) {
			outputSolution(state);
			return 1;
		}
		else {
			openStack.popTop();
			if (closedStack.stateIsClosed(state)) {
				delete state;
				continue;
			}
			closedStack.addState(state);
			for (int i = Moves::N; i < Moves::none; i++){
				Moves dir = static_cast<Moves>(i);
				if (state->canMoveTo(dir)) {
					State *newState = state->moveTo(dir);
					if (!closedStack.stateIsClosed(newState))
						openStack.addState(newState);
					else
						delete newState;
				}
			}
		}
	}
	return 0;
}

static int idasearch(UnsortedStack *stack, int bound)
{
	State *state = stack->getTop();
	int f = state->getScore();
	if (f > bound) {return f;}
	if (state->getHeuristicScore() == 0) {return 0;}
	int min = k_infinite;
	for (int i = Moves::N; i < Moves::none; i++) { //need to sort these based on score.
		Moves dir = static_cast<Moves>(i);
		if (state->canMoveTo(dir)){
			State *newNode = state->moveTo(dir);
			stack->addState(newNode);
			int t = idasearch(stack, bound);
			if (t == 0) {return 0;}
			if (t < min) {min = t;}
			stack->popTop();
			delete newNode;
		}
	}
	return min;
}

int idastar(State *firstState)
{
	UnsortedStack *stack = new UnsortedStack(firstState);
	int bound = firstState->getHeuristicScore();
	int t;

	while (true) {
		t = idasearch(stack, bound);
		if (t == 0) {
			State *state = stack->getTop();
			outputSolution(state);
			delete stack;
			return 1;
		}
		if (t == k_infinite) {
			return 0;
		}
		bound = t;
	}
}