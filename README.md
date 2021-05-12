# EventMessageTrackSamples

ISO/IEC 23001-18 defines the Event Message Track format.

This repository contains sample code for converting a list of DASH Event Messages based on ISO/IEC 23009-1 to 
Event Message Track Samples. 

The algorithm for conversion in clause 9.2 ISO/IEC 23001-18
is implemented to trigger a sample boundary at each time 
the set of active events changes.

A program to generate a textual example is included using random input. 

Only the conceptial conversion from DASHEvents to samples is covered, 
this code does not write any MP4, DASH, ISOBM-FF 
compliant files. 

Libraries or code writing such files may include the provided 
function to detect sample boundaries and contents and implement
the conversion.

The code is available under MIT license.

## find_event_samples.hpp 
Function for converting a list of DASH Event Messages to 
Event Message Track formatting. Only detects sample boundaries and contents,
the function does not write any compliant output.

## generate_example.cpp
Small program to create examples of Event message track samples formatting. 

It prints random events to the std::out. 
Subsequently it prints the Event message track samples formatting.

Examples are for illustrative purpose.

## unittest.cpp
Unit tests validation using catch framework https://github.com/catchorg/Catch2
