// Wrapper for libComedi I/O.
// These functions provide and interface to libComedi limited to use in
// the real time lab.
//
// 2006, Martin Korsgaard


#include "io.h"
#include "channels.h"

#include <comedilib.h>


static comedi_t *it_g = NULL;



int io_init() {
    int i = 0;
    int status = 0;

    it_g = comedi_open("/dev/comedi0");

    if (it_g == NULL)
        return 0;

    for (i = 0; i < 8; i++) {
        status |= comedi_dio_config(it_g, PORT1, i, COMEDI_INPUT);
        status |= comedi_dio_config(it_g, PORT2, i, COMEDI_OUTPUT);
        status |= comedi_dio_config(it_g, PORT3, i + 8, COMEDI_OUTPUT);
        status |= comedi_dio_config(it_g, PORT4, i + 16, COMEDI_INPUT);
    }

    return (status == 0);
}



void io_set_bit(int channel) {
    comedi_dio_write(it_g, channel >> 8, channel & 0xff, 1);
}



void io_clear_bit(int channel) {
    comedi_dio_write(it_g, channel >> 8, channel & 0xff, 0);
}



void io_write_analog(int channel, int value) {
    comedi_data_write(it_g, channel >> 8, channel & 0xff, 0, AREF_GROUND, value);
}



int io_read_bit(int channel) {
    unsigned int data = 0;
    comedi_dio_read(it_g, channel >> 8, channel & 0xff, &data);

    return (int)data;
}



int io_read_analog(int channel) {
    lsampl_t data = 0;
    comedi_data_read(it_g, channel >> 8, channel & 0xff, 0, AREF_GROUND, &data);

    return (int)data;
}
