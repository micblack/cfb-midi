// Example version
const uint8_t VERSION = 1;

// The MIDI channel number to send messages
const uint8_t MIDI_CHANNEL = 1;

// The MIDI message to send
const uint8_t MIDI_CC = MIDI_GENERAL1;

// How frequently to send MIDI instructions (in milliseconds)
const uint8_t THROTTLE_MS = 20;

// Which pins hardware is attached to
const uint8_t SENSOR_PIN = A0;
const uint8_t RESET_PIN = 3;

// Sensor reading ranges

// For Sharp GP2Y0A02YK0F
const uint16_t MIN_READING = 200;
const uint16_t MAX_READING = 800;
const uint8_t INVERT_READING = true;