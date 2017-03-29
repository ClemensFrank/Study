
#include "ControllerStateChart.h"
#include <string.h>

/*! \file Implementation of the state machine 'ControllerStateChart'
*/

ControllerStateChart::ControllerStateChart()
{
	
	ifaceInternalSCI_OCB = null;
	
	stateConfVectorPosition = 0;
	
	timer = null;
}

ControllerStateChart::~ControllerStateChart()
{
}


void ControllerStateChart::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = ControllerStateChart_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
	/* Default init sequence for statechart ControllerStateChart */
	ifaceInternalSCI.song = 0;
	ifaceInternalSCI.songsCount = 5;
	ifaceInternalSCI.vol = 0;
	ifaceInternalSCI.playing = false;
}

void ControllerStateChart::enter()
{
	/* Default enter sequence for statechart ControllerStateChart */
	enseq_main_region_default();
}

void ControllerStateChart::exit()
{
	/* Default exit sequence for statechart ControllerStateChart */
	exseq_main_region();
}

sc_boolean ControllerStateChart::isActive()
{
	return stateConfVector[0] != ControllerStateChart_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean ControllerStateChart::isFinal()
{
   return false;}

void ControllerStateChart::runCycle()
{
	
	clearOutEvents();
	
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++)
		{
			
		switch (stateConfVector[stateConfVectorPosition])
		{
		case main_region_idle :
		{
			react_main_region_idle();
			break;
		}
		case main_region_right_trigger :
		{
			react_main_region_right_trigger();
			break;
		}
		case main_region_left_trigger :
		{
			react_main_region_left_trigger();
			break;
		}
		case main_region_left_triggered :
		{
			react_main_region_left_triggered();
			break;
		}
		case main_region_right_triggered :
		{
			react_main_region_right_triggered();
			break;
		}
		case main_region_changing_Volume :
		{
			react_main_region_changing_Volume();
			break;
		}
		case main_region_pausing :
		{
			react_main_region_pausing();
			break;
		}
		case main_region_nextSong :
		{
			react_main_region_nextSong();
			break;
		}
		case main_region_previousSong :
		{
			react_main_region_previousSong();
			break;
		}
		case main_region_dynamicVolume :
		{
			react_main_region_dynamicVolume();
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents();
}

void ControllerStateChart::clearInEvents()
{
	ifaceInternalSCI.right_raised = false; 
	ifaceInternalSCI.left_raised = false; 
	ifaceInternalSCI.no_right_raised = false; 
	ifaceInternalSCI.no_left_raised = false; 
	timeEvents[0] = false; 
	timeEvents[1] = false; 
	timeEvents[2] = false; 
	timeEvents[3] = false; 
}

void ControllerStateChart::clearOutEvents()
{
}


void ControllerStateChart::setTimer(TimerInterface* timer)
{
	this->timer = timer;
}

TimerInterface* ControllerStateChart::getTimer()
{
	return timer;
}

void ControllerStateChart::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		*(sc_boolean*)evid = true;
	}				
}

sc_boolean ControllerStateChart::isStateActive(ControllerStateChartStates state)
{
	switch (state)
	{
		case main_region_idle : 
			return (sc_boolean) (stateConfVector[0] == main_region_idle
			);
		case main_region_right_trigger : 
			return (sc_boolean) (stateConfVector[0] == main_region_right_trigger
			);
		case main_region_left_trigger : 
			return (sc_boolean) (stateConfVector[0] == main_region_left_trigger
			);
		case main_region_left_triggered : 
			return (sc_boolean) (stateConfVector[0] == main_region_left_triggered
			);
		case main_region_right_triggered : 
			return (sc_boolean) (stateConfVector[0] == main_region_right_triggered
			);
		case main_region_changing_Volume : 
			return (sc_boolean) (stateConfVector[0] == main_region_changing_Volume
			);
		case main_region_pausing : 
			return (sc_boolean) (stateConfVector[0] == main_region_pausing
			);
		case main_region_nextSong : 
			return (sc_boolean) (stateConfVector[0] == main_region_nextSong
			);
		case main_region_previousSong : 
			return (sc_boolean) (stateConfVector[0] == main_region_previousSong
			);
		case main_region_dynamicVolume : 
			return (sc_boolean) (stateConfVector[0] == main_region_dynamicVolume
			);
		default: return false;
	}
}

ControllerStateChart::DefaultSCI* ControllerStateChart::getDefaultSCI()
{
	return &iface;
}



void ControllerStateChart::InternalSCI::raise_right()
{
	right_raised = true;
}

sc_boolean ControllerStateChart::InternalSCI::isRaised_right()
{
	return right_raised;
}

void ControllerStateChart::InternalSCI::raise_left()
{
	left_raised = true;
}

sc_boolean ControllerStateChart::InternalSCI::isRaised_left()
{
	return left_raised;
}

void ControllerStateChart::InternalSCI::raise_no_right()
{
	no_right_raised = true;
}

sc_boolean ControllerStateChart::InternalSCI::isRaised_no_right()
{
	return no_right_raised;
}

void ControllerStateChart::InternalSCI::raise_no_left()
{
	no_left_raised = true;
}

sc_boolean ControllerStateChart::InternalSCI::isRaised_no_left()
{
	return no_left_raised;
}

int32_t ControllerStateChart::InternalSCI::get_song()
{
	return song;
}

void ControllerStateChart::InternalSCI::set_song(int32_t value)
{
	song = value;
}

int32_t ControllerStateChart::InternalSCI::get_songsCount()
{
	return songsCount;
}

void ControllerStateChart::InternalSCI::set_songsCount(int32_t value)
{
	songsCount = value;
}

int32_t ControllerStateChart::InternalSCI::get_vol()
{
	return vol;
}

void ControllerStateChart::InternalSCI::set_vol(int32_t value)
{
	vol = value;
}

sc_boolean ControllerStateChart::InternalSCI::get_playing()
{
	return playing;
}

void ControllerStateChart::InternalSCI::set_playing(sc_boolean value)
{
	playing = value;
}

void ControllerStateChart::setInternalSCI_OCB(InternalSCI_OCB* operationCallback)
{
	ifaceInternalSCI_OCB = operationCallback;
}

// implementations of all internal functions

sc_boolean ControllerStateChart::check_main_region_idle_tr0_tr0()
{
	return ifaceInternalSCI.right_raised;
}

sc_boolean ControllerStateChart::check_main_region_idle_tr1_tr1()
{
	return ifaceInternalSCI.left_raised;
}

sc_boolean ControllerStateChart::check_main_region_right_trigger_tr0_tr0()
{
	return ifaceInternalSCI.no_right_raised;
}

sc_boolean ControllerStateChart::check_main_region_left_trigger_tr0_tr0()
{
	return timeEvents[0];
}

sc_boolean ControllerStateChart::check_main_region_left_trigger_tr1_tr1()
{
	return ifaceInternalSCI.right_raised;
}

sc_boolean ControllerStateChart::check_main_region_left_triggered_tr0_tr0()
{
	return ifaceInternalSCI.no_left_raised;
}

sc_boolean ControllerStateChart::check_main_region_left_triggered_tr1_tr1()
{
	return timeEvents[1];
}

sc_boolean ControllerStateChart::check_main_region_right_triggered_tr0_tr0()
{
	return timeEvents[2];
}

sc_boolean ControllerStateChart::check_main_region_right_triggered_tr1_tr1()
{
	return ifaceInternalSCI.left_raised;
}

sc_boolean ControllerStateChart::check_main_region_changing_Volume_tr0_tr0()
{
	return true;
}

sc_boolean ControllerStateChart::check_main_region_pausing_tr0_tr0()
{
	return true;
}

sc_boolean ControllerStateChart::check_main_region_nextSong_tr0_tr0()
{
	return ifaceInternalSCI.no_left_raised;
}

sc_boolean ControllerStateChart::check_main_region_nextSong_tr1_tr1()
{
	return timeEvents[3];
}

sc_boolean ControllerStateChart::check_main_region_previousSong_tr0_tr0()
{
	return ifaceInternalSCI.no_right_raised;
}

sc_boolean ControllerStateChart::check_main_region_dynamicVolume_tr0_tr0()
{
	return ifaceInternalSCI.no_left_raised;
}

void ControllerStateChart::effect_main_region_idle_tr0()
{
	exseq_main_region_idle();
	enseq_main_region_right_trigger_default();
}

void ControllerStateChart::effect_main_region_idle_tr1()
{
	exseq_main_region_idle();
	enseq_main_region_left_triggered_default();
}

void ControllerStateChart::effect_main_region_right_trigger_tr0()
{
	exseq_main_region_right_trigger();
	enseq_main_region_right_triggered_default();
}

void ControllerStateChart::effect_main_region_left_trigger_tr0()
{
	exseq_main_region_left_trigger();
	enseq_main_region_changing_Volume_default();
}

void ControllerStateChart::effect_main_region_left_trigger_tr1()
{
	exseq_main_region_left_trigger();
	enseq_main_region_previousSong_default();
}

void ControllerStateChart::effect_main_region_left_triggered_tr0()
{
	exseq_main_region_left_triggered();
	enseq_main_region_left_trigger_default();
}

void ControllerStateChart::effect_main_region_left_triggered_tr1()
{
	exseq_main_region_left_triggered();
	enseq_main_region_dynamicVolume_default();
}

void ControllerStateChart::effect_main_region_right_triggered_tr0()
{
	exseq_main_region_right_triggered();
	enseq_main_region_pausing_default();
}

void ControllerStateChart::effect_main_region_right_triggered_tr1()
{
	exseq_main_region_right_triggered();
	enseq_main_region_nextSong_default();
}

void ControllerStateChart::effect_main_region_changing_Volume_tr0()
{
	exseq_main_region_changing_Volume();
	enseq_main_region_idle_default();
}

void ControllerStateChart::effect_main_region_pausing_tr0()
{
	exseq_main_region_pausing();
	enseq_main_region_idle_default();
}

void ControllerStateChart::effect_main_region_nextSong_tr0()
{
	exseq_main_region_nextSong();
	enseq_main_region_idle_default();
}

void ControllerStateChart::effect_main_region_nextSong_tr1()
{
	exseq_main_region_nextSong();
	enseq_main_region_nextSong_default();
}

void ControllerStateChart::effect_main_region_previousSong_tr0()
{
	exseq_main_region_previousSong();
	enseq_main_region_idle_default();
}

void ControllerStateChart::effect_main_region_dynamicVolume_tr0()
{
	exseq_main_region_dynamicVolume();
	enseq_main_region_left_trigger_default();
}

/* Entry action for state 'left_trigger'. */
void ControllerStateChart::enact_main_region_left_trigger()
{
	/* Entry action for state 'left_trigger'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[0]), 500, false);
}

/* Entry action for state 'left_triggered'. */
void ControllerStateChart::enact_main_region_left_triggered()
{
	/* Entry action for state 'left_triggered'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[1]), 1 * 1000, false);
}

/* Entry action for state 'right_triggered'. */
void ControllerStateChart::enact_main_region_right_triggered()
{
	/* Entry action for state 'right_triggered'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[2]), 500, false);
}

/* Entry action for state 'pausing'. */
void ControllerStateChart::enact_main_region_pausing()
{
	/* Entry action for state 'pausing'. */
	ifaceInternalSCI_OCB->changePlaystate();
}

/* Entry action for state 'nextSong'. */
void ControllerStateChart::enact_main_region_nextSong()
{
	/* Entry action for state 'nextSong'. */
	timer->setTimer(this, (sc_eventid)(&timeEvents[3]), 500, false);
	ifaceInternalSCI.song += 1;
	ifaceInternalSCI.song = ifaceInternalSCI.song % ifaceInternalSCI.songsCount;
}

/* Entry action for state 'previousSong'. */
void ControllerStateChart::enact_main_region_previousSong()
{
	/* Entry action for state 'previousSong'. */
	ifaceInternalSCI.song -= 1;
	ifaceInternalSCI.song = ifaceInternalSCI.song % ifaceInternalSCI.songsCount;
}

/* Exit action for state 'left_trigger'. */
void ControllerStateChart::exact_main_region_left_trigger()
{
	/* Exit action for state 'left_trigger'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* Exit action for state 'left_triggered'. */
void ControllerStateChart::exact_main_region_left_triggered()
{
	/* Exit action for state 'left_triggered'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[1]));
}

/* Exit action for state 'right_triggered'. */
void ControllerStateChart::exact_main_region_right_triggered()
{
	/* Exit action for state 'right_triggered'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[2]));
}

/* Exit action for state 'nextSong'. */
void ControllerStateChart::exact_main_region_nextSong()
{
	/* Exit action for state 'nextSong'. */
	timer->unsetTimer(this, (sc_eventid)(&timeEvents[3]));
}

/* 'default' enter sequence for state idle */
void ControllerStateChart::enseq_main_region_idle_default()
{
	/* 'default' enter sequence for state idle */
	stateConfVector[0] = main_region_idle;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state right_trigger */
void ControllerStateChart::enseq_main_region_right_trigger_default()
{
	/* 'default' enter sequence for state right_trigger */
	stateConfVector[0] = main_region_right_trigger;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state left_trigger */
void ControllerStateChart::enseq_main_region_left_trigger_default()
{
	/* 'default' enter sequence for state left_trigger */
	enact_main_region_left_trigger();
	stateConfVector[0] = main_region_left_trigger;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state left_triggered */
void ControllerStateChart::enseq_main_region_left_triggered_default()
{
	/* 'default' enter sequence for state left_triggered */
	enact_main_region_left_triggered();
	stateConfVector[0] = main_region_left_triggered;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state right_triggered */
void ControllerStateChart::enseq_main_region_right_triggered_default()
{
	/* 'default' enter sequence for state right_triggered */
	enact_main_region_right_triggered();
	stateConfVector[0] = main_region_right_triggered;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state changing_Volume */
void ControllerStateChart::enseq_main_region_changing_Volume_default()
{
	/* 'default' enter sequence for state changing_Volume */
	stateConfVector[0] = main_region_changing_Volume;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state pausing */
void ControllerStateChart::enseq_main_region_pausing_default()
{
	/* 'default' enter sequence for state pausing */
	enact_main_region_pausing();
	stateConfVector[0] = main_region_pausing;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state nextSong */
void ControllerStateChart::enseq_main_region_nextSong_default()
{
	/* 'default' enter sequence for state nextSong */
	enact_main_region_nextSong();
	stateConfVector[0] = main_region_nextSong;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state previousSong */
void ControllerStateChart::enseq_main_region_previousSong_default()
{
	/* 'default' enter sequence for state previousSong */
	enact_main_region_previousSong();
	stateConfVector[0] = main_region_previousSong;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state dynamicVolume */
void ControllerStateChart::enseq_main_region_dynamicVolume_default()
{
	/* 'default' enter sequence for state dynamicVolume */
	stateConfVector[0] = main_region_dynamicVolume;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void ControllerStateChart::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state idle */
void ControllerStateChart::exseq_main_region_idle()
{
	/* Default exit sequence for state idle */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state right_trigger */
void ControllerStateChart::exseq_main_region_right_trigger()
{
	/* Default exit sequence for state right_trigger */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state left_trigger */
void ControllerStateChart::exseq_main_region_left_trigger()
{
	/* Default exit sequence for state left_trigger */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_left_trigger();
}

/* Default exit sequence for state left_triggered */
void ControllerStateChart::exseq_main_region_left_triggered()
{
	/* Default exit sequence for state left_triggered */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_left_triggered();
}

/* Default exit sequence for state right_triggered */
void ControllerStateChart::exseq_main_region_right_triggered()
{
	/* Default exit sequence for state right_triggered */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_right_triggered();
}

/* Default exit sequence for state changing_Volume */
void ControllerStateChart::exseq_main_region_changing_Volume()
{
	/* Default exit sequence for state changing_Volume */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state pausing */
void ControllerStateChart::exseq_main_region_pausing()
{
	/* Default exit sequence for state pausing */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state nextSong */
void ControllerStateChart::exseq_main_region_nextSong()
{
	/* Default exit sequence for state nextSong */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
	exact_main_region_nextSong();
}

/* Default exit sequence for state previousSong */
void ControllerStateChart::exseq_main_region_previousSong()
{
	/* Default exit sequence for state previousSong */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state dynamicVolume */
void ControllerStateChart::exseq_main_region_dynamicVolume()
{
	/* Default exit sequence for state dynamicVolume */
	stateConfVector[0] = ControllerStateChart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void ControllerStateChart::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of ControllerStateChart.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_idle :
		{
			exseq_main_region_idle();
			break;
		}
		case main_region_right_trigger :
		{
			exseq_main_region_right_trigger();
			break;
		}
		case main_region_left_trigger :
		{
			exseq_main_region_left_trigger();
			break;
		}
		case main_region_left_triggered :
		{
			exseq_main_region_left_triggered();
			break;
		}
		case main_region_right_triggered :
		{
			exseq_main_region_right_triggered();
			break;
		}
		case main_region_changing_Volume :
		{
			exseq_main_region_changing_Volume();
			break;
		}
		case main_region_pausing :
		{
			exseq_main_region_pausing();
			break;
		}
		case main_region_nextSong :
		{
			exseq_main_region_nextSong();
			break;
		}
		case main_region_previousSong :
		{
			exseq_main_region_previousSong();
			break;
		}
		case main_region_dynamicVolume :
		{
			exseq_main_region_dynamicVolume();
			break;
		}
		default: break;
	}
}

/* The reactions of state idle. */
void ControllerStateChart::react_main_region_idle()
{
	/* The reactions of state idle. */
	if (check_main_region_idle_tr0_tr0())
	{ 
		effect_main_region_idle_tr0();
	}  else
	{
		if (check_main_region_idle_tr1_tr1())
		{ 
			effect_main_region_idle_tr1();
		} 
	}
}

/* The reactions of state right_trigger. */
void ControllerStateChart::react_main_region_right_trigger()
{
	/* The reactions of state right_trigger. */
	if (check_main_region_right_trigger_tr0_tr0())
	{ 
		effect_main_region_right_trigger_tr0();
	} 
}

/* The reactions of state left_trigger. */
void ControllerStateChart::react_main_region_left_trigger()
{
	/* The reactions of state left_trigger. */
	if (check_main_region_left_trigger_tr0_tr0())
	{ 
		effect_main_region_left_trigger_tr0();
	}  else
	{
		if (check_main_region_left_trigger_tr1_tr1())
		{ 
			effect_main_region_left_trigger_tr1();
		} 
	}
}

/* The reactions of state left_triggered. */
void ControllerStateChart::react_main_region_left_triggered()
{
	/* The reactions of state left_triggered. */
	if (check_main_region_left_triggered_tr0_tr0())
	{ 
		effect_main_region_left_triggered_tr0();
	}  else
	{
		if (check_main_region_left_triggered_tr1_tr1())
		{ 
			effect_main_region_left_triggered_tr1();
		} 
	}
}

/* The reactions of state right_triggered. */
void ControllerStateChart::react_main_region_right_triggered()
{
	/* The reactions of state right_triggered. */
	if (check_main_region_right_triggered_tr0_tr0())
	{ 
		effect_main_region_right_triggered_tr0();
	}  else
	{
		if (check_main_region_right_triggered_tr1_tr1())
		{ 
			effect_main_region_right_triggered_tr1();
		} 
	}
}

/* The reactions of state changing_Volume. */
void ControllerStateChart::react_main_region_changing_Volume()
{
	/* The reactions of state changing_Volume. */
	effect_main_region_changing_Volume_tr0();
}

/* The reactions of state pausing. */
void ControllerStateChart::react_main_region_pausing()
{
	/* The reactions of state pausing. */
	effect_main_region_pausing_tr0();
}

/* The reactions of state nextSong. */
void ControllerStateChart::react_main_region_nextSong()
{
	/* The reactions of state nextSong. */
	if (check_main_region_nextSong_tr0_tr0())
	{ 
		effect_main_region_nextSong_tr0();
	}  else
	{
		if (check_main_region_nextSong_tr1_tr1())
		{ 
			effect_main_region_nextSong_tr1();
		} 
	}
}

/* The reactions of state previousSong. */
void ControllerStateChart::react_main_region_previousSong()
{
	/* The reactions of state previousSong. */
	if (check_main_region_previousSong_tr0_tr0())
	{ 
		effect_main_region_previousSong_tr0();
	} 
}

/* The reactions of state dynamicVolume. */
void ControllerStateChart::react_main_region_dynamicVolume()
{
	/* The reactions of state dynamicVolume. */
	if (check_main_region_dynamicVolume_tr0_tr0())
	{ 
		effect_main_region_dynamicVolume_tr0();
	} 
}

/* Default react sequence for initial entry  */
void ControllerStateChart::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	ifaceInternalSCI.playing = true;
	ifaceInternalSCI.vol = 50;
	enseq_main_region_idle_default();
}


