/*
 * A2DPEventSink.h
 *
 *  Created on: Apr 18, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPEVENTSINK_H_
#define LIBRARIES_BT_SRC_A2DPEVENTSINK_H_

#include "esp_a2dp_api.h"

#include "A2DPEventDispatcher.h"

namespace A2DP {
	class EventSink : public EventDispatcher {
	public:
		EventSink();
		bool init();

	private:
		static void eventCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param);
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPEVENTSINK_H_ */
