/*
 * A2DP.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#include <A2DPOut.h>
#include "freertos/FreeRTOS.h"
#include "driver/i2s.h"

#define CONFIG_EXAMPLE_I2S_BCK_PIN 26
#define CONFIG_EXAMPLE_I2S_LRCK_PIN 25
#define CONFIG_EXAMPLE_I2S_DATA_PIN 22

A2DP::Out::Out() {
}

void A2DP::Out::init(int port, int bufCount, int sampleRate) {
	this->port = port;

    i2s_config_t i2sConfig = {
        mode : (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),	// Only TX
        sample_rate : sampleRate,
        bits_per_sample : I2S_BITS_PER_SAMPLE_16BIT,
        channel_format : I2S_CHANNEL_FMT_RIGHT_LEFT,		//2-channels
        communication_format : I2S_COMM_FORMAT_I2S_MSB,
        intr_alloc_flags : 0,								//Default interrupt priority
        dma_buf_count : bufCount,
        dma_buf_len : 60,
		use_apll : true,
        tx_desc_auto_clear : true,							//Auto clear tx descriptor on underflow
		fixed_mclk: 0
    };

    i2s_driver_install((i2s_port_t)port, &i2sConfig, 0, NULL);

    i2s_pin_config_t pin_config = {
        .bck_io_num = CONFIG_EXAMPLE_I2S_BCK_PIN,
        .ws_io_num = CONFIG_EXAMPLE_I2S_LRCK_PIN,
        .data_out_num = CONFIG_EXAMPLE_I2S_DATA_PIN,
        .data_in_num = -1                                                       //Not used
    };

    i2s_set_pin((i2s_port_t)port, &pin_config);
}

void A2DP::Out::subscribeTo(EventDispatcher &dispatcher) {
	dispatcher.addAudioConfigSubscriber(this);
}

void A2DP::Out::setSampleRate(int sampleRate) {
	i2s_set_clk((i2s_port_t)port, sampleRate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);
}

void A2DP::Out::sbc(int sampleRate) {
	setSampleRate(sampleRate);
}

size_t A2DP::Out::play(uint8_t *data, size_t item_size) {
	size_t bytes_written = 0;
	i2s_write((i2s_port_t)0, data, item_size, &bytes_written, portMAX_DELAY);

	return bytes_written;
}
