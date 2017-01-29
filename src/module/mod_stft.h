#ifndef __MARS_MODULE_STFT
#define __MARS_MODULE_STFT

    /**
    * \file     mod_stft.h
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

    #include "../system/hop2frame.h"
    #include "../signal/frame.h"
    #include "../system/frame2freq.h"
    #include "../message/msg_hops.h"
    #include "../message/msg_spectra.h"

    //! Module to perform Short Time Fourier Transform (STFT)
    typedef struct mod_stft_obj {

        hop2frame_obj * hop2frame;                      ///< System to convert from hop to frame.
        frames_obj * frames;                            ///< List of frames.
        frame2freq_obj * frame2freq;                    ///< System to convert from frame to spectrum.

    } mod_stft_obj;

    //! Configuration of STFT
    typedef struct mod_stft_cfg {
        
        unsigned int nMics;                             ///< Number of microphones.
        unsigned int hopSize;                           ///< Number of samples per hop.
        unsigned int frameSize;                         ///< Number of samples per frame.

    } mod_stft_cfg;

   /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */ 
    mod_stft_obj * mod_stft_construct(const mod_stft_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mod_stft_destroy(mod_stft_obj * obj);

    /** Perform Sound Source Localization (SSL) and generate potential sources.
        \param      msg_hops        Message with the hops.
        \param      msg_spectra     Message with the spectra.
        \param      obj             Object to be used.
    */
    void mod_stft_process(mod_stft_obj * obj, const msg_hops_obj * msg_hops, msg_spectra_obj * msg_spectra);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */ 
    mod_stft_cfg * mod_stft_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void mod_stft_cfg_destroy(mod_stft_cfg * cfg);

#endif