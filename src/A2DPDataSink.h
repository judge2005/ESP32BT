/*
 * A2DPIn.h
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPDATASINK_H_
#define LIBRARIES_BT_SRC_A2DPDATASINK_H_
#include <A2DPAudioStateSubscriber.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/ringbuf.h"

namespace A2DP {
	class DataSink : public AudioStateSubscriber {
	public:
		DataSink();
		bool init();
		uint8_t *waitForData(size_t *itemSize);
		void doneWithData(uint8_t *data);

		virtual void started();

	private:
		static void dataCallback(const uint8_t *data, uint32_t len);

		static RingbufHandle_t dataBuffer;
		static uint32_t pktCount;
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPDATASINK_H_ */
