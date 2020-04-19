/*
 * A2DP.h
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPOUT_H_
#define LIBRARIES_BT_SRC_A2DPOUT_H_
#include "A2DPAudioConfigSubscriber.h"
#include "A2DPEventDispatcher.h"

#include <stdint.h>
#include <stddef.h>

namespace A2DP {
	class Out : public AudioConfigSubscriber {
	public:
		Out();
		void init(int port=0, int bufCount=6, int sampleRate=44100);
		void subscribeTo(EventDispatcher &dispatcher);

		void setSampleRate(int sampleRate);
		size_t play(uint8_t *data, size_t item_size);

		// Event handlers
		virtual void sbc(int sampleRate);

	private:
		int port;
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPOUT_H_ */
