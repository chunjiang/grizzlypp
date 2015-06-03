/*
 * grizzlytest.c
 *
 *  Created on: May 26, 2015
 *      Author: felix
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "grizzlypp.h"

int main(void) {
	printf("Testing grizzlypp\n");
	Grizzly g(0x0f);
	if (!g.enable()) {
		printf("Failed to enable.\n");
	}

	g.set_mode(CMODE_NO_PID, DMODE_DRIVE_COAST);
	g.set_target(0);

	g.limit_acceleration(20);
	g.limit_current(1);

	g.init_pid(5,3,1);
	float pidconstants[3];
	g.read_pid_constants(pidconstants);
	printf("kP: %d, kI: %d, kD: %d\n", (int)pidconstants[0], (int)pidconstants[1], (int)pidconstants[2]);

	int s = 0;
	while(1) {
		g.set_target(-s);

		unsigned char mode = g.read_single_register(ADDR_MODE_RO);
		float current = g.read_current();
		int ticks = g.read_encoder();
		int speed = g.read_target();
		printf("Mode: %d, Speed: %d, Current: %f, Count: %d\n", mode, speed, current, ticks);

		if (s >= 100) {
			g.set_target(0);
			return Grizzly::cleanup_all(0);
		} else {
			s += 5;
		}
		sleep(1);
	}
	return Grizzly::cleanup_all(0);
}
