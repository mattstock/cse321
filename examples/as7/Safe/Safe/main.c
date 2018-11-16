#include <atmel_start.h>
#include <malloc.h>
#include <string.h>

const uint8_t rows[] = { K_ROW0, K_ROW1, K_ROW2, K_ROW3 };
const uint8_t cols[] = { K_COL0, K_COL1, K_COL2, K_COL3 };

enum { LOCKED, UNLOCKED } state = UNLOCKED;
volatile char keyval;
struct io_descriptor *I2C_0_io;

const unsigned char messages[][17] = {
	"|-",
	"LOCKED",
	"UNLOCKED",
	"ERROR",
	"            "
};

#define MSG_CLEAR 0
#define MSG_LOCKED 1
#define MSG_UNLOCKED 2 
#define MSG_ERROR 3	
#define MSG_SPACING 4

	
const char keys[4][4] = {
	{ '1', '2', '3', 'A' },
	{ '4', '5', '6', 'B' },
	{ '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
};

static void TIMER_0_task1_cb(const struct timer_task *const timer_task) {
	keyval = '\0';
	for (int r=0; r < 4; r++) {
		gpio_set_pin_direction(rows[r], GPIO_DIRECTION_OUT);
		for (int c=0; c < 4; c++)
			if (!gpio_get_pin_level(cols[c])) {
				gpio_set_pin_direction(rows[r], GPIO_DIRECTION_IN);
				keyval = keys[r][c];
			}
	    gpio_set_pin_direction(rows[r], GPIO_DIRECTION_IN);
	}
}

char *get_input() {
	char *mycode;
	uint8_t keycount = 0;
	
	mycode = malloc(4);
	
	while (keycount < 4) {
		while (keyval == '\0');
		mycode[keycount] = keyval;
		io_write(I2C_0_io, (unsigned char *)&keyval, 1);
		keycount++;
		while (keyval != '\0');
	}
	mycode[keycount] = '\0'; // terminate the string
	return mycode;
}

void lcd_clear() {
	/* Clear the display */
	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x72, I2C_M_SEVEN);
	io_write(I2C_0_io, (unsigned char *)"|-", 2);
}

int main(void)
{
	struct timer_task TIMER_0_task1;
	char *code, *tmpcode;
	
	/* Configure all of the HAL stuff */
	atmel_start_init();
	
	pwm_set_parameters(&PWM_0, 2500, 10);
	pwm_enable(&PWM_0);
	
	/* Set up a timer to strobe the keyboard */
	TIMER_0_task1.interval = 100;
	TIMER_0_task1.cb = TIMER_0_task1_cb;
	TIMER_0_task1.mode = TIMER_TASK_REPEAT;
	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_start(&TIMER_0);
	
	code = NULL;
	
	while (1) {
	
		switch (state) {
			case UNLOCKED:
				lcd_clear();
				gpio_set_pin_level(LED_G, true);
				gpio_set_pin_level(LED_Y, true);
				gpio_set_pin_level(LED_R, false);
				code = get_input();
				state = LOCKED;
				io_write(I2C_0_io, messages[MSG_SPACING], strlen(messages[MSG_SPACING]));
				io_write(I2C_0_io, messages[MSG_LOCKED], strlen(messages[MSG_LOCKED]));
				delay_ms(500);
				break;
			case LOCKED:
				lcd_clear();
				gpio_set_pin_level(LED_G, false);
				gpio_set_pin_level(LED_Y, false);
				gpio_set_pin_level(LED_R, true);
				tmpcode = get_input();
				if (!strncmp(code, tmpcode, 4)) {
					io_write(I2C_0_io, messages[MSG_SPACING], strlen(messages[MSG_SPACING]));
					io_write(I2C_0_io, messages[MSG_UNLOCKED], strlen(messages[MSG_UNLOCKED]));
					delay_ms(1000);
					free(code);
					state = UNLOCKED;
				} else {
					io_write(I2C_0_io, messages[MSG_SPACING], strlen(messages[MSG_SPACING]));
					io_write(I2C_0_io, messages[MSG_ERROR], strlen(messages[MSG_ERROR]));
					delay_ms(1000);
				}
				free(tmpcode);
				break;
		}
	}
}
