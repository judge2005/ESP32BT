/*
 * A2DPEventDispatcher.h
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_ESP32BT_SRC_A2DPEVENTDISPATCHER_H_
#define LIBRARIES_ESP32BT_SRC_A2DPEVENTDISPATCHER_H_

#include <list>

#include "A2DPAudioStateSubscriber.h"
#include "A2DPAudioConfigSubscriber.h"
#include "A2DPConnectionStateSubscriber.h"

namespace A2DP {

	class EventDispatcher {
	public:
		EventDispatcher();

		void addConnectionStateSubscriber(ConnectionStateSubscriber *s);
		void addAudioStateSubscriber(AudioStateSubscriber *s);
		void addAudioConfigSubscriber(AudioConfigSubscriber *s);

	protected:
		static std::list<ConnectionStateSubscriber*> connectionStateSubscribers;
		static std::list<AudioStateSubscriber*> audioStateSubscribers;
		static std::list<AudioConfigSubscriber*> audioConfigSubscribers;
	};

} /* namespace A2DP */

#endif /* LIBRARIES_ESP32BT_SRC_A2DPEVENTDISPATCHER_H_ */
