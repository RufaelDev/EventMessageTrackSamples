# EventMessageTrackSamples

ISO/IEC 23001-18 defines the Event Message Track format.

This format can be used the carry DASH Event Message in ISO-BMFF tracks.

This repository contains sample code for converting a list of DASH Event Messages based on ISO/IEC 23009-1 to 
Event Message Track Samples and track segments. 

The algorithm for conversion from clause 9.2 of ISO/IEC 23001-18
is implemented. This triggers a sample boundary at each time 
the set of active events changes.

The code is available under MIT license.

## find_event_samples.hpp 
Includes a function for converting a list of DASH Event Messages to 
Event Message Track samples output. Only detects sample boundaries and contents,
the function does not write any compliant output. The function takes 
segment start and end, allowing it to be used for generation of Event 
Message Track segments, i.e. detecting all samples and content between 
segment start and segment end.

Only the conceptual conversion from DASHEvents to samples is covered, 
this code does not write any MP4, DASH, ISO-BMFF 
compliant output. 

Libraries or code writing such compliant content may include the provided 
function to detect sample boundaries and contents and implement
the conversion required to implement the Event Message Track Format.

## generate_example.cpp
Small program to create examples of Event message track sample formatting. 

It prints random events to the std::out. 
Subsequently it prints the Event message track samples formatting.

Examples are for illustrative purpose.

## dashEventfmp4.cpp

Program for converting MPD events in an EventStream Element with optionally added attributes @startTime and @endTime

usage dashEventfmp4 in.mpd out_event_track.cmfm track_id target_segment_duration (0=entire track)

## fmp4DashEvent.cpp

Program for converting an event track back to XML format based on EventStream

usage fmp4DashEvent.cpp in_event_track.cmfm out.mpd

## unittest.cpp
Unit tests validation using catch framework https://github.com/catchorg/Catch2
