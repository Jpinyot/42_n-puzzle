/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/01 17:30:07 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "closedStack.h"
#include "stateShuffler.h"
#include "openStack.h"
#include <iostream>

StateShuffler	*shuffle(StateShuffler *state, int n_moves)
{
    int i = 0;
	StateShuffler *currState = state;
    while (i < n_moves) {
        Moves move = static_cast<Moves>(rand() % (Moves::none));
        if (currState->canMoveTo(move)) {
			currState = new StateShuffler(currState, move);
            i++;
        }
    }
	return currState;
}

static int solve(StateManhattanDistance *firstState)
{
	if (!firstState->isSolvable()) {
		cout << "Not solvable puzzle.\n";
		firstState->display();
		return 1;
	}
	OpenStack openStack = OpenStack();
	openStack.addState(firstState);

	ClosedStack closedStack = ClosedStack();
	
	while (openStack.getTop() != NULL) {
		openStack.display();
		State *state = openStack.getTop();
		if (state->getHeuristicScore() == 0) {
			state->displaySteps(true);
			return 0;
		}
		else {
			openStack.popTop();
			closedStack.addState(state);
			if (state->canMoveTo(N)) {
				StateManhattanDistance *newState = new StateManhattanDistance(state, N);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(E)) {
				/* cout <<"E\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, E);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(S)) {
				/* cout <<"S\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, S);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}

			if (state->canMoveTo(W)) {
				/* cout <<"W\n"; */
				StateManhattanDistance *newState = new StateManhattanDistance(state, W);
				if (!closedStack.stateIsClosed(newState))
					openStack.addState(newState);
				/* newState.display(); */
			}
		}
	}

	return 1;
}

const int k_test_size = 9;
int	main()
{
	unsigned char puzzleArr[k_test_size] = {	0,4,2,
					3,1,5,
					6,7,8};
	vector<unsigned char> puzzle;
	for (int i = 0; i < k_test_size ; i++) {
		puzzle.emplace_back(puzzleArr[i]);
	}
	/* puzzle.push_back(0); */
	/* puzzle.push_back(3); */
	/* puzzle.push_back(2); */
	/* puzzle.push_back(1); */
	/* puzzle.push_back(4); */
	/* puzzle.push_back(5); */
	/* puzzle.push_back(6); */
	/* puzzle.push_back(7); */
	/* puzzle.push_back(8); */
	StateManhattanDistance *state = new StateManhattanDistance(puzzle);
	solve(state);
	cout << state->getScore();
	return (0);
}
