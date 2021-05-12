# EventMessageTrackSamples

ISO/IEC 23001-18 defines the Event Message Track format.

This format can be used the carry DASH Event Message in ISO-BMFF tracks, both progressive and segmented.

This repository contains sample code for converting a list of DASH Event Messages based on ISO/IEC 23009-1 to 
Event Message Track Samples. 

The algorithm for conversion from clause 9.2 of ISO/IEC 23001-18
is implemented. This triggers a sample boundary at each time 
the set of active events changes.

Only the conceptial conversion from DASHEvents to samples is covered, 
this code does not write any MP4, DASH, ISO-BMFF 
compliant files. 

Libraries or code writing such compliant content may include the provided 
function to detect sample boundaries and contents and implement
the conversion.

The code is available under MIT license.

## find_event_samples.hpp 
Includes a function for converting a list of DASH Event Messages to 
Event Message Track formatting. Only detects sample boundaries and contents,
the function does not write any compliant output. The function takes 
segment start and end, allowing it to be used for generation of Event 
Message Track segments, i.e. detecting all samples and content between 
segment start and segment end.

## generate_example.cpp
Small program to create examples of Event message track samples formatting. 

It prints random events to the std::out. 
Subsequently it prints the Event message track samples formatting.

Examples are for illustrative purpose.

## unittest.cpp
Unit tests validation using catch framework https://github.com/catchorg/Catch2
