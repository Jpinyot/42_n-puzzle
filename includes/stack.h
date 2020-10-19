/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/10/14 15:53:02 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"
#include "iostream"

class Stack
{
    protected:
        State   *top_;
    
    public:
        Stack():
            top_(NULL)
        {;}

        Stack(State *top):
            top_(top)
        {;}

        virtual ~Stack()
        {
            State *currState = top_;
            State *nextState;

            while (currState != NULL) {
                nextState = currState->getNext();
                delete currState;
                currState = nextState;
            }
        }

        virtual void    addState(State *state) = 0;
        State   *getTop() const {return top_;}
        
        void    popTop();
        void    display() const;
        const bool    stateIsOpen(State *state) const;
};

class OpenStack: public Stack
{
    public:
        OpenStack():
            Stack()
        {;}

        OpenStack(State *state):
            Stack(state)
        {;}

        ~OpenStack()
        {;}

        virtual void    addState(State *state);
};

class UnsortedStack: public Stack
{
    public:
        UnsortedStack():
            Stack()
        {;}

        UnsortedStack(State *state):
            Stack(state)
        {;}

        ~UnsortedStack()
        {;}

        virtual void addState(State *state);
};

class GreedyStack: public Stack
{
    public:
        GreedyStack():
            Stack()
        {;}

        GreedyStack(State *state):
            Stack(state)
        {;}

        ~GreedyStack()
        {;}

        virtual void    addState(State *state);
};
