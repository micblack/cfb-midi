# Teensy MIDI CC

This Arduino sketch can be used to convert an analog value to a MIDI controller value for mapping within your DAW.

# Wiring

Teensy : Sharp GP2Y0A41SK0F

Vin  --> VCC (red)
Gnd  --> GND (black)
A0   --> Signal (yellow)

Teensy : Teensy
3    --> GND (only when sending MIDI reset / to stop sending more MIDI messages)

# Mapping

1. Disconnect digital pin 3 from GND
2. If using Ableton, simply click the MIDI button in the top right of the main project window
3. Now click on the filter you want to map to (eg- volume, frequency of a filter, time of a delay etc)
4. Click the MIDI button again to stop associating a value

# Usage

Bring an object to the GP2Y0A41SK0F sensor and away from it to send MIDI messages to the mapped control element in Ableton.