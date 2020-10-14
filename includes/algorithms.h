/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:05:42 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/14 16:26:58 by mfiguera         ###   ########.fr       */
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

int astar(State *firstState);
int idastar(State *firstState);
int greedyastar(State *firstState);
