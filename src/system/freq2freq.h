#ifndef __MARS_SYSTEM_FREQ2FREQ
#define __MARS_SYSTEM_FREQ2FREQ

    /**
    * \file     freq2freq.h
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
    #include <math.h>
    #include "../utils/fifo.h"
    #include "../signal/freq.h"

    //! Convertor from frequency-domain frame to frequency-domain frame (phasor, phasor product and smoothed phasor product).
    typedef struct freq2freq_obj {

        unsigned int halfFrameSize;                 ///< Number of bins.
        float epsilon;                              ///< Small value to avoid overflow.
        float alpha;                                ///< Adaptation rate \f$\alpha_R\f$.

    } freq2freq_obj;

    /** Constructor. Initialize all fields to zero.
        \param      halfFrameSize   Number of bins per frame.
        \param      epsilon         Small value to avoid overflow.
        \param      alpha           Adaptation rate \f$\alpha_R\f$.
        \return                     Pointer to the instantiated object.
    */  
    freq2freq_obj * freq2freq_construct_zero(const unsigned int halfFrameSize, const float epsilon, const float alpha);

    /** Destructor. Free memory.
        \param      obj             Object to be destroyed.
    */
    void freq2freq_destroy(freq2freq_obj * obj);

    /** Compute phasor \f$\hat{X}^l_m[k] = X^l_m[k] / |X^l_m[k]|\f$.
        \param      freq            Frame in the frequency-domain.
        \param      phasor          Phasor in the frequency-domain.
        \param      obj             Object to be used.
    */
    void freq2freq_process_phasor_single(freq2freq_obj * obj, const freq_obj * freq, freq_obj * phasor);

    /** Compute product of phasors \f$R^l_{ij}[k] = \hat{X}^l_i[k]\hat{X}^l_j[k]^*\f$.
        \param      phasor1         Phasor 1.           
        \param      phasor2         Phasor 2.
        \param      phasor12        Product of phasors 1 and 2.
        \param      obj             Object to be used.
    */
    void freq2freq_process_product_single(freq2freq_obj * obj, const freq_obj * phasor1, const freq_obj * phasor2, freq_obj * phasor12);

    /** Smooth the phasor over time \f$\hat{R}^l_{ij}[k] = (1-\alpha_R)\hat{R}^{l-1}_{ij}[k] + \alpha_R R^l_{ij}[k]\f$.
        \param      phasor          Product of phasors.
        \param      smooth          Smoothed phasors.
        \param      obj             Object to be used.
    */
    void freq2freq_process_smooth_single(freq2freq_obj * obj, const freq_obj * phasor, freq_obj * smooth);

    /** Compute phasors \f$\hat{X}^l_m[k] = X^l_m[k] / |X^l_m[k]|\f$ for all \f$m\f$.
        \param      freqs           Frames in the frequency-domain.
        \param      phasors         Phasors in the frequency-domain.
        \param      obj             Object to be used.
    */
    void freq2freq_process_phasor_many(freq2freq_obj * obj, const freqs_obj * freqs, freqs_obj * phasors);

    /** Compute products of phasors \f$R^l_{ij}[k] = \hat{X}^l_i[k]\hat{X}^l_j[k]^*\f$ for all pairs \f$ij\f$.
        \param      phasors1        Phasors 1.           
        \param      phasors2        Phasors 2.
        \param      phasors12       Product of phasors 1 and 2.
        \param      obj             Object to be used.
    */
    void freq2freq_process_product_many(freq2freq_obj * obj, const freqs_obj * phasors1, const freqs_obj * phasors2, freqs_obj * phasors12);

    /** Smooth the phasors over time \f$\hat{R}^l_{ij}[k] = (1-\alpha_R)\hat{R}^{l-1}_{ij}[k] + \alpha_R R^l_{ij}[k]\f$ for all pairs \f$ij\f$.
        \param      phasors         Product of phasors.
        \param      smooths         Smoothed phasors.
        \param      obj             Object to be used.
    */
    void freq2freq_process_smooth_many(freq2freq_obj * obj, const freqs_obj * phasors, freqs_obj * smooths);


#endif