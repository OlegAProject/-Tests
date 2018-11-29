#include <ch.h>
#include <hal.h>


PWMConfig pwm1conf = {
    .frequency = 500000,
    .period    = 5000,
    .callback  = NULL,
    .channels  = {
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_ACTIVE_HIGH, NULL},
                  {PWM_OUTPUT_DISABLED, NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

PWMConfig pwm2conf = {
    .frequency = 500000,
    .period    = 5000,
    .callback  = NULL,
    .channels  = {
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_ACTIVE_LOW, NULL},
                  {PWM_OUTPUT_DISABLED, NULL},
                  {PWM_OUTPUT_DISABLED, NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};


int main(void)
{
	int k = 0;
	char f = 1;
    chSysInit();
    halInit();
    palSetLineMode( LINE_LED1, PAL_MODE_ALTERNATE(2) );
    palSetLineMode( LINE_LED2, PAL_MODE_ALTERNATE(2) );
    pwmStart(&PWMD3 , &pwm1conf );
    pwmStart(&PWMD4 , &pwm2conf );

    while (true)
    {
        //k += 500;
        if (k < 5000 && f == 1)
        	{
        		k += 500;
        	}
        else
        {
        	f = 0;
        	k -= 500;
        	if (k <= 0) f = 1;
        }

        pwmEnableChannel(&PWMD3, 2 , k);
        pwmEnableChannel(&PWMD4, 1 , k);

        chThdSleepMilliseconds(10);
    }
}

