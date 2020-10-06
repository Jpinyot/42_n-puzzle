/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/06 09:49:43 by mfiguera         ###   ########.fr       */
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

int k_infinite = 9999999;

static int astar(State *firstState)
{
	OpenStack openStack = OpenStack(firstState);
	ClosedStack closedStack = ClosedStack();

	while (openStack.getTop() != NULL) {
		State *state = openStack.getTop();
		if (state->getHeuristicScore() == 0) {
			cout << "Total opened states: " << State::getStatesCreated() << ".\n";
			cout << "Max active states at once: " << State::getMaxStatesActive() << ".\n";
			cout << "Solved in " << state->getMoveCount() << " steps.\n";
			state->displaySteps();
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
				}
			}
		}
	}
	return 0;
}

int idasearch(UnsortedStack *stack, int bound)
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

static int idastar(State *firstState)
{
	UnsortedStack *stack = new UnsortedStack(firstState);
	int bound = firstState->getHeuristicScore();
	int t;

	while (true) {
		t = idasearch(stack, bound);
		if (t == 0) {
			State *state = stack->getTop();
			cout << "Total opened states: " << State::getStatesCreated() << ".\n";
			cout << "Max active states at once: " << State::getMaxStatesActive() << ".\n";
			cout << "Solved in " << state->getMoveCount() << " steps.\n";
			state->displaySteps();
			return 1;
		}
		if (t == k_infinite) {
			//no solution
			return 0;
		}
		bound = t;
	}
}

static int solve(State *firstState)
{
	if (firstState->isSolvable()) {
		if (idastar(firstState)) {
			return 1;
		}
	}
	cout << "Total opened states: " << State::getStatesCreated() << ".\n";
	cout << "Not solvable puzzle.\n";
	firstState->display();
	return 1;
}

const int k_test_size = k_size * k_size;
int	main()
{
	unsigned char puzzleArr[k_test_size] = {	7,5,6,
												1,4,3,
												2,8,0};


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
	Shuffler shuffler = Shuffler(3);
	shuffler.shuffle(170);
	solve(new StateManhattanDistance(puzzle, none), "LinConf");
	// shuffler.display();
	return (0);
}
