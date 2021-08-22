/*
 * MQTT.c
 *
 *  Created on: 18 sie 2021
 *      Author: rk
 */

#include "MQTT.h"

unsigned char mqttDataBuffer[128];
static int internalState = 0;
static int reconnect_cnt = 0;
static int topic_cnt = 0;

// Transport layer uses the esp8266 networkwrapper
static transport_iofunctions_t iof = {NetworkSend, NULL};
static int transport_socket;

int MQTTClient_Start()
{
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
	int length;

	transport_socket = transport_open(&iof);

	connectData.MQTTVersion 	  = 3;
	connectData.clientID.cstring  = DEVICE_NAME;
	connectData.keepAliveInterval = CONNECTION_KEEPALIVE_S;
	connectData.username.cstring  = L_USER;
	connectData.password.cstring  = L_PASSWORD;

	length = MQTTSerialize_connect(mqttDataBuffer, sizeof(mqttDataBuffer), &connectData);

	// Send CONNECT to the mqtt broker
	if(length == transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length))
	{
		internalState = 1;
		reconnect_cnt = 0;
		return 1;
	}

	reconnect_cnt++;

	return 0;
}

int MQTTClient_Publish(const t_measf * data)
{
	MQTTString topicString = MQTTString_initializer;
	int length;
	unsigned char payload[16];
	int result = 0;

	switch(internalState) {
	case 0:
		if(reconnect_cnt < 4)
		{
			MQTTClient_Start();
			result = 1;
		}
		else { return 0; }
		break;
	case 1:
		switch(topic_cnt) {
		case 0:
			topicString.cstring = TOPIC_CH1;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch1)));
			break;
		case 1:
			topicString.cstring = TOPIC_CH2;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch2)));
			break;
		case 2:
			topicString.cstring = TOPIC_CH3;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch3)));
			break;
		case 3:
			topicString.cstring = TOPIC_CH4;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch4)));
			break;
		case 4:
			topicString.cstring = TOPIC_EFF;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Eff)));
			break;
		case 5:
			topicString.cstring = TOPIC_P1;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->P1)));
			break;
		case 6:
			topicString.cstring = TOPIC_P2;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->P2)));
			break;
		case 7:
			topicString.cstring = TOPIC_ENERGY_CH1;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->EnergyCH1)));
			break;
		case 8:
			topicString.cstring = TOPIC_ENERGY_CH2;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->EnergyCH2)));
			break;
		case 9:
			topicString.cstring = TOPIC_Q_CH1;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Q_CH1)));
			break;
		case 10:
			topicString.cstring = TOPIC_Q_CH2;
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Q_CH2)));
			break;
		}

		if( length == transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) { topic_cnt = (topic_cnt + 1) % 11; }
		else { internalState = 0; }

		result = 1;
	break;
	default:
		result = 0;
	}

	return result;

}
