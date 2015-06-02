/*
 * grizzlypp.cpp
 *
 *  Created on: May 29, 2015
 *      Author: felix
 */
using namespace std;

#include <libusb-1.0/libusb.h>
extern "C" {
	#include "libgrizzly.h"
}

class Grizzly {
	libusb_device_handle* dev;
	static libusb_device_handle* all_dev[10];
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
int Grizzly::dev_cnt = 0;
libusb_context* Grizzly::ctx = NULL;

Grizzly::Grizzly(unsigned char dev_addr) {
	if (ctx == NULL) {
		int result = libusb_init(&ctx);
		if (0 > result)
		{
			fprintf(stderr, "libusb_init() failed with %d.\n", result);
			libusb_exit(ctx);
			return;
		}
	}

	dev = find_grizzly(ctx, dev_addr);
	all_dev[dev_cnt++] = dev;
}

Grizzly::~Grizzly() {
	grizzly_exit(dev);
}

void Grizzly::write_registers(unsigned char addr, unsigned char* data, int num) {
	grizzly_write_registers(dev, addr, data, num);
}

void Grizzly::write_single_register(unsigned char addr, unsigned char data) {
	grizzly_write_single_register(dev, addr, data);
}

void Grizzly::read_registers(unsigned char addr, unsigned char* data, int num) {
	grizzly_read_registers(dev, addr, data, num);
}

unsigned char Grizzly::read_single_register(unsigned char addr) {
	return grizzly_read_single_register(dev, addr);
}

int Grizzly::read_as_int(unsigned char addr, int num) {
	return grizzly_read_as_int(dev, addr, num);
}

void Grizzly::write_as_int(unsigned char addr, int val, int num) {
	grizzly_write_as_int(dev, addr, val, num);
}

void Grizzly::set_target(float setpoint) {
	grizzly_set_target(dev, setpoint);
}

void Grizzly::set_mode(char cmode, char dmode) {
	grizzly_set_mode(dev, cmode, dmode);
}

float Grizzly::read_current() {
	return grizzly_read_current(dev);
}

int Grizzly::read_encoder() {
	return grizzly_read_encoder(dev);
}

void Grizzly::write_encoder(int new_val) {
	grizzly_write_encoder(dev, new_val);
}

void Grizzly::limit_acceleration(int new_val) {
	grizzly_limit_acceleration(dev, new_val);
}

void Grizzly::limit_current(int new_val) {
	grizzly_limit_current(dev, new_val);
}

void Grizzly::init_pid(float kp, float ki, float kd) {
	grizzly_init_pid(dev, kp, ki, kd);
}

void Grizzly::read_pid_constants(float* constants) {
	grizzly_read_pid_constants(dev, constants);
}

int Grizzly::enable(void) {
	return grizzly_enable(dev);
}

void Grizzly::disable(void) {
	grizzly_disable(dev);
}

static int Grizzly::cleanup_all(int error) {
	for (int i = 0; i < dev_cnt; i++) {
		grizzly_exit(all_dev[i]);
	}
	libusb_exit(ctx);
	return error;
}

unsigned char Grizzly::addr_to_id(unsigned char addr) {
	return grizzly_addr_to_id(addr);
}

unsigned char Grizzly::id_to_addr(unsigned char id) {
	return grizzly_id_to_addr(id);
}
