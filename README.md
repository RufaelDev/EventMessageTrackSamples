# EventMessageTrackSamples

ISO/IEC 23001-18 defines the Event Message Track format.

This repository contains sample code for converting a list of DASH Event Messages based on ISO/IEC 23009-1 to 
Event Message Track Samples. The algorithm for conversion in clause 9.2 ISO/IEC 23001-18
is implemented to trigger a sample boundary at each time the set of active events changes. 

The code is available under MIT license.

## find_event_samples.hpp 
Function for event message track samples generation

## generate_example.cpp
Small program to create examples of event message track samples formatting

## unittest.cpp
Unit tests validation using catch framework https://github.com/catchorg/Catch2
