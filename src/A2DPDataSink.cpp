/*
 * A2DPIn.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: mpand
 */

#include <A2DPDataSink.h>
#include "esp32-hal-bt.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_a2dp_api.h"

#define A2DP_DATA_SINK_TAG	"A2DP_DATA_SINK"

uint32_t A2DP::DataSink::pktCount = 0;
RingbufHandle_t A2DP::DataSink::dataBuffer = 0;

A2DP::DataSink::DataSink() {
    dataBuffer = xRingbufferCreate(8 * 1024, RINGBUF_TYPE_BYTEBUF);
}

bool A2DP::DataSink::init() {
    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        ESP_LOGE(A2DP_DATA_SINK_TAG, "%s bluedroid not enabled", __func__);
        return false;
    }

    esp_a2d_sink_init();

    esp_a2d_sink_register_data_callback(dataCallback);

    return true;
}

void A2DP::DataSink::started() {
	pktCount = 0;
}

uint8_t *A2DP::DataSink::waitForData(size_t *itemSize) {
	if (dataBuffer) {
		return (uint8_t*) xRingbufferReceive(dataBuffer, itemSize, (portTickType)portMAX_DELAY);
	} else {
		return 0;
	}
}

void A2DP::DataSink::doneWithData(uint8_t *data) {
	vRingbufferReturnItem(dataBuffer,(void *)data);
}

void A2DP::DataSink::dataCallback(const uint8_t *data, uint32_t len) {
	// Called in task 'BtA2dSinkT'
	if (dataBuffer) {
		xRingbufferSend(dataBuffer, (void *)data, len, (portTickType)portMAX_DELAY);
	}
    if (++pktCount % 100 == 0) {
    	ESP_LOGD(A2DP_DATA_SINK_TAG, "Task: %s", pcTaskGetTaskName(NULL));
        ESP_LOGI(A2DP_DATA_SINK_TAG, "Audio packet count %u", pktCount);
    }
}
