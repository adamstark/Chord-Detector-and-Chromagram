//=======================================================================
/** @file ChordDetector.h
 *  @brief ChordDetector - a class for estimating chord labels from chromagram input
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

#ifndef CHORDDETECT_H
#define CHORDDETECT_H

#include <vector>

//=======================================================================
/** A class for estimating chord labels from chromagram input */
class ChordDetector
{
public:
    
    /** An enum describing the chord qualities used in the algorithm */
    enum ChordQuality
    {
        Minor,
        Major,
        Suspended,
        Dominant,
        Dimished5th,
        Augmented5th,
    };
    
	/** Constructor */
	ChordDetector();
    
    /** Detects the chord from a chromagram. This is the vector interface 
     * @param chroma a vector of length 12 containing the chromagram
     */
    void detectChord(std::vector<double> chroma);
    
    /** Detects the chord from a chromagram. This is the array interface
     * @param chroma an array of length 12 containing the chromagram
     */
    void detectChord(double *chroma);
	
    /** The root note of the detected chord */
	int rootNote;
    
    /** The quality of the detected chord (Major, Minor, etc) */
	int quality;
    
    /** Any other intervals that describe the chord, e.g. 7th */
	int intervals;
	
private:
	void makeChordProfiles();

	void classifyChromagram();
	
	double calculateChordScore(double *chroma,double *chordProfile,double biasToUse, double N);

	int minimumIndex(double *array,int length);

	double chromagram[12];
	double chordProfiles[108][12];
	
	double chord[108];
	
	double bias;
};

#endif
