/*
 * A2DP.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#include <A2DPOutInternal.h>
#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

#define CONFIG_EXAMPLE_I2S_BCK_PIN 26
#define CONFIG_EXAMPLE_I2S_LRCK_PIN 25
#define CONFIG_EXAMPLE_I2S_DATA_PIN 22

A2DP::OutInternal::OutInternal() {
}

void A2DP::OutInternal::init(int port, int bufCount, int sampleRate) {
	this->port = port;

    i2s_config_t i2sConfig = {
        mode : (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_DAC_BUILT_IN),	// Only TX
        sample_rate : sampleRate,
        bits_per_sample : I2S_BITS_PER_SAMPLE_16BIT, /* the DAC module will only take the 8bits from MSB */
        channel_format : I2S_CHANNEL_FMT_RIGHT_LEFT,		// 2-channels
        communication_format : I2S_COMM_FORMAT_I2S_MSB,		// ?
        intr_alloc_flags : 0,								// Default interrupt priority
        dma_buf_count : bufCount,
        dma_buf_len : 60,
		use_apll : false,
        tx_desc_auto_clear : false,							//Auto clear tx descriptor on underflow
		fixed_mclk: 0
    };

    i2s_driver_install((i2s_port_t)port, &i2sConfig, 0, NULL);

    i2s_set_pin((i2s_port_t)port, NULL);
}

void A2DP::OutInternal::setSampleRate(int sampleRate) {
	i2s_set_sample_rates((i2s_port_t)port, sampleRate);
}

void play() {
}

size_t A2DP::OutInternal::play(uint8_t *data, size_t item_size) {
	size_t bytes_written = 0;

    uint16_t* corr_data = (uint16_t*) data;
    for (int i=0; i<item_size/2; i++) {
        int16_t sample = data[i*2] | data[i*2+1]<<8;
        corr_data[i]= sample + 0x8000;
    }

	i2s_write((i2s_port_t)0, data, item_size, &bytes_written, portMAX_DELAY);

	return bytes_written;
}


