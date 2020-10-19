/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:05:42 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/19 09:08:32 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"
#include "stack.h"
#include "closedStack.h"

const int k_infinite = 9999999;

enum Algorithms {
	a,
	ida,
	greedy
};

int astar(State *firstState, bool display);
int idastar(State *firstState, bool display);
int greedyastar(State *firstState, bool display);
