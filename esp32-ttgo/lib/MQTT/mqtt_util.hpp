#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

void mqtt_setup();
void mqtt_loop();

void mqtt_reconnect();

void sender(void* param);
void onReceiveMessage(char* topic, byte* payload, unsigned int length);