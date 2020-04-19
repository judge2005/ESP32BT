#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"

#include "A2DPOut.h"
#include "A2DPAudio.h"
#include "A2DPDataSink.h"
#include "A2DPEventSink.h"

A2DP::Out *out = 0;
A2DP::Audio a2dpAudio;
A2DP::DataSink a2dpDataSink;
A2DP::EventSink a2dpEventSink;

void i2sTask(void *arg) {
	uint8_t *data = NULL;
	size_t itemSize = 0;

	out = new A2DP::Out();
	out->init();
	out->subscribeTo(a2dpEventSink);	// Listen for bit rate change

	while (true) {
		itemSize = 0;
		data = a2dpDataSink.waitForData(&itemSize);
		if (itemSize != 0) {
			out->play(data, itemSize);
			a2dpDataSink.doneWithData(data);
		}
	}
}

xTaskHandle i2sTaskHandle = NULL;

class DummyConnectStateSubscriber : public A2DP::ConnectionStateSubscriber {
public:
	void subscribeTo(A2DP::EventDispatcher &dispatcher) {
		dispatcher.addConnectionStateSubscriber(this);
	}
};

DummyConnectStateSubscriber dummySubscriber;

void setup()
{
    /* Initialize NVS — it is used to store PHY calibration data */
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    /* Bluetooth device name, connection mode and profile set up */
    a2dpAudio.init("ESP_SPEAKER");	// Initialize bluetooth
    a2dpDataSink.init();			// Define an A2DP sink
    a2dpEventSink.init();			// Listen for bluetooth events

    // Add event subscriptions for the sink and the output classes
    a2dpDataSink.subscribeTo(a2dpEventSink);	// For data packet counter reset
    dummySubscriber.subscribeTo(a2dpEventSink); // So we can see connection state messages in console

    /* create I2S task */
    xTaskCreate(i2sTask, "I2S", 4096, NULL, configMAX_PRIORITIES - 3, &i2sTaskHandle);

    vTaskDelete(NULL);	// Delete this task (so loop() won't be called)
}


void loop() {

}
