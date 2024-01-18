#pragma once

#include <Arduino.h>
#include <CAN.h>
#include <TFT_eSPI.h>

#include <thread>

void can_showMessages(char history[4][11]);
void can_addHistory(char message[10]);
void can_clear_screen();
void can_sender();
void can_receiver();

void can_setup();
void can_loop();