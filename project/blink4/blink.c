/*
 * Copyright (c) 2006, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * $Id: hello-world.c,v 1.1 2006/10/02 21:46:46 adamdunkels Exp $
 */

/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "dev/serial-line.h"
#include "dev/rs232.h"
#include "dev/leds.h"

#include <stdio.h> /* For printf() */
/*---------------------------------------------------------------------------*/
PROCESS(echo_process, "Echo process");
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(echo_process, ev, data)
{
  PROCESS_BEGIN();

  //static struct etimer t;
  //etimer_set(&t, 3*CLOCK_SECOND);
  rs232_set_input(RS232_PORT_0, serial_line_input_byte);
  while(1) {
	PROCESS_WAIT_EVENT_UNTIL(ev == serial_line_event_message);
	//printf("%s\n", (char*)data);
	printf("hello\n");
	//etimer_reset(&t);
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
PROCESS(blink_process, "Blink process");
//AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data)
{
  PROCESS_BEGIN();

  static struct etimer t;
  etimer_set(&t, CLOCK_SECOND);
  while(1) {
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&t));
	leds_toggle(LEDS_BLUE);
	etimer_reset(&t);
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
PROCESS(blink2_process, "Blink2 process");
AUTOSTART_PROCESSES(&blink_process, &blink2_process, &echo_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink2_process, ev, data)
{
  PROCESS_BEGIN();

printf("hello blink4\n");
  static struct etimer t;
  etimer_set(&t, 2*CLOCK_SECOND);
  while(1) {
	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&t));
	leds_toggle(LEDS_GREEN);
	printf("hello!\n");
	etimer_reset(&t);
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
