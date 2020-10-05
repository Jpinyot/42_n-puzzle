/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/05 11:20:39 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"
#include "iostream"

class OpenStack
{
    private:
        State   *top_;
    
    public:
        OpenStack()
        {
            top_ = NULL;
        }

        ~OpenStack()
        {
            State *currState = top_;
            State *nextState;

            while (currState) {
                nextState = currState->getNext();
                delete currState;
                currState = nextState;
            }
        }

        void    addState(State *state);
        State   *getTop() const {return top_;}
        
        void    popTop();
        void    display() const;
        const bool    stateIsOpen(State *state) const;
};
