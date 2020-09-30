/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closedStack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:19:24 by jpinyot           #+#    #+#             */
/*   Updated: 2020/09/28 18:34:43 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

const int k_maxScore = 80; //TODO: change to a real value :)

class ClosedStack
{
	private:
		vector<State *>	stack_;
	public:
		ClosedStack():
			stack_(k_maxScore, NULL)
		{;}

		bool	stateIsClosed(State& state);
		void	addState(State& state);
		/* void */	
};
