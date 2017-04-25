// communicating with STM32

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/neutrino.h>
#include <stdint.h>
#include <sys/mman.h>
#include <pthread.h>

#define START_CONV_LSB 0x280 
#define PAGE_MSB 0x281 
#define CHANNEL 0x282 
#define WAIT_GAIN 0x283 
#define POLARITY 0x28D

#define IO_PORT_SIZE 1

uintptr_t start_lsb_handle;
uintptr_t page_msb_handle;
uintptr_t set_channel_handle;
uintptr_t wait_gain_handle;
uintptr_t set_polarity_handle;

void *_adc_gen(void *arg){

	if( ThreadCtl(_NTO_TCTL_IO,NULL) == -1 ) {
		perror("Failed to get I/O access permission.");
		return 1;
	}

	start_lsb_handle = mmap_device_io(IO_PORT_SIZE,START_CONV_LSB);
	// error handle
	page_msb_handle = mmap_device_io(IO_PORT_SIZE,PAGE_MSB);
	// error handle
	set_channel_handle = mmap_device_io(IO_PORT_SIZE,CHANNEL);
	// error handle
	wait_gain_handle = mmap_device_io(IO_PORT_SIZE,WAIT_GAIN);
	// error handle
	set_polarity_handle = mmap_device_io(IO_PORT_SIZE,POLARITY);
	// error handle
}



int main( void ) {
	pthread_t _adc;

	pthread_create(_adc,NULL,_adc_gen,NULL);

	pthread_join(_adc,NULL);

	return 0;
}