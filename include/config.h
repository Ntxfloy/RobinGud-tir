#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>
#include <RCSwitch.h>
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// Пины и константы
#define DATA_PIN1 13
#define CLK_PIN1 14
#define CS_PIN1 12
#define DATA_PIN2 13
#define CLK_PIN2 14
#define CS_PIN2 26
#define RF_RECEIVE_PIN 27
#define LED_PIN 25
#define BUTTON_PIN 15
#define PAIRING_BUTTON_PIN 23

// Общие константы
#define MAX_DEVICES 2
#define NUM_LEDS 120
#define EEPROM_ADDR 0

#endif 