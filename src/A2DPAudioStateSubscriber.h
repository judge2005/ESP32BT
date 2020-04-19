/*
 * A2DPAudioStateHandler.h
 *
 *  Created on: Apr 18, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPAUDIOSTATESUBSCRIBER_H_
#define LIBRARIES_BT_SRC_A2DPAUDIOSTATESUBSCRIBER_H_

namespace A2DP {
	class AudioStateSubscriber {
	public:
		AudioStateSubscriber();

		virtual void started() {}
		virtual void stopped() {}
		virtual void suspended() {}
	};
}
#endif /* LIBRARIES_BT_SRC_A2DPAUDIOSTATESUBSCRIBER_H_ */
