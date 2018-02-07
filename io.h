// Wrapper for libComedi I/O.
// These functions provide and interface to libComedi limited to use in
// the real time lab.
//
// 2006, Martin Korsgaard
#ifndef __INCLUDE_IO_H__
#define __INCLUDE_IO_H__



/**
  Initialize libComedi in "Sanntidssalen"
  @return Non-zero on success and 0 on failure
*/
int io_init();



/**
  Sets a digital channel bit.
  @param channel Channel bit to set.
*/
void io_set_bit(int channel);



/**
  Clears a digital channel bit.
  @param channel Channel bit to set.
*/
void io_clear_bit(int channel);



/**
  Writes a value to an analog channel.
  @param channel Channel to write to.
  @param value Value to write.
*/
void io_write_analog(int channel, int value);



/**
  Reads a bit value from a digital channel.
  @param channel Channel to read from.
  @return Value read.
*/
int io_read_bit(int channel);




/**
  Reads a bit value from an analog channel.
  @param channel Channel to read from.
  @return Value read.
*/
int io_read_analog(int channel);

#endif // #ifndef __INCLUDE_IO_H__

