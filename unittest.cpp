/*
    unittest find_event_samples.hpp
	
    All Rights Reserved CodeShop B.V. 2021 - 
*/
#include "find_event_samples.hpp"
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

using namespace event_track;


TEST_CASE("test with randomly generated events]") {

	std::vector<DASHEventMessageBoxv1> emsgs_in;
	uint64_t segment_start_time = 0;
	uint64_t segment_end_time = 200;

	for (int i = 0; i < 50; i++)
	{
		DASHEventMessageBoxv1 e = generate_random_event();

		if (i % 5 == 0)  // insert some events with zero duration
			e = generate_random_event(true);

		if (i % 19 == 0) // introduce indefinete duration event
			e.event_duration = 0xFFFFFFFF; 

		e.id = (unsigned int)i;
		emsgs_in.push_back(e);
	}

	std::vector<EventSample> samples;
	find_event_samples(emsgs_in, samples, segment_start_time, segment_end_time);

	SECTION("test that all track timing match stored event time")
	{
		for(unsigned int i=0; i < samples.size();i++)
			
			for (unsigned int j = 0; j < samples[i].instance_boxes.size(); j++) 
			{
				// check sample presentation and (stored) event presentation times match
				uint64_t dt = samples[i].sample_presentation_time + samples[i].instance_boxes[j].presentation_time_delta;
				uint64_t st = (uint64_t)samples[i].instance_boxes[j].message_data[0];
				
				if (dt < 256)
					REQUIRE(st == dt);

				// check that the duration of a 0 duration event is enclosed in a sample with a single tick
				uint32_t dur_e =  samples[i].instance_boxes[j].event_duration;
				uint32_t dur_s = samples[i].sample_duration;
				
				if (dur_e == 0)
					REQUIRE(dur_s == 1);
			}
	}

	SECTION("test that all active events are stored in samples overlapping the active events")
	{
		// for each event check that it is stored in overlapping samples
		for (unsigned int i = 0; i < emsgs_in.size(); i++)
			for (unsigned int j = 0; j < samples.size(); j++)
			{
			   int64_t s_t = samples[j].sample_presentation_time;
			   int64_t s_td =samples[j].sample_duration + s_t;

			   int64_t e_t = emsgs_in[i].presentation_time;
			   int64_t e_td = emsgs_in[i].presentation_time + emsgs_in[i].event_duration;
			   if (emsgs_in[i].event_duration == 0)
				   e_td += 1;
			   int32_t l_id = emsgs_in[i].id;

			   // overlapping means event starts at least before sample end 
			   // event ends at least after sample start
			   if (e_t < s_td && e_td > s_t) {
				   // overlapping
				   bool id_found = false;
				   for (int k = 0; k < samples[j].instance_boxes.size(); k++)
				   {
					   if (samples[j].instance_boxes[k].id == l_id)
						   id_found = true;
				   }
				   REQUIRE(id_found);
			   }
			}
	}

	SECTION("test that there are no events ending or starting without a samples boundary")
	{
		for (unsigned int j = 0; j < samples.size(); j++)
		{
			int64_t sp = samples[j].sample_presentation_time;
			int64_t sp_d = samples[j].sample_presentation_time + samples[j].sample_duration;

			for (int k = 0; k < samples[j].instance_boxes.size(); k++)
			{
				int64_t e_t = samples[j].sample_presentation_time + samples[j].instance_boxes[k].presentation_time_delta;
				int64_t e_d = samples[j].instance_boxes[k].event_duration;

				if (e_d = 0)
					e_d += 1;

                // event cannot end in the sample
				bool ends_out_sample = (e_t + e_d >= sp_d) || (e_t + e_d <= sp);
				REQUIRE(ends_out_sample);

				// event cannot start after start of sample
				bool starts_out_of_sample_bounds = (e_t <= sp) || (e_t >= sp_d);
				REQUIRE(starts_out_of_sample_bounds);
					
			}
		}
	}

	SECTION("check that the sample timeline is continuous and starts and ends")
	{
		int64_t last_time = -1;

		REQUIRE(samples[0].sample_presentation_time == segment_start_time);
		size_t last_index = samples.size() - 1;
		REQUIRE(samples[last_index].sample_presentation_time + samples[last_index].sample_duration== segment_end_time);

		for (unsigned int j = 0; j < samples.size(); j++)
		{
			int64_t sp = samples[j].sample_presentation_time;
			int64_t sp_d = samples[j].sample_presentation_time + samples[j].sample_duration;
			if (last_time != -1)
			{
				REQUIRE(last_time == sp);
			}
			last_time = sp_d;
		}
	}
}