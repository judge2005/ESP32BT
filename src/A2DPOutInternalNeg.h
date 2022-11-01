/*
 * A2DP.h
 *
 *  Created on: Dec 17, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPOUTINTERNALNEG_H_
#define LIBRARIES_BT_SRC_A2DPOUTINTERNALNEG_H_
#include "A2DPOut.h"

#include <stdint.h>
#include <stddef.h>
#include "A2DPOutInternal.h"

namespace A2DP {
	class OutInternalNeg : public OutInternal {
	public:
		OutInternalNeg();
		virtual ~OutInternalNeg();
		virtual size_t play(uint8_t *data, size_t item_size);
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPOUTINTERNALNEG_H_ */
