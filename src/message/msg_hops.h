#ifndef __MARS_MESSAGE_HOPS
#define __MARS_MESSAGE_HOPS

    /**
    * \file     msg_hops.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  2.0
    * \date     2017-01-25
    * \copyright
    *
    * This program is free software: you can redistribute it and/or modify
    * it under the terms of the GNU General Public License as published by
    * the Free Software Foundation, either version 3 of the License, or
    * (at your option) any later version.
    *
    * This program is distributed in the hope that it will be useful,
    * but WITHOUT ANY WARRANTY; without even the implied warranty of
    * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    * GNU General Public License for more details.
    * 
    * You should have received a copy of the GNU General Public License
    * along with this program.  If not, see <http://www.gnu.org/licenses/>.
    *
    */

    #include <stdlib.h>
    #include "../src/signal/hop.h"

    //! Message that contains hops
    typedef struct msg_hops_obj {

        unsigned long long timeStamp;       ///< Time stamp.

        hops_obj * hops;                    ///< List of hops.

    } msg_hops_obj;

    //! Configuration of the message that contains hops
    typedef struct msg_hops_cfg {

        unsigned int hopSize;               ///< Number of samples in a hop.
        unsigned int nMics;                 ///< Number of microphones.

    } msg_hops_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    msg_hops_obj * msg_hops_construct(const msg_hops_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void msg_hops_destroy(msg_hops_obj * obj);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */  
    msg_hops_cfg * msg_hops_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void msg_hops_cfg_destroy(msg_hops_cfg * cfg);

#endif