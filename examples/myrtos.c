#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define LED_G (1 << PB2)
#define LED_R (1 << PB1)
#define LED_Y (1 << PB0)

/* Three sample tasks, each that just blink a different LED in a delay loop.
 * Since the tasks are being preempted, it's worth noting that the idea that
 * a delay loop will in fact delay for a fixed amount of time goes out the
 * window. */
void task_a(void) {
  while (1) {
    PORTB |= LED_R;
    _delay_ms(1000);
    PORTB &= ~LED_R;
    _delay_ms(1000);
  }
}

void task_b(void) {
  while (1) {
    PORTB |= LED_Y;
    _delay_ms(50);
    PORTB &= ~LED_Y;
    _delay_ms(100);
  }
}

void task_c(void) {
  while (1) {
    PORTB |= LED_G;
    _delay_ms(175);
    PORTB &= ~LED_G;
    _delay_ms(100);
  }
}

volatile uint8_t current_task;
volatile uint8_t **px;
volatile uint8_t *task0_stack;
volatile uint8_t *task1_stack;
volatile uint8_t *task2_stack;

/* The task scheduler.  The trick here is that we need to swap our stack
 * pointer, so that when we return from the ISR, we return to the new task.
 * We also need to save the stack pointer so that we can return again later.
 * The final twist is that we need to save all of the bits of CPU state,
 * and so that's all of the registers.  We set the ISR to be "naked" so that
 * we have total control of the process. */
ISR(TIMER0_COMPA_vect, ISR_NAKED) {
  /* Save all of the execution state to the current stack */
  asm volatile ("push r0\n in r0, __SREG__");
  asm volatile ("push r0");
  asm volatile ("push r1\n clr r1");
  asm volatile ("push r2\n push r3\n push r4\n push r5\n push r6\n push r7");
  asm volatile ("push r8\n push r9\n push r10\n push r11\n push r12");
  asm volatile ("push r13\n push r14\n push r15\n push r16\n push r17");
  asm volatile ("push r18\n push r19\n push r20\n push r21\n push r22");
  asm volatile ("push r23\n push r24\n push r25\n push r26\n push r27");
  asm volatile ("push r28\n push r29\n push r30\n push r31");
  
  switch (current_task) {
  case 0:
    px = &task0_stack;
    break;
  case 1:
    px = &task1_stack;
    break;
  case 2:
    px = &task2_stack;
    break;
  }
  
  /* Save the task's stack pointer */
  asm volatile ("lds r26, px");
  asm volatile ("lds r27, px+1");
  asm volatile ("in r0, __SP_L__\n st x+, r0");
  asm volatile ("in r0, __SP_H__\n st x+, r0");
  
  /* Change task */
  current_task = (current_task + 1) % 3;
  switch (current_task) {
  case 0:
    px = &task0_stack;
    break;
  case 1:
    px = &task1_stack;
    break;
  case 2:
    px = &task2_stack;
    break;
  }
  
  /* Set up new stack location */
  asm volatile ("lds r26, px");
  asm volatile ("lds r27, px+1");
  asm volatile ("ld r0, x+\n out __SP_L__, r0");
  asm volatile ("ld r0, x+\n out __SP_H__, r0");
  
  /* recover previous state */
  asm volatile ("pop r31\n pop r30\n pop r29\n pop r28\n pop r27\n pop r26");
  asm volatile ("pop r25\n pop r24\n pop r23\n pop r22\n pop r21\n pop r20");
  asm volatile ("pop r19\n pop r18\n pop r17\n pop r16\n pop r15\n pop r14");
  asm volatile ("pop r13\n pop r12\n pop r11\n pop r10\n pop r9\n pop r8");
  asm volatile ("pop r7\n pop r6\n pop r5\n pop r4\n pop r3\n pop r2\n pop r1");
  asm volatile ("pop r0\n out __SREG__, r0\n pop r0");
  
  asm volatile ("reti");
}

int main() {
  DDRB = LED_R|LED_Y|LED_G;
  TCCR0B = 0b10; // div 8
  TIMSK = (1 << OCIE0A);
  
  /* the first task will use the default stack */
  current_task = 0;
  px = &task0_stack;
  
  /* for the other two processes, we need to initialize the
   * saved state so that when they are "restored" things
   * work properly.  There are other/better ways to do this,
   * but they add their own complexity.
   *
   * We set the base of the stack (we only have 256 bytes) to
   * space the tasks away from each other a bit, and then fill in
   * the return address (the start of the function), and then
   * initialize all of the registers to 0. */
  task1_stack = (void *)0x200;
  *task1_stack-- = (uint8_t)(((uint16_t)&task_b) & 0xff);
  *task1_stack-- = (uint8_t)(((uint16_t)&task_b) >> 8);
  for (int i=0; i < 33; i++)
    *task1_stack-- = 0x00;
  
  task2_stack = (void *)0x180;
  *task2_stack-- = (uint8_t)(((uint16_t)&task_c) & 0xff);
  *task2_stack-- = (uint8_t)(((uint16_t)&task_c) >> 8);
  for (int i=0; i < 33; i++)
    *task2_stack-- = 0x00;
  
  sei();
  
  task_a();
}
