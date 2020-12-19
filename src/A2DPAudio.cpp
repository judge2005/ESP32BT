/*
 * A2DP::Audio.cpp
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#include <A2DPAudio.h>
#include "esp32-hal-bt.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "esp_a2dp_api.h"

#define A2DP_AUDIO_TAG	"A2DP_AUDIO"

A2DP::Audio::Audio() {
}

bool A2DP::Audio::init(const char *deviceName) {
	esp_bt_mem_release(ESP_BT_MODE_BLE);

	btStart();
    ESP_LOGI(A2DP_AUDIO_TAG, "btStarted() said: %d", btStarted());

    if (esp_bluedroid_init() != ESP_OK) {
        ESP_LOGE(A2DP_AUDIO_TAG, "%s initialize bluedroid failed", __func__);
        return false;
    }
    ESP_LOGI(A2DP_AUDIO_TAG, "esp_bluedroid_get_status() after esp_bluedroid_init() said: %d", esp_bluedroid_get_status());

    if (esp_bluedroid_enable() != ESP_OK) {
        ESP_LOGE(A2DP_AUDIO_TAG, "%s enable bluedroid failed", __func__);
        return false;
    }
    ESP_LOGI(A2DP_AUDIO_TAG, "esp_bluedroid_get_status() after esp_bluedroid_enable() said: %d", esp_bluedroid_get_status());

    /* set up device name */
    esp_bt_dev_set_device_name(deviceName);

    /* set discoverable and connectable mode, wait to be connected */
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);

    return true;
}

void A2DP::Audio::stop() {
	btStop();
}
