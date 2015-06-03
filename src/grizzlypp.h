/*
 * grizzlypp.h
 *
 *  Created on: Jun 2, 2015
 *      Author: felix
 */

#ifndef GRIZZLYPP_H_
#define GRIZZLYPP_H_

using namespace std;

#include <libusb-1.0/libusb.h>
extern "C" {
	#include "libgrizzly.h"
}

class Grizzly {
	libusb_device_handle* dev;
	static libusb_device_handle* all_dev[];
	static int dev_cnt;
	static libusb_context* ctx;

	public:
		Grizzly(unsigned char dev_addr);
		~Grizzly();
		void write_registers(unsigned char addr, unsigned char* data, int num);
		void write_single_register(unsigned char addr, unsigned char data);
		void read_registers(unsigned char addr, unsigned char* data, int num);
		unsigned char read_single_register(unsigned char addr);
		int read_as_int(unsigned char addr, int num);
		void write_as_int(unsigned char addr, int val, int num);
		void set_target(float setpoint);
		float read_target(void);
		void set_mode(char cmode, char dmode);
		float read_current(void);
		int read_encoder(void);
		void write_encoder(int new_val);
		void limit_acceleration(int new_val);
		void limit_current(int new_val);
		void init_pid(float kp, float ki, float kd);
		void read_pid_constants(float* constants);
		int enable(void);
		void disable(void);
		static int cleanup_all(int error);
		static unsigned char addr_to_id(unsigned char addr);
		static unsigned char id_to_addr(unsigned char id);
};

#endif /* GRIZZLYPP_H_ */
