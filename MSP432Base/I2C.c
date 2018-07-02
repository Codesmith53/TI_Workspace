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
uBYTE	TxBuffCnt, RecBuffCnt;

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
uBYTE I2CReadRdy(void)
{
    // Ensure stop condition got sent
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

    EUSCI_B0->CTLW0 &= ~EUSCI_B_CTLW0_TR;   // Set RX mode

    EUSCI_B0->IE |= EUSCI_B_IE_RXIE0 |      // Enable RX interrupt
            EUSCI_B_IE_STPIE;               // Enable stop interrupt

    // I2C start condition
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;

    return 1;
}
//-----------------------------------------------------------------------------
void I2CWriteByte(uBYTE adx, uBYTE data)
{
    while (EUSCI_B0->CTLW0 & EUSCI_B_CTLW0_TXSTP);

    EUSCI_B0->CTLW0 |=  EUSCI_B_CTLW0_TR;  // Set TX mode

    if(adx)EUSCI_B0->I2CSA = adx;        // Slave address
    else EUSCI_B0->I2CSA = I2C_SLAVE_ADX;

    EUSCI_B0->TXBUF = data;

    // I2C start condition
    EUSCI_B0->CTLW0 |= EUSCI_B_CTLW0_TXSTT;


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

    //    EUSCI_B_CTLW0_TR |              // Transmit enabled

    EUSCI_B0->CTLW1 |= EUSCI_B_CTLW1_ASTP_2;// Automatic stop generated
                                            // after EUSCI_B0->TBCNT is reached
    EUSCI_B0->BRW = 30;                     // baudrate = SMCLK / 30 = 100kHz
    EUSCI_B0->TBCNT = 0x0001;               // number of bytes to be received
    EUSCI_B0->I2CSA = I2C_SLAVE_ADX;        // Slave address
    EUSCI_B0->CTLW0 &= ~EUSCI_A_CTLW0_SWRST;// Release eUSCI from reset

    EUSCI_B0->IE |= EUSCI_A_IE_RXIE |       // Enable receive interrupt
            EUSCI_B_IE_NACKIE |             // Enable NACK interrupt
            EUSCI_B_IE_BCNTIE;              // Enable byte counter interrupt

}

//-----------------------------------------------------------------------------
// This is the I2C isr based upon TI MSP432 series chip. It is configured to run
// real time off an event generated interrupt on I2C dedicated pins
void EUSCIB0_IRQHandler(void)
{
    P3->OUT ^= BIT0;                    // Toggle P3.0 GPIO

    //----------- Recieve data -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_NACKIFG)
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_NACKIFG;
    }

    if (EUSCI_B0->IFG & EUSCI_B_IFG_RXIFG0)
    {
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_RXIFG0;
        // Get RX data
        I2cRecBuff[RecBuffCnt++] = EUSCI_B0->RXBUF;
        if (RecBuffCnt >= sizeof(I2cRecBuff)) RecBuffCnt = 0;
    }

    if (EUSCI_B0->IFG & EUSCI_B_IFG_BCNTIFG) EUSCI_B0->IFG &= ~EUSCI_B_IFG_BCNTIFG;

    //----------- Transmit data -------------------------
    if (EUSCI_B0->IFG & EUSCI_B_IFG_STPIFG)    // Stop interrupt rec
    {
        // Clear stop condition int flag
        EUSCI_B0->IFG &= ~EUSCI_B_IFG_STPIFG;
    }

    if (EUSCI_B0->IFG & EUSCI_B_IFG_TXIFG0)    // Tx buffer empty
    {
        // Only transmit the data if it is less than the
        // transmit data size
        if (TxBuffCnt < I2C_BUFF_SIZE)
        {
            EUSCI_B0->TXBUF = I2cTxBuff[TxBuffCnt++];
            if(TxBuffCnt >= I2C_BUFF_SIZE) TxBuffCnt = 0;
        }
        else
        {
            // Else load a dummy byte which does not get clocked out
            // as the STOP bit will get triggered on the last byte
            // since the TXBUF is double buffered
            EUSCI_B0->TXBUF = 0;
        }

        TxBuffCnt++;
    }

    P3->OUT ^= BIT0;                    // Toggle P3.0 GPIO
}
