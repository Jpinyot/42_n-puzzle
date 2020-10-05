/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/05 23:03:39 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"
#include "iostream"

class OpenStack
{
    protected:
        State   *top_;
    
    public:
        OpenStack():
            top_(NULL)
        {;}

        OpenStack(State *top):
            top_(top)
        {;}

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

class UnsortedStack: public OpenStack
{
    public:
        UnsortedStack():
            OpenStack()
        {;}

        UnsortedStack(State *state):
            OpenStack(state)
        {;}

        ~UnsortedStack()
        {
            State *currState = top_;
            State *nextState;

            while (currState) {
                nextState = currState->getNext();
                delete currState;
                currState = nextState;
            }
        }

        void addState(State *state);
};
