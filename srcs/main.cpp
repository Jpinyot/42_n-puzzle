/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 11:46:41 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "closedStack.h"
#include "shuffler.h"
#include "openStack.h"
#include <iostream>

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
	
	int prev = 0;
	while (openStack.getTop() != NULL) {
		// openStack.display();
		State *state = openStack.getTop();
		if (state->getMoveCount() > prev) {
			prev = state->getMoveCount();
			cout << prev << '\n';
		}
		if (state->getHeuristicScore() == 0) {
			cout << "Solved in " << state->getMoveCount() << " steps.\n";
			state->displaySteps(true);
			return 0;
		}
		else {
			openStack.popTop();
			if (closedStack.stateIsClosed(state)) {
				delete state;
				continue;
			}
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

const int k_test_size = k_size * k_size;
int	main()
{
	unsigned char puzzleArr[k_test_size] = {	3,1,6,
												0,8,5,
												2,4,7};


	// unsigned char puzzleHard[k_test_size] = {
	// 	0,12,7,1,
	// 	14,10,15,5,
	// 	2,6,11,9,
	// 	3,4,8,13,
	// };

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
	Shuffler shuffler = Shuffler(3);
	shuffler.shuffle(10);
	shuffler.display();
	return (0);
}
