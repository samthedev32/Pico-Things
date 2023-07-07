#ifndef VirtualWire_h
#define VirtualWire_h

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/clocks.h"
#include "hardware/timer.h"

#include <string.h>

// typedef unsigned int uint8_t;

// These defs cause trouble on some versions of Arduino
#undef abs
#undef double
#undef round

/// Maximum number of bytes in a message, counting the byte count and FCS
#define VW_MAX_MESSAGE_LEN 30

/// The maximum payload length
#define VW_MAX_PAYLOAD VW_MAX_MESSAGE_LEN - 3

/// The size of the receiver ramp. Ramp wraps modulu this number
#define VW_RX_RAMP_LEN 160

/// Number of samples per bit
#define VW_RX_SAMPLES_PER_BIT 8

// Ramp adjustment parameters
// Standard is if a transition occurs before VW_RAMP_TRANSITION (80) in the ramp,
// the ramp is retarded by adding VW_RAMP_INC_RETARD (11)
// else by adding VW_RAMP_INC_ADVANCE (29)
// If there is no transition it is adjusted by VW_RAMP_INC (20)
/// Internal ramp adjustment parameter
#define VW_RAMP_INC (VW_RX_RAMP_LEN / VW_RX_SAMPLES_PER_BIT)
/// Internal ramp adjustment parameter
#define VW_RAMP_TRANSITION VW_RX_RAMP_LEN / 2
/// Internal ramp adjustment parameter
#define VW_RAMP_ADJUST 9
/// Internal ramp adjustment parameter
#define VW_RAMP_INC_RETARD (VW_RAMP_INC - VW_RAMP_ADJUST)
/// Internal ramp adjustment parameter
#define VW_RAMP_INC_ADVANCE (VW_RAMP_INC + VW_RAMP_ADJUST)

/// Outgoing message bits grouped as 6-bit words
/// 36 alternating 1/0 bits, followed by 12 bits of start symbol
/// Followed immediately by the 4-6 bit encoded byte count,
/// message buffer and 2 byte FCS
/// Each byte from the byte count on is translated into 2x6-bit words
/// Caution, each symbol is transmitted LSBit first,
/// but each byte is transmitted high nybble first
#define VW_HEADER_LEN 8

// Cant really do this as a real C++ class, since we need to have
// an ISR
/// Set the digital IO pin to be for transmit data.
/// This pin will only be accessed if
/// the transmitter is enabled
/// \param[in] pin The Arduino pin number for transmitting data. Defaults to 12.
extern void vw_set_tx_pin(uint8_t pin);

/// Set the digital IO pin to be for receive data.
/// This pin will only be accessed if
/// the receiver is enabled
/// \param[in] pin The Arduino pin number for receiving data. Defaults to 11.
extern void vw_set_rx_pin(uint8_t pin);

// Set the digital IO pin to enable the transmitter (press to talk, PTT)'
/// This pin will only be accessed if
/// the transmitter is enabled
/// \param[in] pin The Arduino pin number to enable the transmitter. Defaults to 10.
extern void vw_set_ptt_pin(uint8_t pin);

/// By default the PTT pin goes high when the transmitter is enabled.
/// This flag forces it low when the transmitter is enabled.
/// \param[in] inverted True to invert PTT
extern void vw_set_ptt_inverted(uint8_t inverted);

/// Initialise the VirtualWire software, to operate at speed bits per second
/// Call this one in your setup() after any vw_set_* calls
/// Must call vw_rx_start() before you will get any messages
/// \param[in] speed Desired speed in bits per second
extern void vw_setup(uint16_t speed);

/// Start the Phase Locked Loop listening to the receiver
/// Must do this before you can receive any messages
/// When a message is available (good checksum or not), vw_have_message();
/// will return true.
extern void vw_rx_start();

/// Stop the Phase Locked Loop listening to the receiver
/// No messages will be received until vw_rx_start() is called again
/// Saves interrupt processing cycles
extern void vw_rx_stop();

/// Returns the state of the
/// transmitter
/// \return true if the transmitter is active else false
extern uint8_t vx_tx_active();

/// Block until the transmitter is idle
/// then returns
extern void vw_wait_tx();

/// Block until a message is available
/// then returns
extern void vw_wait_rx();

/// Block until a message is available or for a max time
/// \param[in] milliseconds Maximum time to wait in milliseconds.
/// \return true if a message is available, false if the wait timed out.
extern uint8_t vw_wait_rx_max(unsigned long milliseconds);

/// Send a message with the given length. Returns almost immediately,
/// and message will be sent at the right timing by interrupts
/// \param[in] buf Pointer to the data to transmit
/// \param[in] len Number of octetes to transmit
/// \return true if the message was accepted for transmission, false if the message is too long (>VW_MAX_MESSAGE_LEN - 3)
extern uint8_t vw_send(uint8_t *buf, uint8_t len);

// Returns true if an unread message is available
/// \return true if a message is available to read
extern uint8_t vw_have_message();

// If a message is available (good checksum or not), copies
// up to *len octets to buf.
/// \param[in] buf Pointer to location to save the read data (must be at least *len bytes.
/// \param[in,out] len Available space in buf. Will be set to the actual number of octets read
/// \return true if there was a message and the checksum was good
extern uint8_t vw_get_message(uint8_t *buf, uint8_t *len);

#endif
