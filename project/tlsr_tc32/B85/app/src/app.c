/********************************************************************************************************
 * @file    app.c
 *
 * @brief   This is the source file for Telink MCU
 *
 * @author  Driver Group
 * @date    2018
 *
 * @par     Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#include "app_config.h"


#define NUM_OF_LEDS                         (sizeof(leds) / sizeof(leds[0]))
#define TOGGLE_MS                           245
#define DEBOUNCE_MS                         50

static volatile unsigned char do_debounce = 0;

static unsigned int ms_cnt = 0;
static unsigned int led_idx = 0;

static const GPIO_PinTypeDef leds[] =
{
    LED1,
    LED2,
    LED3,
    LED4,
};


void user_init(void)
{
	/* Initialize the LED pins, for indication */
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        gpio_set_func(leds[i], AS_GPIO);
        gpio_set_output_en(leds[i], 1);   /* enable output */
        gpio_set_input_en(leds[i], 0);     /* disable input */
        gpio_write(leds[i], 0);           /* LED Off */
    }

    /*
     * Button matrix table:
     * 	        KEY3    KEY4
     * 	KEY1    SW2	    SW3
     * 	KEY2    SW4	    SW5
     */

    /* Initialization signal generation output pin */
    gpio_set_func(KEY3 ,AS_GPIO);
    gpio_set_output_en(KEY3, 1);        /* enable output */
    gpio_set_input_en(KEY3 ,0);         /* disable input */

    /* Initialize interrupt detection input pin */
    gpio_set_func(IRQ_PIN, AS_GPIO);
    gpio_set_output_en(IRQ_PIN, 0); 	/* disable output */
    gpio_set_input_en(IRQ_PIN, 1);	    /* enable input */

    /* Configure IRQ_PIN to receive falling edge interrupts. In this way, when
     * KEY3 is pressed, there will be a falling edge on IRQ_PIN.
     */
    gpio_write(KEY3, 0);
    gpio_setup_up_down_resistor(IRQ_PIN, PM_PIN_PULLUP_10K);
    gpio_set_interrupt(IRQ_PIN, POL_FALLING);
    irq_enable();
}


/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////

void main_loop(void)
{
	if (do_debounce) {
		do_debounce = 0;

        sleep_ms(DEBOUNCE_MS);

        if (!gpio_read(IRQ_PIN)) {
            if (++led_idx >= NUM_OF_LEDS) {
                led_idx = 0;
            }
        }
	}
	else {
        sleep_ms(1);
        if (++ms_cnt >= TOGGLE_MS) {

        	if (!do_debounce) {
        	    gpio_toggle(leds[led_idx]);
            }

        	ms_cnt = 0;
        }
	}
}

/**
 * @brief		This function serves to handle the interrupt of MCU
 * @param[in] 	none
 * @return 		none
 */
_attribute_ram_code_sec_noinline_ void irq_handler(void)
{
    if ((reg_irq_src & FLD_IRQ_GPIO_EN) == FLD_IRQ_GPIO_EN) {
        reg_irq_src = FLD_IRQ_GPIO_EN; /* clear the relevant IRQ */

        if (!do_debounce) {
            /* Stop blinking current LED */
            gpio_write(leds[led_idx], 0);

            do_debounce = 1;
        }
	}
}



