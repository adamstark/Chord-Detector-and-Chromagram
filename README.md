Chromagram Estimation & Chord Detection
=======================================

*by Adam Stark and Mark Plumbley.*

This is a C++ implementation of the chord recognition algorithm first described 
in the following conference paper:

* "Real-Time Chord Recognition For Live Performance", A. M. Stark and M. D. Plumbley. In Proceedings of the 2009 International Computer Music Conference (ICMC 2009), Montreal, Canada, 16-21 August 2009.

And expanded upon in Adam Stark's PhD Thesis:

* "Musicians and Machines: Bridging the Semantic Gap in Live Performance", A. M. Stark, PhD Thesis, Queen Mary, University of London, 2011.

Versions
--------

==== 1.0.6 ==== [21st November 2014]

* Moved to GitHub, no implementation changes

==== 1.0.1 ==== [26th June 2014]

* Added support for Kiss FFT as an alternative to FFTW

==== 1.0.0 ==== [14th June 2014]

* This is the re-implementation of the chromagram and chord detection code, circa 2014


License
-------

This code is made available under the GNU General Public License, version 3. Please see the included LICENSE.txt for more details.

Dependencies
------------

The Chromagram estimation code requires one of the following FFT libraries: 

* FFTW [add the flag -DUSE_FFTW]
* Kiss FFT [add the flag -DUSE_KISS_FFT]


Usage - Chromagram Estimation
-----------------------------

**STEP 1**

Include the Chromagram header file as follows:

	#include "Chromagram.h"
	
**STEP 2**

Instantiate the algorithm, specifying the audio frame size and sample rate:

	int frameSize = 512;
	int sampleRate = 44100;

	Chromagram c(frameSize,sampleRate); 

**STEP 3.1 - Audio Input Using An Array**

In the processing loop, fill a double precision array with one frame of audio samples: 

	double frame[frameSize]; 
	
	// !
	// do something here to fill the frame with audio samples
	// !

and then call:

	c.processAudioFrame(frame);
	

**STEP 3.2 - Audio Input Using Vectors**

In the processing loop, fill a double precsion vector with one frame of audio samples:

	std::vector<double> frame(frameSize); 
	
	// !
	// do something here to fill the frame with audio samples
	// !

and then call:

	c.processAudioFrame(frame);	


**STEP 4 - Getting The Chromagram**

The algorithm requires a fair bit of audio to calculate the chromagram, so calculating it at every audio frame of (for example) 512 samples may be unnecessary (and take up lots of CPU cycles).

After calling `processAudioFrame()` (see step 3), simply call:

	if (c.isReady())
	{
		std::vector<double> chroma = c.getChromagram();
		
		// do something with the chromagram here
	}
	
**NOTE - Setting Parameters**

You can set a number of parameters for the algorithm. These include...

The audio frame size:

	c.setInputAudioFrameSize(512);

The sampling frequency:

	c.setSamplingFrequency(44100);
	
The interval at which the chromagram is calculated (specified in audio samples at the sampling frequency that the algorithm has been initialised with - the default is 8192):

	c.setChromaCalculationInterval(8192);


Usage - Chord Detection
-----------------------

**STEP 1**

Include the ChordDetector header file as follows:

	#include "ChordDetector.h"

**STEP 2**

Instantiate the Chord Detector as follows:

	ChordDetector chordDetector;

**STEP 3**

Fill either a double precision array or vector of length 12 with chromagram values (perhaps estimated from audio, using the Chromagram class):

	double chroma[12]; // or std::vector<double> chroma(12);
	
	// !
	// fill with chromagram values here
	// !
	
Then call:

	chordDetector.detectChord(chroma);
	
**STEP 4**

You can then get the root note, chord quality (major, minor, etc) and any other intervals via...

	chordDetector.rootNote
    chordDetector.quality
    chordDetector.intervals
    
 
QUESTIONS?
----------

Visit:

http://www.adamstark.co.uk 

and send me an email. :)
	