#ifndef __MARS_MESSAGE_SPECTRA
#define __MARS_MESSAGE_SPECTRA

    /**
    * \file     msg_spectra.h
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

    #include "../signal/freq.h"

    //! Message that contains the spectra of signals
    typedef struct msg_spectra_obj {

        unsigned long long timeStamp;           ///< Time stamp.

        freqs_obj * freqs;                      ///< List of spectra.

    } msg_spectra_obj;

    //! Configuration of the message that contains the spectra of signals
    typedef struct msg_spectra_cfg {

        unsigned int frameSize;                 ///< Number of samples in a frame in the time-domain.
        unsigned int nMics;                     ///< Number of microphones.

    } msg_spectra_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    msg_spectra_obj * msg_spectra_construct(const msg_spectra_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void msg_spectra_destroy(msg_spectra_obj * obj);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */ 
    msg_spectra_cfg * msg_spectra_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void msg_spectra_cfg_destroy(msg_spectra_cfg * cfg);

#endif