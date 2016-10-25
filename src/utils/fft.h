#ifndef __MARS_UTILS_FFT
#define __MARS_UTILS_FFT

    #include <fftw3.h>
    #include <stdlib.h>

    /**
    * \file     fft.h
    * \author   François Grondin <francois.grondin2@usherbrooke.ca>
    * \version  1.0
    * \date     2016-10-25
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

    //! A structure that holds all the fields to perform forward and reverse Fast Fourier Transform. 
    typedef struct fft_obj {

        unsigned int frameSize;         ///< Number of samples in the real vector.		 
        unsigned int halfFrameSize;     ///< Number of samples in the complex vector.
        fftwf_plan R2C;                 ///< Internal structure for FFTW.
        fftwf_plan C2R;                 ///< Internal structure for FFTW.
        float * realArray;              ///< Real vector.
        fftwf_complex * complexArray;   ///< Complex vector.

    } fft_obj;

    /** Constructor of the FFT object.	
        \param      size    Size of the FFT.
        \return             Pointer to the instantiated object.
    */
    fft_obj * fft_construct(const unsigned int size);

    /** Destructor of the FFT object.
        \param      obj     Pointer to the object to be destroyed.
    */
    void fft_destroy(fft_obj * obj);

    /** Perform a FFT from real vector to complex vector.
        \param      obj     Pointer to the instantiated object.
        \param      in      Pointer to the array that contains input real samples (size = frameSize).
        \param      out     Pointer to the array that contains output complex samples (size = halfFrameSize).
    */
    void fft_r2c(fft_obj * obj, const float * in, float * out);

    /** Perform a inverse FFT from complex vector to real vector.
        \param      obj     Pointer to the instantiated object.
        \param      in      Pointer to the array that contains input complex samples (size = halfFrameSize).
        \param      out     Pointer to the array that contains output real samples (size = frameSize).
    */
    void fft_c2r(fft_obj * obj, const float * in, float * out);

#endif