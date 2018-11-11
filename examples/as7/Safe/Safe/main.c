#include <atmel_start.h>

const uint8_t rows[] = { K_ROW0, K_ROW1, K_ROW2, K_ROW3 };
const uint8_t cols[] = { K_COL0, K_COL1, K_COL2, K_COL3 };

volatile char v = '\0';

const char keys[4][4] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
};

static void TIMER_0_task1_cb(const struct timer_task *const timer_task) {
	v = '\0';
	for (int r=0; r < 4; r++) {
		gpio_set_pin_direction(rows[r], GPIO_DIRECTION_OUT);
		for (int c=0; c < 4; c++)
		  if (!gpio_get_pin_level(cols[c])) {
			gpio_set_pin_direction(rows[r], GPIO_DIRECTION_IN);
			v = keys[r][c];
		  }
	    gpio_set_pin_direction(rows[r], GPIO_DIRECTION_IN);
	}
}

int main(void)
{
	struct io_descriptor *I2C_0_io;
	struct timer_task TIMER_0_task1;
	
	/* Configure all of the HAL stuff */
	atmel_start_init();
	
	/* Set up a timer to strobe the keyboard */
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb = TIMER_0_task1_cb;
	TIMER_0_task1.mode = TIMER_TASK_REPEAT;
	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_start(&TIMER_0);
	
	/* Clear the display */
	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x72, I2C_M_SEVEN);
	io_write(I2C_0_io, (unsigned char *)"|-", 2);
	
	while (1) {
		gpio_set_pin_level(LED_R, true);
		gpio_set_pin_level(LED_G, true);
		gpio_set_pin_level(LED_Y, true);
		
		unsigned char c = v;
		if (c != '\0') {
			gpio_set_pin_level(LED_B, true);
		    io_write(I2C_0_io, &c, 1);
		}
		delay_ms(40);
	}
}
