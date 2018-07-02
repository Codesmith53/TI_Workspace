//-----------------------------------------------------------------------------
// @file: main.c
// @brief: Application main and startup
//
// @details: This is an TI version compiled in CCP.
// @copyright: CONFIDENTIAL Property of Jess Fisher Copyright 2018
//
// @All rights reserved: Copying or other reproduction of this program except
// for archival purposes is prohibited without the prior written consent of
// Jess Fisher.
//
// Jess Fisher Copyright, Hoquiam, WA, USA
//
// @author:  Jess Fisher
// @date: 05/16/2018
// @version: 1.0
//
//-----------------------------------------------------------------------------
#include <msp.h>
#include <stdint.h>
#include "App.h"
#include "I2C.h"

#define TIMER_ISR_CNT 3000

// timer flags
uBYTE T50mSFlag;
uBYTE T100mSFlag;
uBYTE T250mSFlag;
uBYTE T1SFlag;
uBYTE SystemPwr;

uBYTE TaskCount1ms;
uBYTE TaskCount5ms;
uBYTE TaskCount50ms;
uBYTE TaskCount100ms;
uBYTE TaskCount250ms;
uBYTE TaskCount1sec;
uWORD SystemFaults;

//-----------------------------------------------------------------------------
void IoInit(void)
{

    //    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;             // Stop WDT
    // Configure the watchdog timer to timeout every ~250ms
    WDT_A->CTL = WDT_A_CTL_PW |WDT_A_CTL_IS_5;

    P1->DIR |= BIT0;                        // P1.0 set as output
    P3->DIR |= BIT0;                        // P3.0 set as output
}
//-----------------------------------------------------------------------------
void TaskInit(void)
{
    T50mSFlag=TRUE;
    T100mSFlag=FALSE;
    T250mSFlag=FALSE;
    T1SFlag=FALSE;

    TaskCount50ms = 4;
    TaskCount100ms = 9;
    TaskCount250ms = 24;
    TaskCount1sec = 99;
}
//-----------------------------------------------------------------------------
void TaskCounter(void)
{
    static uBYTE timercnt = 10;
    timercnt--; // timer running at 1msec

    if(timercnt == 0)
    {
        timercnt = 10;

        //50mSec
        if(!TaskCount50ms)
        {
            TaskCount50ms=4;
            T50mSFlag=TRUE;
        }
        else TaskCount50ms--;

        //100mSec Task Counter, Task step
        if(!TaskCount100ms)
        {
            TaskCount100ms=9;
            T100mSFlag=TRUE;
        }
        else TaskCount100ms--;

        //250mSec Task Counter, Task step
        if(!TaskCount250ms)
        {
            TaskCount250ms=24;
            T250mSFlag=TRUE;
        }
        else TaskCount250ms--;

        //1Sec Task Counter, Task step
        if(!TaskCount1sec)
        {
            TaskCount1sec=99;
            T1SFlag=TRUE;
        }
        else TaskCount1sec--;

    }
}
//-----------------------------------------------------------------------------
void TimerInit(void)
{
    // Enable global interrupt
    __enable_irq();

    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);

    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;     // TACCR0 interrupt enabled
    TIMER_A0->CCR[0] = TIMER_ISR_CNT;
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK |   // SMCLK, UP mode
            TIMER_A_CTL_MC__UP;

}
//-----------------------------------------------------------------------------
// This is the heartbeat of the system. It is configured to run real time off a
// timer generated interrupt at 1 millisecond
void TA0_0_IRQHandler(void)
{
    // Clear the compare interrupt flag
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    TaskCounter();
}
//-----------------------------------------------------------------------------
void setup()
{
    IoInit();
    TaskInit();
    SystemPwr = OFF;
    SystemFaults = FALSE;

    // Init and enable timer allowing task timing
    TimerInit();
    // Init I2C communication
    I2CInit();

    // Application init to be call last after rest of system init is complete
    // AppInit();

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
    volatile uBYTE rx_test,tx_test=0x55;

    setup();

    //main loop
    while(1)
    {
        if(T50mSFlag)
        {
            I2CWriteByte(I2C_SLAVE_ADX, tx_test);
            T50mSFlag = FALSE;

        }
        else if(T100mSFlag)
        {
            uBYTE dmy = I2CReadRdy();
            rx_test = I2CReadQueue();
            T100mSFlag = FALSE;
        }
        else if(T250mSFlag)
        {
            T250mSFlag = FALSE;
        }
        else if(T1SFlag)
        {
            P1->OUT ^= BIT0;                    // Blink P1.0 HeartbeatLED
            T1SFlag=FALSE;
        }


        WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_CNTCL | WDT_A_CTL_IS_5; // Pet the dog
    }
}


