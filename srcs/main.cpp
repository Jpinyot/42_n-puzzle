/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/09/30 16:48:31 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "closedStack.h"
#include "openStack.h"
#include <iostream>

int solve(StateManhattanDistance firstState)
{
	OpenStack openStack = OpenStack();
	openStack.addState(firstState);

	ClosedStack closedStack = ClosedStack();
	
	while (openStack.getTop() != NULL) {
		openStack.display();
		State *state = openStack.getTop();
		if (state->getHeuristicScore() == 0) {
			state->display();
			return 0;
		}
		else {
			openStack.popTop();
			closedStack.addState(*state);
			openStack.display();

			if (state->canMoveTo(N)) {
				StateManhattanDistance newState = StateManhattanDistance(state, N);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
			}

			if (state->canMoveTo(E)) {
				printf("E\n");
				StateManhattanDistance newState = StateManhattanDistance(state, E);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
			}

			if (state->canMoveTo(S)) {
				printf("S\n");
				StateManhattanDistance newState = StateManhattanDistance(state, S);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
			}

			if (state->canMoveTo(W)) {
				printf("W\n");
				StateManhattanDistance newState = StateManhattanDistance(state, W);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
			}
		}
	}

	return 1;
}

int	main()
{
	vector<char> puzzle;
	puzzle.push_back(0);
	puzzle.push_back(1);
	puzzle.push_back(2);
	puzzle.push_back(3);
	puzzle.push_back(4);
	puzzle.push_back(5);
	puzzle.push_back(6);
	puzzle.push_back(7);
	puzzle.push_back(8);
	StateManhattanDistance state(puzzle);
	cout << state.getScore();
	return (0);
}
