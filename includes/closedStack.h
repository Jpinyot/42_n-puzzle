/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closedStack.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:19:24 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/02 11:13:27 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

const int k_maxScore = 80; //TODO: change to a real value :)

class ClosedStack
{
	private:
		vector<State *>	stack_; //TODO: try list instead of vector
	public:
		ClosedStack():
			stack_(k_maxScore, NULL)
		{;}

		const bool	stateIsClosed(State* state) const;
		void		addState(State* state);
		/* void */	
};
