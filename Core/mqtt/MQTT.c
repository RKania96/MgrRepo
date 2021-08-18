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

// Transport layer uses the esp8266 networkwrapper
static transport_iofunctions_t iof = {NetworkSend, NULL};
static int transport_socket;

int MQTTClient_Start()
{
	transport_socket = transport_open(&iof);

	int result, length;
	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

	connectData.MQTTVersion 	  = 3;
	connectData.clientID.cstring  = DEVICE_NAME;
	connectData.keepAliveInterval = CONNECTION_KEEPALIVE_S;
	connectData.username.cstring  = L_USER;
	connectData.password.cstring  = L_PASSWORD;

	length = MQTTSerialize_connect(mqttDataBuffer, sizeof(mqttDataBuffer), &connectData);

	// Send CONNECT to the mqtt broker
	if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { internalState++; }
	else { return 0; }
}

int MQTTClient_Publish(const t_measf * data)
{
	if(internalState == 1)
	{
		// Populate the publish message.
		MQTTString topicString = MQTTString_initializer;
		int result = 0;
		int length;
		unsigned char payload[16];

		topicString.cstring = TOPIC_CH1;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch1)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_CH2;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch2)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_CH3;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch3)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_CH4;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Ch4)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_EFF;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Eff)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_P1;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->P1)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_P2;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->P2)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_ENERGY_CH1;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->EnergyCH1)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_ENERGY_CH2;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->EnergyCH2)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_Q_CH1;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Q_CH1)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }

		topicString.cstring = TOPIC_Q_CH2;
		length = MQTTSerialize_publish(mqttDataBuffer, sizeof(mqttDataBuffer), 0, 0, 0, 0, topicString, payload, (length = sprintf(payload, "%f", data->Q_CH2)));
		if((result = transport_sendPacketBuffer(transport_socket, mqttDataBuffer, length)) == length) { result = 1; }
		else { result = 0; }


		if(result == 1) { return 1; }
		else
		{
			if(reconnect_cnt++ < 4)
			{
				internalState = 0;
				return 0;
			}
			else
			{
				internalState = 2;
				return -1;
			}
		}
	}
	else if(internalState == 0)
	{
		MQTTClient_Start();
		internalState = 1;
	}
	else { return -1; }
}
