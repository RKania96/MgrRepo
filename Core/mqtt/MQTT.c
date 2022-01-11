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
	}
	else
	{
		reconnect_cnt++;
	}

	return 0;
}

int MQTTClient_Publish(const t_measf * data, const float * temp)
{
	MQTTString topicString = MQTTString_initializer;
	int length;
    unsigned char payload[16];

	int notUsed = 0;

	switch(internalState) {
	case 0:
		if(reconnect_cnt < 3)
		{
			MQTTClient_Start();
		}
		break;
	case 1:
		switch(topic_cnt) {
		case 0:
			topicString.cstring = TOPIC_V_CH1;
			length = sprintf((char*)payload, "%f", data->Ch1);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 1:
			topicString.cstring = TOPIC_V_CH2;
			length = sprintf((char*)payload, "%f", data->Ch2);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 2:
			topicString.cstring = TOPIC_I_CH1;
			length = sprintf((char*)payload, "%f", data->Ch3);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 3:
			topicString.cstring = TOPIC_I_CH2;
			length = sprintf((char*)payload, "%f", data->Ch4);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 4:
			topicString.cstring = TOPIC_EFF;
			length = sprintf((char*)payload, "%f", data->Eff);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 5:
			topicString.cstring = TOPIC_P_CH1;
			length = sprintf((char*)payload, "%f", data->P1);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 6:
			topicString.cstring = TOPIC_P_CH2;
			length = sprintf((char*)payload, "%f", data->P2);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 7:
			topicString.cstring = TOPIC_ENERGY_CH1;
			length = sprintf((char*)payload, "%f", data->EnergyCH1);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 8:
			topicString.cstring = TOPIC_ENERGY_CH2;
			length = sprintf((char*)payload, "%f", data->EnergyCH2);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 9:
			topicString.cstring = TOPIC_Q_CH1;
			length = sprintf((char*)payload, "%f", data->Q_CH1);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 10:
			topicString.cstring = TOPIC_Q_CH2;
			length = sprintf((char*)payload, "%f", data->Q_CH2);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 11:
			topicString.cstring = TOPIC_TEMP_1;
			length = sprintf((char*)payload, "%f", *temp);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 12:
			topicString.cstring = TOPIC_STATUS_1;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 13:
			topicString.cstring = TOPIC_NO_OF_CYCLES;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 14:
			topicString.cstring = TOPIC_STATUS_2;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 15:
			topicString.cstring = TOPIC_TEMP_2;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 16:
			topicString.cstring = TOPIC_CHARGE_DEGREE;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 17:
			topicString.cstring = TOPIC_CAPACITY;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 18:
			topicString.cstring = TOPIC_INSOLATION;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		case 19:
			topicString.cstring = TOPIC_ENERGY;
			length = sprintf((char*)payload, "%d", notUsed);
			length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, length);
			break;
		}

		if( length == transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length))
		{
			topic_cnt = (topic_cnt + 1) % 20;
		}
		else
		{
			internalState = 0;
		}
		break;
	}

	return 0;
}
