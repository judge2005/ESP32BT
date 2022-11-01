/*
 * EventDispatcher.cpp
 *
 *  Created on: Apr 19, 2020
 *      Author: mpand
 */

#include <A2DPEventDispatcher.h>

std::list<A2DP::ConnectionStateSubscriber*> A2DP::EventDispatcher::connectionStateSubscribers;
std::list<A2DP::AudioStateSubscriber*> A2DP::EventDispatcher::audioStateSubscribers;
std::list<A2DP::AudioConfigSubscriber*> A2DP::EventDispatcher::audioConfigSubscribers;

A2DP::EventDispatcher::EventDispatcher() {
}

void A2DP::EventDispatcher::addConnectionStateSubscriber(A2DP::ConnectionStateSubscriber *s) {
	connectionStateSubscribers.push_back(s);
}

void A2DP::EventDispatcher::addAudioStateSubscriber(A2DP::AudioStateSubscriber *s) {
	audioStateSubscribers.push_back(s);
}

void A2DP::EventDispatcher::addAudioConfigSubscriber(A2DP::AudioConfigSubscriber *s) {
	audioConfigSubscribers.push_back(s);
}

void A2DP::EventDispatcher::removeConnectionStateSubscriber(A2DP::ConnectionStateSubscriber *s) {
	connectionStateSubscribers.remove(s);
}

void A2DP::EventDispatcher::removeAudioStateSubscriber(A2DP::AudioStateSubscriber *s) {
	audioStateSubscribers.remove(s);
}

void A2DP::EventDispatcher::removeAudioConfigSubscriber(A2DP::AudioConfigSubscriber *s) {
	audioConfigSubscribers.remove(s);
}
