/*******************************************************************************

Supplementary software media ingest specification:
https://github.com/unifiedstreaming/fmp4-ingest

Copyright (C) 2009-2021 CodeShop B.V.
http://www.code-shop.com

convert DASH Events in an XML file to a timed metadata track

******************************************************************************/

#include "fmp4stream.h"
#include "event_track.h"
#include "base64.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <algorithm>

using namespace fmp4_stream;
using namespace event_track;
extern std::string moov_64_enc;



/*
 generate an avail track based on 
        track duration (ms) 
		segment duration (ms) 
		avail duration (ms)
        avail frequency (ms)		
*/
int main(int argc, char *argv[])
{
	std::vector<event_track::DASHEventMessageBoxv1> events;
	
	std::string out_file_cmfm = "out_avail_track.cmfm";
	std::string out_file_mpd = "out_avail_track.mpd";
	
	uint32_t timescale = 1000;
	uint32_t track_duration = 0;
	uint32_t seg_duration_ticks_ms = 0; // segmentation duration 0 = entire track
	uint32_t avail_duration = 0; 
	uint32_t avail_interval = 0;
	uint32_t track_id = 99; // default track_id

	if (argc > 4){
		
	    track_duration  = atoi(argv[1]);
	    seg_duration_ticks_ms = atoi(argv[2]);
		avail_duration = atoi(argv[3]);
		avail_interval = atoi(argv[4]);
		
		
		uint32_t start_time = 0;
		uint32_t id_count = 0;
	    while(start_time < track_duration)
		{
		    event_track::DASHEventMessageBoxv1 ev;
			ev.id_= id_count++;
			ev.presentation_time_ = start_time; 
			ev.event_duration_ = avail_duration;
			ev.timescale_ = timescale; 
			ev.scheme_id_uri_ = "urn:scte:scte35:2013:bin"; 
			fmp4_stream::gen_splice_insert(ev.message_data_, ev.id_, ev.event_duration_ * 90);
			start_time+=avail_interval;
			events.push_back(ev);
		}
		
		event_track::write_to_segmented_event_track_file(
			     out_file_cmfm, events,
			     track_id, 0,  
			     track_duration, "test_urn", 
			     seg_duration_ticks_ms, timescale);

		std::cout << "wrote event track " << std::endl; 


		std::cout << "generating the MPD" << std::endl;
		std::ofstream ot = std::ofstream("out_avail_track.mpd");
		ot << "<EventStream " << std::endl;
		if (events[0].scheme_id_uri_.compare("urn:scte:scte35:2013:bin") == 0) // convert binary scte 214 to xml + bin
		{
			ot << "schemeIdUri=" << '"' << "urn:scte:scte35:2014:xml+bin" << '"' << std::endl;
		}
		else {
			ot << "schemeIdUri=" << '"' << events[0].scheme_id_uri_ << '"' << std::endl;
		}
		ot << " timescale=" << '"' << timescale << '"' << ">" << std::endl;

		// write each of the event messages as moof mdat combinations in sparse track 
		for (auto it2 = events.begin(); it2 != events.end(); it2++)
		{
			std::cout << " writing an event to output " << std::endl;
			ot << "<Event "
				<< "presentationTime=" << '"' << it2->presentation_time_ << '"' << " "  \
				<< "duration=" << '"' << it2->event_duration_ << '"' << " "  \
				<< "id=" << '"' << it2->id_ << '"';
			if (it2->scheme_id_uri_.compare("urn:scte:scte35:2013:bin") == 0) // write binary scte as xml + bin as defined by scte-35
			{
				ot << '>' << std::endl << "  <Signal xmlns=" << '"' << "http://www.scte.org/schemas/35/2016" << '"' << '>' << std::endl \
					<< "    <Binary>" << base64_encode(it2->message_data_.data(), (unsigned int)it2->message_data_.size()) << "</Binary>" << std::endl
					<< "  </Signal>" << std::endl;
			}
			else {
				ot << " " << "contentEncoding=" << '"' << "base64" << '"' << '>' << std::endl
					<< base64_encode(it2->message_data_.data(), (unsigned int)it2->message_data_.size()) << std::endl;
			}
			ot << "</Event>" << std::endl;
		}
		
		ot << "</EventStream> " << std::endl;
	    ot.close();

		return 0;
	}
	else
	{
		std::cout << " Tool for generating a splice insert avail track  " << std::endl;
		std::cout << "  splice insert commands in events in event message track / MPD " << std::endl;
		std::cout << " Format is under consideration for standardisation in MPEG as event message track " << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << " Usage: gen_avails track_duration[ms] segment_duration avail_duration[ms] avail_interval[ms]" << std::endl;
	}
}
