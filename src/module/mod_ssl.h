#ifndef __MARS_MODULE_SSL
#define __MARS_MODULE_SSL

    /**
    * \file     mod_ssl.h
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
    #include <string.h>

    #include "../signal/aimg.h"
    #include "../signal/mic.h"
    #include "../signal/freq.h"
    #include "../signal/xcorr.h"
    
    #include "../system/freq2freq.h"
    #include "../system/freq2xcorr.h"
    #include "../system/xcorr2aimg.h"
    #include "../system/xcorr2xcorr.h"

    #include "../init/scanning.h"

    #include "../message/msg_spectra.h"
    #include "../message/msg_pots.h"

    //! Module to perform sound source localization
    typedef struct mod_ssl_obj {

        unsigned int nMics;                 ///< Number of microphones.
        unsigned int nPairs;                ///< Number of pairs of microphones.
        unsigned int nPots;                 ///< Number of potential sources generated.
        unsigned int nScans;                ///< Number of scans (levels).

        scans_obj * scans;                  ///< List of scans to perform.

        unsigned int * deltasMax;           ///< List of deltas for the size of the maximum sliding window.
        unsigned int deltaReset;            ///< Delta for the size of the reset window.
        unsigned int r;                     ///< Counter of frames.
        unsigned int R;                     ///< Number of frames to wait to perform a new scan.

        freqs_obj * phasors;                ///< List of phasors.
        freqs_obj * products;               ///< List of products of frames for each pair of microphones.
        freqs_obj * smooths;                ///< List of smoothed products of frames for each pair of microphones.
        xcorrs_obj ** xcorrsReset;          ///< List of cross-correlations, where some have been reset to find many potential sources.
        xcorrs_obj *** xcorrsMax;           ///< List of cross-correlations, filtered with the sliding maximum window.
        aimg_obj *** aimgs;                 ///< List of acoustic images.

        freq2freq_obj * freq2freq;          ///< System to manipulate spectra.
        freq2xcorr_obj * freq2xcorr;        ///< System to convert spectra to cross-correlations.
        xcorr2xcorr_obj * xcorr2xcorr;      ///< System to manipulate cross-correlations.
        xcorr2aimg_obj ** xcorr2aimg;       ///< System to generate acoustic images.

        pots_obj * pots;                    ///< Potential sources generated.

    } mod_ssl_obj;

    //! Configuration of sound source localization
    typedef struct mod_ssl_cfg {

        mics_obj * mics;                    ///< List of microphones.
        unsigned int nPots;                 ///< Number of potential sources.
        unsigned int fS;                    ///< Sample rate (in samples/sec).
        float c;                            ///< Speed of sound (m/sec).
        unsigned int frameSize;             ///< Number of samples per frame.
        unsigned int nMatches;              ///< Number of matches with points between successive levels.
        float sigma;                        ///< Parameter \f$\sigma_\mathcal{V}\f$ when linking points in different levels.
        float epsilon;                      ///< Small value to avoid overflow.
        float alpha;                        ///< Adaptation rate to smooth cross-correlations.
        char * shape;                       ///< Shape to scan points ("sphere" or "halfsphere").
        unsigned int nLevels;               ///< Number of levels.
        unsigned int * levels;              ///< List of levels.
        unsigned int * deltasMax;           ///< List of deltas for the size of the maximum sliding window.
        unsigned int deltaReset;            ///< Delta for the size of the reset window.
        unsigned int R;                     ///< Number of frames to wait to perform a new scan.

    } mod_ssl_cfg;

    /** Constructor. Initialize all elements according to the configuration file.
        \param      cfg             Configuration.
        \return                     Pointer to the instantiated object.
    */  
    mod_ssl_obj * mod_ssl_construct(const mod_ssl_cfg * cfg);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void mod_ssl_destroy(mod_ssl_obj * obj);

    /** Perform Sound Source Localization (SSL) and generate potential sources.
        \param      msg_spectra     Message with the spectra.
        \param      msg_pots        Message with the potential sources.
        \param      obj             Object to be used.
    */
    void mod_ssl_process(mod_ssl_obj * obj, msg_spectra_obj * msg_spectra, msg_pots_obj * msg_pots);

    /** Constructor.
        \return                     Pointer to the instantiated object.
    */  
    mod_ssl_cfg * mod_ssl_cfg_construct(void);

    /** Destructor. Free memory.
        \param      cfg             Object to be destroyed.
    */
    void mod_ssl_cfg_destroy(mod_ssl_cfg * cfg);

#endif