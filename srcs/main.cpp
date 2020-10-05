/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 16:30:15 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "state.h" */
#include "stateManhattanDistance.h"
#include "stateLinearConflict.h"
#include "closedStack.h"
#include "shuffler.h"
#include "openStack.h"
#include <iostream>
#include <map>

map<const char*, State *(*)(State*,Moves&)> heuristicTypes = {
    { "ManDist", StateManhattanDistance::moveTo},
    { "LinConf", StateLinearConflict::moveTo}
  };

static int solve(State *firstState, const char *heuristic)
{
	State *(*moveStateTo)(State*, Moves&) = heuristicTypes[heuristic];

	if (firstState->isSolvable()) {

		OpenStack openStack = OpenStack(firstState);
		ClosedStack closedStack = ClosedStack();

		while (openStack.getTop() != NULL) {
			State *state = openStack.getTop();
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
				for (int i = Moves::N; i < Moves::none; i++){
					Moves dir = static_cast<Moves>(i);
					if (state->canMoveTo(dir)) {
						State *newState = moveStateTo(state, dir);
						if (!closedStack.stateIsClosed(newState))
							openStack.addState(newState);
					}
				}
			}
		}
	}
	
	cout << "Not solvable puzzle.\n";
	firstState->display();
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
	shuffler.shuffle(25);
	solve(new StateManhattanDistance(shuffler.getPuzzle(), none), "LinConf");
	// shuffler.display();
	return (0);
}
