/* 
 *  Teensy MIDI CC Example
 *  =================
 *  Based on: USB MIDI AnalogControlChange Example by PJRC
 *  Prepared by: Mic Black <mic@micslab.com>
 *  
 *  Please note: You must select MIDI + Serial from the "Tools > USB Type" menu
*/

#include <Bounce.h>
#include "midi_cc.h"
#include "config.h"

// Initial states for hardware
uint16_t lastReading = -1;
uint8_t lastReset = false;

// Start a counter using the built in Teensy milliseconds incrementer
// https://www.pjrc.com/teensy/td_timing_elaspedMillis.html
elapsedMillis counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Teensy MIDI CC Example");
  Serial.printf("Version: %d\n", VERSION);
  Serial.printf("MIDI Channel: %d, CC: %d\n", MIDI_CHANNEL, MIDI_CC);
  Serial.println("===");

  pinMode(RESET_PIN, INPUT_PULLUP);
}

void loop() {
  if (counter >= THROTTLE_MS) {
    counter = 0;

    // Check if we need to send a panic reset signal
    uint8_t resetting = processResetPin();

    // If we are not resetting, then proceed with reading the sensor and sending a MIDI value
    if (!resetting) {
      processSensorReading();
    }
  }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

uint8_t processResetPin(){
  uint8_t reset = digitalRead(RESET_PIN);
  if (reset == LOW && lastReset == false) {
    usbMIDI.sendControlChange(MIDI_RESET, 127, MIDI_CHANNEL);
    delay(100);
    usbMIDI.sendControlChange(MIDI_RESET, 0, MIDI_CHANNEL);
    lastReset = true;
    Serial.println("Sent panic MIDI RESET");
  } else if (reset == HIGH && lastReset == true) {
    lastReset = false;
  }

  return lastReset;
}

void processSensorReading() {
  // Pluck the sensor reading from a 16 bit number and map it to a 7 bit number (MIDI is 0...127)
  uint16_t rawReading = analogRead(SENSOR_PIN);
  rawReading = constrain(rawReading, MIN_READING, MAX_READING);
  uint8_t reading = map(rawReading, MIN_READING,  MAX_READING, 0, 127);

  if (INVERT_READING) {
    reading = 127 - reading;
  }

  // only transmit MIDI messages if analog input changed
  if (reading != lastReading) {
    usbMIDI.sendControlChange(MIDI_CC, reading, MIDI_CHANNEL);
    lastReading = reading;
    Serial.printf("%d / %d\n", rawReading, reading);
  }
}
