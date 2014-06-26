//=======================================================================
/** @file ChordDetector.cpp
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

#include "ChordDetector.h"
#include <math.h>

//=======================================================================
ChordDetector::ChordDetector()
{
	bias = 1.06;
	
	makeChordProfiles();
		
}

//=======================================================================
void ChordDetector::detectChord(std::vector<double> chroma)
{
    detectChord(&chroma[0]);
}

//=======================================================================
void ChordDetector::detectChord(double *chroma)
{
	for (int i = 0;i < 12;i++)
	{
		chromagram[i] = chroma[i];
	}

	classifyChromagram();
}


//=======================================================================
void ChordDetector::classifyChromagram()
{
	int i;
	int j;
	int fifth;
	int chordindex;
	
	// remove some of the 5th note energy from chromagram
	for (i = 0;i < 12;i++)
	{
		fifth = (i+7) % 12;
		chromagram[fifth] = chromagram[fifth] - (0.1*chromagram[i]);
		
		if (chromagram[fifth] < 0)
		{
			chromagram[fifth] = 0;
		}
		
	}
	
	
	// major chords
	for (j=0;j < 12;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// minor chords
	for (j=12;j < 24;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// diminished 5th chords
	for (j=24;j < 36;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// augmented 5th chords
	for (j=36;j < 48;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// sus2 chords
	for (j=48;j < 60;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,3);
	}
	
	// sus4 chords
	for (j=60;j < 72;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,3);
	}
	
	// major 7th chords
	for (j=72;j < 84;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,4);
	}
	
	// minor 7th chords
	for (j=84;j < 96;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,4);
	}

	// dominant 7th chords
	for (j=96;j < 108;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,4);
	}
	
	chordindex = minimumIndex(chord,108);
	
	// major
	if (chordindex < 12)
	{
		rootNote = chordindex;
		quality = Major;
		intervals = 0;
	}
	
	// minor
	if ((chordindex >= 12) && (chordindex < 24))
	{
		rootNote = chordindex-12;
		quality = Minor;
		intervals = 0;
	}
	
	// diminished 5th
	if ((chordindex >= 24) && (chordindex < 36))
	{
		rootNote = chordindex-24;
		quality = Dimished5th;
		intervals = 0;
	}
	
	// augmented 5th
	if ((chordindex >= 36) && (chordindex < 48))
	{
		rootNote = chordindex-36;
		quality = Augmented5th;
		intervals = 0;
	}
	
	// sus2
	if ((chordindex >= 48) && (chordindex < 60))
	{
		rootNote = chordindex-48;
		quality = Suspended;
		intervals = 2;
	}
	
	// sus4
	if ((chordindex >= 60) && (chordindex < 72))
	{
		rootNote = chordindex-60;
		quality = Suspended;
		intervals = 4;
	}
	
	// major 7th
	if ((chordindex >= 72) && (chordindex < 84))
	{
		rootNote = chordindex-72;
		quality = Major;
		intervals = 7;
	}
	
	// minor 7th
	if ((chordindex >= 84) && (chordindex < 96))
	{
		rootNote = chordindex-84;
		quality = Minor;
		intervals = 7;
	}
	
	// dominant 7th
	if ((chordindex >= 96) && (chordindex < 108))
	{
		rootNote = chordindex-96;
		quality = Dominant;
		intervals = 7;
	}
}

//=======================================================================
double ChordDetector::calculateChordScore(double *chroma,double *chordProfile,double biasToUse, double N)
{
	double sum = 0;
	double delta;

	for (int i=0;i < 12;i++)
	{
		sum = sum + ((1-chordProfile[i])*(chroma[i]*chroma[i]));
	}

	delta = sqrt(sum) / ((12 - N)*biasToUse);
	
	return delta;
}

//=======================================================================
int ChordDetector::minimumIndex(double *array,int arrayLength)
{
	double minValue = 100000;
	int minIndex = 0;
	int i;
	
	for (i = 0;i < arrayLength;i++)
	{
		if (array[i] < minValue)
		{
			minValue = array[i];
			minIndex = i;
		}
	}
	
	return minIndex;
}

//=======================================================================
void ChordDetector::makeChordProfiles()
{
	int i;
	int t;
	int j = 0;
	int root;
	int third;
	int fifth;
	int seventh;
	
	double v1 = 1;
	double v2 = 1;
	double v3 = 1;
	
	// set profiles matrix to all zeros
	for (j = 0;j < 108;j++)
	{
		for (t = 0;t < 12;t++)
		{
			chordProfiles[j][t] = 0;
		}
	}
	
	// reset j to zero to begin creating profiles
	j = 0;
	
	// major chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}

	// minor chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}

	// diminished chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+6) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// augmented chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+8) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// sus2 chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+2) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}
	
	// sus4 chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+5) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}		
	
	// major 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		seventh = (i+11) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		
		j++;				
	}	
	
	// minor 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		seventh = (i+10) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		
		j++;				
	}
	
	// dominant 7th chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		seventh = (i+10) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		
		j++;				
	}
}