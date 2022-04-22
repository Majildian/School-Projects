/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== gpiointerrupt.c ========
 */
#include <stdint.h>
#include <stddef.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/Timer.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Variables */
enum Morse_States { Morse_Start, Morse_SOS, Morse_OK } Morse_State;
enum Transmit_States { Transmit_S, Transmit_O, Transmit_K, Transmit_CBreak, Transmit_WBreak } Transmit_State;
unsigned char t_Count; // tick counter
unsigned char m_Toggle; // message toggle
unsigned char c_Count; // character counter
unsigned char w_Count; // wait counter for dashes or mixed morse

/*
 *  ======== gpioButtonFxn0 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_0.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn0(uint_least8_t index)
{
    /* Switch messages at next word break */
    m_Toggle = 1;
}

/*
 *  ======== gpioButtonFxn1 ========
 *  Callback function for the GPIO interrupt on CONFIG_GPIO_BUTTON_1.
 *  This may not be used for all boards.
 *
 *  Note: GPIO interrupts are cleared prior to invoking callbacks.
 */
void gpioButtonFxn1(uint_least8_t index)
{
    /* Switch messages at next word break */
    m_Toggle = 1;
}

void tickFct_SOS(){
    switch(Transmit_State) {
        case Transmit_WBreak:
            t_Count++;
            GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            if(t_Count >= 6){
                t_Count = 0;
                c_Count = 0;
                Transmit_State = Transmit_S;
            }
            break;
        case Transmit_CBreak:
            GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            t_Count++;
            if(t_Count >= 3){
                t_Count = 0;
                if(c_Count == 1){
                    Transmit_State = Transmit_O;
                    w_Count = 0;
                }else if(c_Count == 2){
                    Transmit_State = Transmit_S;
                }
            }
            break;
        case Transmit_S:
            t_Count++;
            GPIO_toggle(CONFIG_GPIO_LED_0);
            if(t_Count >= 5){
                t_Count = 0;
                if(c_Count == 0){
                    // First S, move to char break
                    c_Count = 1;
                    Transmit_State = Transmit_CBreak;
                } else {
                    // Second S, move to word break
                    Transmit_State = Transmit_WBreak;
                }

            }
            break;
        case Transmit_O:
            t_Count++;

            // Handle LED timing for dashes
            w_Count++;
            if(w_Count >= 4){
                w_Count = 0;
            }
            if(w_Count == 0 || w_Count == 1){
                GPIO_toggle(CONFIG_GPIO_LED_1);
            }

            if(t_Count >= 11) {
                t_Count = 0;
                c_Count = 2;
                Transmit_State = Transmit_CBreak;
            }
            break;
        default:
            Transmit_State = Transmit_WBreak;
            break;
    }
}

void tickFct_OK(){
    switch(Transmit_State) {
        case Transmit_WBreak:
            t_Count++;
            GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
            if(t_Count >= 6){
                t_Count = 0;
                c_Count = 0;
                w_Count = 0;
                Transmit_State = Transmit_O;
            }
            break;
        case Transmit_CBreak:
            GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
            t_Count++;
            if(t_Count >= 3){
                t_Count = 0;
                if(c_Count == 1){
                    Transmit_State = Transmit_K;
                    w_Count = 0;
                }else{
                    Transmit_State = Transmit_WBreak;
                }
            }
            break;
        case Transmit_O:
            t_Count++;

            // Handle LED timing for dashes
            w_Count++;
            if(w_Count >= 4){
                w_Count = 0;
            }
            if(w_Count == 0 || w_Count == 1){
                GPIO_toggle(CONFIG_GPIO_LED_1);
            }

            if(t_Count >= 11) {
                t_Count = 0;
                c_Count = 1;
                Transmit_State = Transmit_CBreak;

            }
            break;
        case Transmit_K:
            t_Count++;

            if(w_Count == 0 || w_Count == 3 || w_Count == 6){
                GPIO_toggle(CONFIG_GPIO_LED_1);
            }
            if(w_Count == 4 || w_Count == 5){
                GPIO_toggle(CONFIG_GPIO_LED_0);
            }
            w_Count++;

            if(t_Count >= 9){
                t_Count = 0;
                Transmit_State = Transmit_WBreak;
            }

    }
}

/*
 * Callback function for the timer.
 */
void timerCallback(Timer_Handle myHandle, int_fast16_t status)
{
    switch(Morse_State) {
        case Morse_Start:
            Morse_State = Morse_SOS;
            Transmit_State = Transmit_S;
            break;
        case Morse_SOS:
            if(m_Toggle && Transmit_State == Transmit_WBreak){
                m_Toggle = 0;
                Morse_State = Morse_OK;
                // To handle the edge case of changing messages at the last "tick",
                // call the other function here instead of SOS
                tickFct_OK();
            } else {
                tickFct_SOS();
            }
            break;
        case Morse_OK:
            if(m_Toggle && Transmit_State == Transmit_WBreak){
                m_Toggle = 0;
                Morse_State = Morse_SOS;
                // To handle the edge case of changing messages at the last "tick",
                // call the other function here instead of OK
                tickFct_SOS();
            }else {
                tickFct_OK();
            }
            break;
        default:
            Morse_State = Morse_Start;
            break;
    }
}

void initTimer(void)
{
    Timer_Handle timer0;
    Timer_Params params;

    Timer_init();
    Timer_Params_init(&params);
    params.period = 500000;
    params.periodUnits = Timer_PERIOD_US;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;

    timer0 = Timer_open(CONFIG_TIMER_0, &params);

    if (timer0 == NULL) {
        /* Failed to initialized timer */
        while (1) {}
    }

    if (Timer_start(timer0) == Timer_STATUS_ERROR) {
        /* Failed to start timer */
        while (1) {}
    }
}

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();

    /* Configure the LED and button pins */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_LED_1, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);
    GPIO_setConfig(CONFIG_GPIO_BUTTON_0, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

    /* Turn on user LED */
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);

    /* Install Button callback */
    GPIO_setCallback(CONFIG_GPIO_BUTTON_0, gpioButtonFxn0);

    /* Enable interrupts */
    GPIO_enableInt(CONFIG_GPIO_BUTTON_0);

    /*
     *  If more than one input pin is available for your device, interrupts
     *  will be enabled on CONFIG_GPIO_BUTTON1.
     */
    if (CONFIG_GPIO_BUTTON_0 != CONFIG_GPIO_BUTTON_1) {
        /* Configure BUTTON1 pin */
        GPIO_setConfig(CONFIG_GPIO_BUTTON_1, GPIO_CFG_IN_PU | GPIO_CFG_IN_INT_FALLING);

        /* Install Button callback */
        GPIO_setCallback(CONFIG_GPIO_BUTTON_1, gpioButtonFxn1);
        GPIO_enableInt(CONFIG_GPIO_BUTTON_1);
    }

    t_Count = 0;
    m_Toggle = 0;
    Morse_State = Morse_Start;
    Transmit_State = Transmit_WBreak;
    GPIO_write(CONFIG_GPIO_LED_1, CONFIG_GPIO_LED_OFF);
    GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
    initTimer();

    return (NULL);
}
