/*
 * A2DPConnectionStateSubscriber.h
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPCONNECTIONSTATESUBSCRIBER_H_
#define LIBRARIES_BT_SRC_A2DPCONNECTIONSTATESUBSCRIBER_H_

namespace A2DP {
	class ConnectionStateSubscriber {
	public:
		ConnectionStateSubscriber();

		virtual void disconnected() {}
		virtual void connecting() {}
		virtual void connected() {}
		virtual void disconnecting() {}
	};
}

#endif /* LIBRARIES_BT_SRC_A2DPCONNECTIONSTATESUBSCRIBER_H_ */
