#ifndef CHORD_TESTS
#define CHORD_TESTS

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "../../../src/ChordDetector.h"

//======================================================================
//==================== CHECKING INITIALISATION =========================
//======================================================================
BOOST_AUTO_TEST_SUITE(SimpleChords)

//======================================================================
BOOST_AUTO_TEST_CASE(CMajor)
{
    ChordDetector chordDetector;
    
    double chroma[12] = {1,0,0,0,1,0,0,1,0,0,0,0};
    
    chordDetector.detectChord(chroma);
    
    BOOST_CHECK_EQUAL(chordDetector.rootNote, 0);
    BOOST_CHECK_EQUAL(chordDetector.quality, ChordDetector::Major);
    BOOST_CHECK_EQUAL(chordDetector.intervals, 0);
}

//======================================================================
BOOST_AUTO_TEST_CASE(CMinor)
{
    ChordDetector chordDetector;
    
    double chroma[12] = {1,0,0,1,0,0,0,1,0,0,0,0};
    
    chordDetector.detectChord(chroma);
    
    BOOST_CHECK_EQUAL(chordDetector.rootNote, 0);
    BOOST_CHECK_EQUAL(chordDetector.quality, ChordDetector::Minor);
    BOOST_CHECK_EQUAL(chordDetector.intervals, 0);
}

BOOST_AUTO_TEST_SUITE_END()
//======================================================================
//======================================================================

#endif
