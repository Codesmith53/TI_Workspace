//-----------------------------------------------------------------------------
// @file: I2C.c
// @brief: Interface file for I2C bus
//
// @details: TI CCP complier support
//
// @copyright: CONFIDENTIAL Property of Jess Fisher Copyright 2018
//
// @All rights reserved: Copying or other reproduction of this program except
// for archival purposes is prohibited without the prior written consent of
// Jess Fisher.
//
// Jess Fisher Copyright, Hoquiam, WA, USA
//
// @author:  Jess Fisher
// @date: 06/26/2018
// @version: 1.0
//
//-----------------------------------------------------------------------------
#include <msp.h>
#include "App.h"
#include "DIO.h"
#include "I2C.h"

uBYTE   I2cTxBuff[I2C_BUFF_SIZE], I2cRecBuff[I2C_BUFF_SIZE];
uBYTE	TxBuffCnt, RecBuffCnt, Transmitting = FALSE, Reciving = FALSE;

//-----------------------------------------------------------------------------
void I2CWriteQueue(uBYTE data)
{
    if(TxBuffCnt == I2C_BUFF_SIZE) TxBuffCnt = 0;

    I2cTxBuff[TxBuffCnt]=data;              // Buffer the data

    EUSCI_B0->IE |= EUSCI_B_IE_TXIE0 |      // Enable transmit interrupt
            EUSCI_B_IE_STPIE;               // Enable stop interrupt

}
//-----------------------------------------------------------------------------
uBYTE I2CReadQueue(void)
{
    uBYTE data = 0;

    if (RecBuffCnt)
    {
        data = (I2cRecBuff[RecBuffCnt]);
    }
	return data;
}
//-----------------------------------------------------------------------------
void I2CReadRdy(uBYTE adx)
{
    // Ensure stop condition got sent
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

   EUSCI_B0->IE |= EUSCI_B_IE_RXIE0 |      // Enable RX interrupt
                   EUSCI_B_IE_STPIE;       // Enable stop interrupt

    // Set Slave address
   if(adx)EUSCI_B0->I2CSA = adx;
   else EUSCI_B0->I2CSA = I2C_SLAVE_ADX;

   // Set RX mode
   EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR;

   // I2C start condition
   EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

}
//-----------------------------------------------------------------------------
uBYTE I2CReadByte(uBYTE adx)
{
    uBYTE rtn = 0;
    uWORD timeout;

    // make sure we are not in process of stopping
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

    // Set Slave address
   if(adx)EUSCI_B0->I2CSA = adx;
   else EUSCI_B0->I2CSA = I2C_SLAVE_ADX;

   // Set RX mode
   EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR;

   // I2C start condition
   EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

   timeout = 0xFFFF;
   while ((EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0) == 0)
   {
       if(--timeout == 0) break;
   }
   rtn = EUSCI_B0->RXBUF;

   return rtn;
}
//-----------------------------------------------------------------------------
void I2CWriteByte(uBYTE adx, uBYTE data)
{
    uWORD timeout;

    P3->OUT = 1;                       // Toggle P3.0 GPIO
    // make sure we are not in process of stopping
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

    // Set Slave address
    if(adx)EUSCI_B0->I2CSA = adx;
    else EUSCI_B0->I2CSA = I2C_SLAVE_ADX;

    // Set TX mode
    EUSCI_B0->CTLW0 |=  EUSCI_B_CTLW0_TR;

    // I2C start condition
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

    // wait for start bit complete to send data
    timeout = 0xFFFF;
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTT)
    {
        if(--timeout == 0) break;
    }

    if(EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG0);  // wait for add tx
    {
       I2cTxBuff[0] = data;
       EUSCI_B0->TXBUF = I2cTxBuff[0];
    }

    P3->OUT ^= BIT0;                       // Toggle P3.0 GPIO
}
//-----------------------------------------------------------------------------
void I2CSetAdxBytes(uBYTE adx, uBYTE num)
{
    EUSCI_B0->TBCNT = num;          // Set number of bytes to be received
    if(adx)EUSCI_B0->I2CSA = adx;   // Set Slave address
    else EUSCI_B0->I2CSA = I2C_SLAVE_ADX;
}
//-----------------------------------------------------------------------------
void I2CInit(void)
{
	TxBuffCnt = 0;
	RecBuffCnt = 0;

    // Configure GPIO
    P1->SEL0 |= BIT6 | BIT7;                // I2C pins

    // Enable global interrupt
    __enable_irq();

    // Enable eUSCIB0 interrupt in NVIC module
    NVIC->ISER[0] = 1 << ((EUSCIB0_IRQn) & 31);

    // Configure USCI_B0 for I2C mode
    EUSCI_B0->CTLW0 |= EUSCI_A_CTLW0_SWRST; // Software reset enabled
    EUSCI_B0->CTLW0 = EUSCI_A_CTLW0_SWRST | // Remain eUSCI in reset mode
            EUSCI_B_CTLW0_MODE_3 |          // I2C mode
            EUSCI_B_CTLW0_MST |             // Master mode
            EUSCI_B_CTLW0_SYNC |            // Sync mode
            EUSCI_B_CTLW0_SSEL__SMCLK;      // SMCLK


    EUSCI_B0->CTLW1 |= EUSCI_B_CTLW1_ASTP_2;// Automatic stop generated
                                            // after EUSCI_B0->TBCNT is reached
    EUSCI_B0->BRW = 30;                     // baudrate = SMCLK / 30 = 100kHz
    EUSCI_B0->TBCNT = 0x0001;               // number of bytes to be received
    EUSCI_B0->I2CSA = I2C_SLAVE_ADX;        // Slave address
    EUSCI_B0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;// Release eUSCI from reset
/*
    EUSCI_B0->IE |= EUSCI_A_IE_RXIE |       // Enable receive interrupt
            EUSCI_B_IE_NACKIE |             // Enable NACK interrupt
            EUSCI_B_IE_BCNTIE;              // Enable byte counter interrupt
*/
    EUSCI_B0->IE |= EUSCI_B_IE_TXIE0 |      // Enable transmit interrupt
            EUSCI_B_IE_STPIE;               // Enable stop interrupt
}
//-----------------------------------------------------------------------------
// This is the I2C isr based upon TI MSP432 series chip. It is configured to run
// real time off an event generated interrupt on I2C dedicated pins
void EUSCIB0_IRQHandler(void)
{
    //----------- Recieve data -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0) // generated when character has been received
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0; // clear bit
//      I2cRecBuff[RecBuffCnt++] = EUSCI_B0->RXBUF; // read data into buffer
//      if (RecBuffCnt >= sizeof(I2cRecBuff)) RecBuffCnt = 0;
    }

    //----------- Transmit data -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG0)    // TX reg is ready after start is issued
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_TXIFG0;  // clear buffer empty interrupt flag
    }

    //----------- Stop interrupt -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_STPIFG)
    {
        // Clear stop condition int flag
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_STPIFG;
    }

    //----------- NO ACK timeout -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_NACKIFG)
    {
      EUSCI_B0->IFG &= ~EUSCI_B_IFG_NACKIFG;
    }

    //----------- Reached byte count -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_BCNTIFG)
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_BCNTIFG;
    }



}
