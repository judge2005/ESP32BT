/*
 * A2DP.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#include <A2DPOutInternalNeg.h>
#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

A2DP::OutInternalNeg::OutInternalNeg() {
}

A2DP::OutInternalNeg::~OutInternalNeg() {
}

size_t A2DP::OutInternalNeg::play(uint8_t *data, size_t item_size) {
	size_t bytes_written = 0;

    uint16_t* corr_data = (uint16_t*) data;
    for (int i=0; i<item_size/2; i++) {
        uint16_t sample = (data[i*2] | data[i*2+1]<<8) ^ 0xffff;
        corr_data[i]= sample + 0x8000;
    }

	i2s_write((i2s_port_t)0, data, item_size, &bytes_written, portMAX_DELAY);

	return bytes_written;
}


