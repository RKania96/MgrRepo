/*
 * MQTT.h
 *
 *  Created on: 18 sie 2021
 *      Author: rk
 */

#ifndef MQTT_MQTT_H_
#define MQTT_MQTT_H_

#include "ADS131A0x.h"
#include <NetworkWrapper.h>
#include "MQTTPacket.h"
#include "transport.h"

int MQTTClient_Start();
int MQTTClient_Publish(const t_measf * data);

#endif /* MQTT_MQTT_H_ */
