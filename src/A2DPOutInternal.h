/*
 * A2DP.h
 *
 *  Created on: Dec 17, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPOUTINTERNAL_H_
#define LIBRARIES_BT_SRC_A2DPOUTINTERNAL_H_
#include "A2DPOut.h"

#include <stdint.h>
#include <stddef.h>

namespace A2DP {
	class OutInternal : public Out {
	public:
		OutInternal();
		virtual void init(int port=0, int bufCount=6, int sampleRate=44100);
		virtual void setSampleRate(int sampleRate);
		virtual size_t play(uint8_t *data, size_t item_size);
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPOUTINTERNAL_H_ */
