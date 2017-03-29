
#ifndef CONTROLLERSTATECHART_H_
#define CONTROLLERSTATECHART_H_

#include "..\src\sc_types.h"
#include "StatemachineInterface.h"
#include "..\src\TimedStatemachineInterface.h"

/*! \file Header of the state machine 'ControllerStateChart'.
*/

class ControllerStateChart : public TimedStatemachineInterface, public StatemachineInterface
{
	
	public:
		
		ControllerStateChart();
		
		~ControllerStateChart();
		
		/*! Enumeration of all states */ 
		typedef enum
		{
			main_region_idle,
			main_region_right_trigger,
			main_region_left_trigger,
			main_region_left_triggered,
			main_region_right_triggered,
			main_region_changing_Volume,
			main_region_pausing,
			main_region_nextSong,
			main_region_previousSong,
			main_region_dynamicVolume,
			ControllerStateChart_last_state
		} ControllerStateChartStates;
		
		//! Inner class for default interface scope.
		class DefaultSCI
		{
			
			public:
				
			private:
				friend class ControllerStateChart;
		};
				
		
		/*! Returns an instance of the interface class 'DefaultSCI'. */
		DefaultSCI* getDefaultSCI();
		
		
		//! Inner class for internal interface scope operation callbacks.
		class InternalSCI_OCB
		{
			public:
				virtual ~InternalSCI_OCB() = 0;
				
				virtual void changePlaystate() = 0;
		};
		
		/*! Set the working instance of the operation callback interface 'InternalSCI_OCB'. */
		void setInternalSCI_OCB(InternalSCI_OCB* operationCallback);
		
		void init();
		
		void enter();
		
		void exit();
		
		void runCycle();
		
		/*!
		* Checks if the state machine is active (until 2.4.1 this method was used for states).
		* A state machine is active if it has been entered. It is inactive if it has not been entered at all or if it has been exited.
		*/
		sc_boolean isActive();
		
		
		/*!
		* Checks if all active states are final. 
		* If there are no active states then the state machine is considered being inactive. In this case this method returns false.
		*/
		sc_boolean isFinal();
		
		void setTimer(TimerInterface* timer);
		
		TimerInterface* getTimer();
		
		void raiseTimeEvent(sc_eventid event);
		
		/*! Checks if the specified state is active (until 2.4.1 the used method for states was calles isActive()). */
		sc_boolean isStateActive(ControllerStateChartStates state);
	
	private:
	
		//! Inner class for internal interface scope.
		class InternalSCI
		{
			
			public:
				/*! Raises the in event 'right' that is defined in the internal scope. */
				void raise_right();
				
				/*! Checks if the out event 'right' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_right();
				
				/*! Raises the in event 'left' that is defined in the internal scope. */
				void raise_left();
				
				/*! Checks if the out event 'left' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_left();
				
				/*! Raises the in event 'no_right' that is defined in the internal scope. */
				void raise_no_right();
				
				/*! Checks if the out event 'no_right' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_no_right();
				
				/*! Raises the in event 'no_left' that is defined in the internal scope. */
				void raise_no_left();
				
				/*! Checks if the out event 'no_left' that is defined in the internal scope has been raised. */
				sc_boolean isRaised_no_left();
				
				/*! Gets the value of the variable 'song' that is defined in the internal scope. */
				int32_t get_song();
				
				/*! Sets the value of the variable 'song' that is defined in the internal scope. */
				void set_song(int32_t value);
				
				/*! Gets the value of the variable 'songsCount' that is defined in the internal scope. */
				int32_t get_songsCount();
				
				/*! Sets the value of the variable 'songsCount' that is defined in the internal scope. */
				void set_songsCount(int32_t value);
				
				/*! Gets the value of the variable 'vol' that is defined in the internal scope. */
				int32_t get_vol();
				
				/*! Sets the value of the variable 'vol' that is defined in the internal scope. */
				void set_vol(int32_t value);
				
				/*! Gets the value of the variable 'playing' that is defined in the internal scope. */
				sc_boolean get_playing();
				
				/*! Sets the value of the variable 'playing' that is defined in the internal scope. */
				void set_playing(sc_boolean value);
				
				
			private:
				friend class ControllerStateChart;
				sc_boolean right_raised;
				sc_boolean left_raised;
				sc_boolean no_right_raised;
				sc_boolean no_left_raised;
				int32_t song;
				int32_t songsCount;
				int32_t vol;
				sc_boolean playing;
		};
	
		//! the maximum number of orthogonal states defines the dimension of the state configuration vector.
		static const sc_integer maxOrthogonalStates = 1;
		
		//! number of time events used by the state machine.
		static const sc_integer timeEventsCount = 4;
		TimerInterface* timer;
		sc_boolean timeEvents[timeEventsCount];
		
		ControllerStateChartStates stateConfVector[maxOrthogonalStates];
		
		sc_ushort stateConfVectorPosition;
		
		DefaultSCI iface;
		InternalSCI ifaceInternalSCI;
		InternalSCI_OCB* ifaceInternalSCI_OCB;
		
		// prototypes of all internal functions
		
		sc_boolean check_main_region_idle_tr0_tr0();
		sc_boolean check_main_region_idle_tr1_tr1();
		sc_boolean check_main_region_right_trigger_tr0_tr0();
		sc_boolean check_main_region_left_trigger_tr0_tr0();
		sc_boolean check_main_region_left_trigger_tr1_tr1();
		sc_boolean check_main_region_left_triggered_tr0_tr0();
		sc_boolean check_main_region_left_triggered_tr1_tr1();
		sc_boolean check_main_region_right_triggered_tr0_tr0();
		sc_boolean check_main_region_right_triggered_tr1_tr1();
		sc_boolean check_main_region_changing_Volume_tr0_tr0();
		sc_boolean check_main_region_pausing_tr0_tr0();
		sc_boolean check_main_region_nextSong_tr0_tr0();
		sc_boolean check_main_region_nextSong_tr1_tr1();
		sc_boolean check_main_region_previousSong_tr0_tr0();
		sc_boolean check_main_region_dynamicVolume_tr0_tr0();
		void effect_main_region_idle_tr0();
		void effect_main_region_idle_tr1();
		void effect_main_region_right_trigger_tr0();
		void effect_main_region_left_trigger_tr0();
		void effect_main_region_left_trigger_tr1();
		void effect_main_region_left_triggered_tr0();
		void effect_main_region_left_triggered_tr1();
		void effect_main_region_right_triggered_tr0();
		void effect_main_region_right_triggered_tr1();
		void effect_main_region_changing_Volume_tr0();
		void effect_main_region_pausing_tr0();
		void effect_main_region_nextSong_tr0();
		void effect_main_region_nextSong_tr1();
		void effect_main_region_previousSong_tr0();
		void effect_main_region_dynamicVolume_tr0();
		void enact_main_region_left_trigger();
		void enact_main_region_left_triggered();
		void enact_main_region_right_triggered();
		void enact_main_region_pausing();
		void enact_main_region_nextSong();
		void enact_main_region_previousSong();
		void exact_main_region_left_trigger();
		void exact_main_region_left_triggered();
		void exact_main_region_right_triggered();
		void exact_main_region_nextSong();
		void enseq_main_region_idle_default();
		void enseq_main_region_right_trigger_default();
		void enseq_main_region_left_trigger_default();
		void enseq_main_region_left_triggered_default();
		void enseq_main_region_right_triggered_default();
		void enseq_main_region_changing_Volume_default();
		void enseq_main_region_pausing_default();
		void enseq_main_region_nextSong_default();
		void enseq_main_region_previousSong_default();
		void enseq_main_region_dynamicVolume_default();
		void enseq_main_region_default();
		void exseq_main_region_idle();
		void exseq_main_region_right_trigger();
		void exseq_main_region_left_trigger();
		void exseq_main_region_left_triggered();
		void exseq_main_region_right_triggered();
		void exseq_main_region_changing_Volume();
		void exseq_main_region_pausing();
		void exseq_main_region_nextSong();
		void exseq_main_region_previousSong();
		void exseq_main_region_dynamicVolume();
		void exseq_main_region();
		void react_main_region_idle();
		void react_main_region_right_trigger();
		void react_main_region_left_trigger();
		void react_main_region_left_triggered();
		void react_main_region_right_triggered();
		void react_main_region_changing_Volume();
		void react_main_region_pausing();
		void react_main_region_nextSong();
		void react_main_region_previousSong();
		void react_main_region_dynamicVolume();
		void react_main_region__entry_Default();
		void clearInEvents();
		void clearOutEvents();
		
};
inline ControllerStateChart::InternalSCI_OCB::~InternalSCI_OCB() {}
#endif /* CONTROLLERSTATECHART_H_ */
