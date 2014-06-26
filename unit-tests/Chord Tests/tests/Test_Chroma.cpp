#ifndef CHROMA_TESTS
#define CHROMA_TESTS

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "../../../src/Chromagram.h"
#include "Test_Signals.h"

//======================================================================
//==================== CHECKING INITIALISATION =========================
//======================================================================
BOOST_AUTO_TEST_SUITE(TestOnChords)

//======================================================================
BOOST_AUTO_TEST_CASE(CMajor441kHz)
{
    int frameSize = 1024;
    
    Chromagram c(frameSize,44100);
    
    std::vector<double> frame(frameSize);
    
    for (int i = 0;i < 8192;i = i + frameSize)
    {
        for (int k = 0;k < frameSize;k++)
        {
            frame[k] = C_Major_44_1[i+k];
        }
        
        c.processAudioFrame(frame);
        
        if (c.isReady())
        {
            std::vector<double> chroma = c.getChromagram();
            
            BOOST_CHECK(chroma[0] > chroma[1]);
            BOOST_CHECK(chroma[0] > chroma[2]);
            BOOST_CHECK(chroma[0] > chroma[3]);
            BOOST_CHECK(chroma[0] > chroma[5]);
            BOOST_CHECK(chroma[0] > chroma[6]);
            BOOST_CHECK(chroma[0] > chroma[8]);
            BOOST_CHECK(chroma[0] > chroma[9]);
            BOOST_CHECK(chroma[0] > chroma[10]);
            BOOST_CHECK(chroma[0] > chroma[11]);
            
            BOOST_CHECK(chroma[4] > chroma[1]);
            BOOST_CHECK(chroma[4] > chroma[2]);
            BOOST_CHECK(chroma[4] > chroma[3]);
            BOOST_CHECK(chroma[4] > chroma[5]);
            BOOST_CHECK(chroma[4] > chroma[6]);
            BOOST_CHECK(chroma[4] > chroma[8]);
            BOOST_CHECK(chroma[4] > chroma[9]);
            BOOST_CHECK(chroma[4] > chroma[10]);
            BOOST_CHECK(chroma[4] > chroma[11]);
            
            BOOST_CHECK(chroma[7] > chroma[1]);
            BOOST_CHECK(chroma[7] > chroma[2]);
            BOOST_CHECK(chroma[7] > chroma[3]);
            BOOST_CHECK(chroma[7] > chroma[5]);
            BOOST_CHECK(chroma[7] > chroma[6]);
            BOOST_CHECK(chroma[7] > chroma[8]);
            BOOST_CHECK(chroma[7] > chroma[9]);
            BOOST_CHECK(chroma[7] > chroma[10]);
            BOOST_CHECK(chroma[7] > chroma[11]);
        }
    }
}

//======================================================================
BOOST_AUTO_TEST_CASE(CMajor48kHz)
{
    int frameSize = 1024;
    
    Chromagram c(frameSize,48000);
    
    double frame[frameSize];
    
    for (int i = 0;i < 8192;i = i + frameSize)
    {
        for (int k = 0;k < frameSize;k++)
        {
            frame[k] = C_Major_48[i+k];
        }
        
        c.processAudioFrame(frame);
        
        if (c.isReady())
        {
            std::vector<double> chroma = c.getChromagram();
            
            BOOST_CHECK(chroma[0] > chroma[1]);
            BOOST_CHECK(chroma[0] > chroma[2]);
            BOOST_CHECK(chroma[0] > chroma[3]);
            BOOST_CHECK(chroma[0] > chroma[5]);
            BOOST_CHECK(chroma[0] > chroma[6]);
            BOOST_CHECK(chroma[0] > chroma[8]);
            BOOST_CHECK(chroma[0] > chroma[9]);
            BOOST_CHECK(chroma[0] > chroma[10]);
            BOOST_CHECK(chroma[0] > chroma[11]);
            
            BOOST_CHECK(chroma[4] > chroma[1]);
            BOOST_CHECK(chroma[4] > chroma[2]);
            BOOST_CHECK(chroma[4] > chroma[3]);
            BOOST_CHECK(chroma[4] > chroma[5]);
            BOOST_CHECK(chroma[4] > chroma[6]);
            BOOST_CHECK(chroma[4] > chroma[8]);
            BOOST_CHECK(chroma[4] > chroma[9]);
            BOOST_CHECK(chroma[4] > chroma[10]);
            BOOST_CHECK(chroma[4] > chroma[11]);
            
            BOOST_CHECK(chroma[7] > chroma[1]);
            BOOST_CHECK(chroma[7] > chroma[2]);
            BOOST_CHECK(chroma[7] > chroma[3]);
            BOOST_CHECK(chroma[7] > chroma[5]);
            BOOST_CHECK(chroma[7] > chroma[6]);
            BOOST_CHECK(chroma[7] > chroma[8]);
            BOOST_CHECK(chroma[7] > chroma[9]);
            BOOST_CHECK(chroma[7] > chroma[10]);
            BOOST_CHECK(chroma[7] > chroma[11]);
        }
    }

}

BOOST_AUTO_TEST_SUITE_END()
//======================================================================
//======================================================================

#endif
