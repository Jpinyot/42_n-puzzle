/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 17:27:26 by jpinyot          ###   ########.fr       */
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

        void    addState(State &state);
        State   *getTop() {return top_;}
        
        void    popTop();
        void    display();
};
