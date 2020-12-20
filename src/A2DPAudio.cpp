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

#define BT_CONTROLLER_CLASSIC_CONFIG() {                              \
    .controller_task_stack_size = ESP_TASK_BT_CONTROLLER_STACK,            \
    .controller_task_prio = ESP_TASK_BT_CONTROLLER_PRIO,                   \
    .hci_uart_no = BT_HCI_UART_NO_DEFAULT,                                 \
    .hci_uart_baudrate = BT_HCI_UART_BAUDRATE_DEFAULT,                     \
    .scan_duplicate_mode = SCAN_DUPLICATE_MODE,                            \
    .scan_duplicate_type = SCAN_DUPLICATE_TYPE_VALUE,                      \
    .normal_adv_size = NORMAL_SCAN_DUPLICATE_CACHE_SIZE,                   \
    .mesh_adv_size = MESH_DUPLICATE_SCAN_CACHE_SIZE,                       \
    .send_adv_reserved_size = SCAN_SEND_ADV_RESERVED_SIZE,                 \
    .controller_debug_flag = CONTROLLER_ADV_LOST_DEBUG_BIT,                \
    .mode = ESP_BT_MODE_CLASSIC_BT,                                      \
    .ble_max_conn = 0,               \
    .bt_max_acl_conn = CONFIG_BTDM_CONTROLLER_BR_EDR_MAX_ACL_CONN_EFF,     \
    .bt_sco_datapath = CONFIG_BTDM_CTRL_BR_EDR_SCO_DATA_PATH_EFF,          \
    .auto_latency = BTDM_CTRL_AUTO_LATENCY_EFF,                            \
    .bt_legacy_auth_vs_evt = BTDM_CTRL_LEGACY_AUTH_VENDOR_EVT_EFF,         \
    .bt_max_sync_conn = CONFIG_BTDM_CONTROLLER_BR_EDR_MAX_SYNC_CONN_EFF,   \
    .magic = ESP_BT_CONTROLLER_CONFIG_MAGIC_VAL,                           \
};

static bool a2dpStart() {
	esp_bt_controller_config_t cfg = BT_CONTROLLER_CLASSIC_CONFIG();
	if(esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED){
		return true;
	}
	if(esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_IDLE){
		esp_bt_controller_init(&cfg);
		while(esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_IDLE){}
	}
	if(esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_INITED){
		if (esp_bt_controller_enable(ESP_BT_MODE_CLASSIC_BT)) {
			log_e("BT Enable failed");
			return false;
		}
	}
	if(esp_bt_controller_get_status() == ESP_BT_CONTROLLER_STATUS_ENABLED){
		return true;
	}
	log_e("BT Start failed");
	return false;
}

A2DP::Audio::Audio() {
}

bool A2DP::Audio::init(const char *deviceName) {
	esp_bt_mem_release(ESP_BT_MODE_BLE);

	a2dpStart();
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
