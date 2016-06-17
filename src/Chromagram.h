//=======================================================================
/** @file Chromagram.h
 *  @brief Chromagram - a class for calculating the chromagram in real-time
 *  @author Adam Stark
 *  @copyright Copyright (C) 2008-2014  Queen Mary University of London
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
 */
//=======================================================================

#ifndef __CHROMAGRAM_H
#define __CHROMAGRAM_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#ifdef USE_FFTW
#include "fftw3.h"
#endif

#ifdef USE_KISS_FFT
#include "kiss_fft.h"
#endif

//=======================================================================
/** A class for calculating a Chromagram from input audio
 * in a real-time context */
class Chromagram
{
    
public:
    /** Constructor
     * @param frameSize the input audio frame size 
     * @param fs the sampling frequency
     */
    Chromagram (int frameSize, int fs);

    /** Destructor */
    ~Chromagram();
    
    /** Process a single audio frame. This will determine whether enough samples
     * have been accumulated and if so, will calculate the chromagram
     * @param inputAudioFrame an array containing the input audio frame. This should be
     * the length indicated by the input audio frame size passed to the constructor
     * @see setInputAudioFrameSize
     */
    void processAudioFrame (double* inputAudioFrame);
    
    /** Process a single audio frame. This will determine whether enough samples
     * have been accumulated and if so, will calculate the chromagram
     * @param inputAudioFrame a vector containing the input audio frame. This should be
     * the length indicated by the input audio frame size passed to the constructor
     * @see setInputAudioFrameSize
     */
    void processAudioFrame (std::vector<double> inputAudioFrame);
    
    /** Sets the input audio frame size
     * @param frameSize the input audio frame size
     */
    void setInputAudioFrameSize (int frameSize);
    
    /** Set the sampling frequency of the input audio
     * @param fs the sampling frequency in Hz
     */
    void setSamplingFrequency (int fs);
    
    /** Set the interval at which the chromagram is calculated. As the algorithm requires
     * a significant amount of audio to be accumulated, it may be desirable to have the algorithm
     * not calculate the chromagram at every new audio frame. This function allows you to set the 
     * interval at which the chromagram will be calculated, specified in the number of samples at
     * the audio sampling frequency 
     * @param numSamples the number of samples that the algorithm will receive before calculating a new chromagram
     */
    void setChromaCalculationInterval (int numSamples);
    
    /** @returns the chromagram vector */
    std::vector<double> getChromagram();
    
    /** @returns true if a new chromagram vector has been calculated at the current iteration. This should
     * be called after processAudioFrame
     */
    bool isReady();
    
private:
    
    void setupFFT();
    void calculateChromagram();
    void calculateMagnitudeSpectrum();
	void downSampleFrame (std::vector<double> inputAudioFrame);
    void makeHammingWindow();
    double round (double val);
    
    std::vector<double> window;
    std::vector<double> buffer;
    std::vector<double> magnitudeSpectrum;
    std::vector<double> downsampledInputAudioFrame;
    std::vector<double> chromagram;
    
    double referenceFrequency;
    double noteFrequencies[12];
    
    int bufferSize;
    int samplingFrequency;
    int inputAudioFrameSize;
    int downSampledAudioFrameSize;
    int numHarmonics;
	int numOctaves;
	int numBinsToSearch;
    int numSamplesSinceLastCalculation;
    int chromaCalculationInterval;
    bool chromaReady;

#ifdef USE_FFTW
    fftw_plan p;
	fftw_complex* complexOut;
    fftw_complex* complexIn;
#endif
    
#ifdef USE_KISS_FFT
    kiss_fft_cfg cfg;
    kiss_fft_cpx* fftIn;
    kiss_fft_cpx* fftOut;
#endif
    
};

#endif /* defined(__CHROMAGRAM_H) */
