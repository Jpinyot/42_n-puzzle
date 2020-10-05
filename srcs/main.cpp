/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 17:28:02 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 18:58:17 by mfiguera         ###   ########.fr       */
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

static int astar(State *firstState, State* (moveStateTo)(State*, Moves&))
{
	int n_openStates = 0;
	OpenStack openStack = OpenStack(firstState);
	ClosedStack closedStack = ClosedStack();

	while (openStack.getTop() != NULL) {
		State *state = openStack.getTop();
		n_openStates++;
		if (state->getHeuristicScore() == 0) {
			cout << "Total opened states: " << n_openStates << ".\n";
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
					State *newState = moveStateTo(state, dir);
					if (!closedStack.stateIsClosed(newState))
						openStack.addState(newState);
				}
			}
		}
	}
	return 0;
}

int idasearch(State *path, int bound, State* (moveStateTo)(State*, Moves&))
{
	int f = path->getScore();
	if (f > bound) {return f;}
	if (path->getHeuristicScore() == 0) {return 0;}
	int min = k_infinite;
	for (int i = Moves::N; i < Moves::none; i++) {
		Moves dir = static_cast<Moves>(i);
		if (path->canMoveTo(dir)){
			State *newNode = moveStateTo(path, dir);
			int t = idasearch(newNode, bound, moveStateTo);
			if (t == 0) {return 0;}
			if (t < min) {min = t;}
			delete newNode;
		}
	}
	return min;
}

static int idastar(State *firstState, State* (moveStateTo)(State*, Moves&))
{
	int bound = firstState->getHeuristicScore();
	int t;

	while (true) {
		t = search(path, bound);
		if (t == 0) {
			//Solution found
		}
		if (t == k_infinite) {
			//no solution
		}
		bound = t;
	}
}

static int solve(State *firstState, const char *heuristic)
{
	State *(*moveStateTo)(State*, Moves&) = heuristicTypes[heuristic];
	int n_openStates = 0;

	if (firstState->isSolvable()) {
		if (astar(firstState, moveStateTo)) {
			return 1;
		}
	}
	cout << "Total opened states: " << n_openStates << ".\n";
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
