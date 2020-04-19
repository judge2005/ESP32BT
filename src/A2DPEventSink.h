/*
 * A2DPEventSink.h
 *
 *  Created on: Apr 18, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPEVENTSINK_H_
#define LIBRARIES_BT_SRC_A2DPEVENTSINK_H_

#include <list>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "esp_a2dp_api.h"

#include "A2DPAudioStateSubscriber.h"
#include "A2DPAudioConfigSubscriber.h"
#include "A2DPConnectionStateSubscriber.h"

namespace A2DP {
	class EventSink {
	public:
		EventSink();
		bool init();
		void addConnectionStateSubscriber(ConnectionStateSubscriber *s);
		void addAudioStateSubscriber(AudioStateSubscriber *s);
		void addAudioConfigSubscriber(AudioConfigSubscriber *s);

	private:
		static void eventCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);

		static std::list<ConnectionStateSubscriber*> connectionStateSubscribers;
		static std::list<AudioStateSubscriber*> audioStateSubscribers;
		static std::list<AudioConfigSubscriber*> audioConfigSubscribers;
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPEVENTSINK_H_ */
