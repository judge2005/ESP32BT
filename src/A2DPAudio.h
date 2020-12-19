/*
 * A2DPAudio.h
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#ifndef LIBRARIES_BT_SRC_A2DPAUDIO_H_
#define LIBRARIES_BT_SRC_A2DPAUDIO_H_

namespace A2DP {
	class Audio {
	public:
		Audio();

		bool init(const char *deviceName);
		void stop();
	};
}
#endif /* LIBRARIES_BT_SRC_A2DPAUDIO_H_ */
