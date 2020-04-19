/*
 * A2DPAudioConfigSubscriber.h
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPAUDIOCONFIGSUBSCRIBER_H_
#define LIBRARIES_BT_SRC_A2DPAUDIOCONFIGSUBSCRIBER_H_

namespace A2DP {
	class AudioConfigSubscriber {
	public:
		AudioConfigSubscriber();

		virtual void sbc(int sampleRate) {}
		virtual void m12() {}
		virtual void m24() {}
		virtual void atrac() {}
	};
}
#endif /* LIBRARIES_BT_SRC_A2DPAUDIOCONFIGSUBSCRIBER_H_ */
