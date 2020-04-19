/*
 * A2DPEventSink.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: mpand
 */

#include <A2DPEventSink.h>

#include <string.h>
#include "esp32-hal-log.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_a2dp_api.h"

#define A2DP_EVENT_SINK_TAG	"A2DP_EVENT_SINK"

std::list<A2DP::ConnectionStateSubscriber*> A2DP::EventSink::connectionStateSubscribers;
std::list<A2DP::AudioStateSubscriber*> A2DP::EventSink::audioStateSubscribers;
std::list<A2DP::AudioConfigSubscriber*> A2DP::EventSink::audioConfigSubscribers;

A2DP::EventSink::EventSink() {
}

bool A2DP::EventSink::init() {
    if (esp_bluedroid_get_status() != ESP_BLUEDROID_STATUS_ENABLED) {
        ESP_LOGE(A2DP_EVENT_SINK_TAG, "%s bluedroid not enabled", __func__);
        return false;
    }

    esp_a2d_register_callback(eventCallback);

    return true;
}

void A2DP::EventSink::addConnectionStateSubscriber(A2DP::ConnectionStateSubscriber *s) {
	connectionStateSubscribers.push_back(s);
}

void A2DP::EventSink::addAudioStateSubscriber(A2DP::AudioStateSubscriber *s) {
	audioStateSubscribers.push_back(s);
}

void A2DP::EventSink::addAudioConfigSubscriber(A2DP::AudioConfigSubscriber *s) {
	audioConfigSubscribers.push_back(s);
}

void A2DP::EventSink::eventCallback(esp_a2d_cb_event_t event, esp_a2d_cb_param_t *param) {
	// Called in task 'Btc_task'
	ESP_LOGD(A2DP_EVENT_SINK_TAG, "Task: %s, event %d", pcTaskGetTaskName(NULL), event);
    switch (event) {
    case ESP_A2D_CONNECTION_STATE_EVT: {
    	for (A2DP::ConnectionStateSubscriber *s : connectionStateSubscribers) {
    		switch (param->conn_stat.state) {
    		case ESP_A2D_CONNECTION_STATE_DISCONNECTED:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Disconnected");
    			s->disconnected();
    			break;
    		case ESP_A2D_CONNECTION_STATE_CONNECTING:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Connecting");
    			s->connecting();
    			break;
    		case ESP_A2D_CONNECTION_STATE_CONNECTED:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Connected");
    			s->connected();
    			break;
    		case ESP_A2D_CONNECTION_STATE_DISCONNECTING:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Disconnecting");
    			s->disconnecting();
    			break;
    		default:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Unknown A2DP Connection State Event: %d", param->conn_stat.state);
    		}
    	}
        break;
    }
    case ESP_A2D_AUDIO_STATE_EVT: {
    	for (A2DP::AudioStateSubscriber *s : audioStateSubscribers) {
    		switch (param->audio_stat.state) {
    		case ESP_A2D_AUDIO_STATE_STARTED:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio started");
    			s->started();
    			break;
    		case ESP_A2D_AUDIO_STATE_STOPPED:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio stopped");
    			s->stopped();
    			break;
    		case ESP_A2D_AUDIO_STATE_REMOTE_SUSPEND:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio suspended");
    			s->suspended();
    			break;
    		default:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Unknown A2DP Audio State Event: %d", param->audio_stat.state);
    		}
    	}
        break;
    }
    case ESP_A2D_AUDIO_CFG_EVT: {
        // for now only SBC stream is supported
    	for (A2DP::AudioConfigSubscriber *s : audioConfigSubscribers) {
    		switch(param->audio_cfg.mcc.type) {
    		case ESP_A2D_MCT_SBC: {
                int sampleRate = 16000;
                char oct0 = param->audio_cfg.mcc.cie.sbc[0];
                if (oct0 & (0x01 << 6)) {
                    sampleRate = 32000;
                } else if (oct0 & (0x01 << 5)) {
                    sampleRate = 44100;
                } else if (oct0 & (0x01 << 4)) {
                    sampleRate = 48000;
                }

    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio codec SBC, sample rate %d", sampleRate);

                ESP_LOGI(A2DP_EVENT_SINK_TAG, "Configure audio player %x-%x-%x-%x",
                		param->audio_cfg.mcc.cie.sbc[0],
    					param->audio_cfg.mcc.cie.sbc[1],
    					param->audio_cfg.mcc.cie.sbc[2],
    					param->audio_cfg.mcc.cie.sbc[3]);

    			s->sbc(sampleRate);
    			break;
    		}
    		case ESP_A2D_MCT_M12:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio codec M12");
    			s->m12();
    			break;
    		case ESP_A2D_MCT_M24:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio codec M24");
    			s->m24();
    			break;
    		case ESP_A2D_MCT_ATRAC:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Audio codec ATRAC");
    			s->atrac();
    			break;
    		default:
    	        ESP_LOGI(A2DP_EVENT_SINK_TAG, "Unknown A2DP Audio Config Event: %d", param->audio_cfg.mcc.type);
    		}	// End switch
    	}	// End for
        break;	// End case ESP_A2D_AUDIO_CFG_EVT
    }	// End ESP_A2D_AUDIO_CFG_EVT
    default:
        ESP_LOGE(A2DP_EVENT_SINK_TAG, "Unhandled evt %d", event);
        break;
    }
}

