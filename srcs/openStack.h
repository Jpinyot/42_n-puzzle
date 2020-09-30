/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openStack.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfiguera <mfiguera@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 11:45:15 by mfiguera          #+#    #+#             */
/*   Updated: 2020/09/30 16:42:24 by mfiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "state.h"

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