/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    mcc.c

  @Summary:
    This is the mcc.c file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.35
        Device            :  PIC24FJ128GA310
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.31
        MPLAB             :  MPLAB X 3.60
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F    // Deep Sleep Watchdog Timer Postscale Select bits->1:68719476736 (25.7 Days)
#pragma config DSWDTOSC = LPRC    // DSWDT Reference Clock Select->DSWDT uses LPRC as reference clock
#pragma config DSBOREN = ON    // Deep Sleep BOR Enable bit->DSBOR Enabled
#pragma config DSWDTEN = ON    // Deep Sleep Watchdog Timer Enable->DSWDT Enabled
#pragma config DSSWEN = ON    // DSEN Bit Enable->Deep Sleep is controlled by the register bit DSEN

// CONFIG3
#pragma config WPFP = WPFP127    // Write Protection Flash Page Segment Boundary->Page 127 (0x1FC00)
#pragma config VBTBOR = ON    // VBAT BOR enable bit->VBAT BOR enabled
#pragma config SOSCSEL = ON    // SOSC Selection bits->SOSC circuit selected
#pragma config WDTWIN = PS25_0    // Watch Dog Timer Window Width->Watch Dog Timer Window Width is 25 percent
#pragma config BOREN = ON    // Brown-out Reset Enable->Brown-out Reset Enable
#pragma config WPDIS = WPDIS    // Segment Write Protection Disable->Disabled
#pragma config WPCFG = WPCFGDIS    // Write Protect Configuration Page Select->Disabled
#pragma config WPEND = WPENDMEM    // Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMD = HS    // Primary Oscillator Select->HS Oscillator Enabled
#pragma config BOREN1 = EN    // BOR Override bit->BOR Enabled [When BOREN=1]
#pragma config IOL1WAY = ON    // IOLOCK One-Way Set Enable bit->Once set, the IOLOCK bit cannot be cleared
#pragma config OSCIOFCN = ON    // OSCO Pin Configuration->OSCO/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSDCMD    // Clock Switching and Fail-Safe Clock Monitor Configuration bits->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = PRI    // Initial Oscillator Select->Primary Oscillator (XT, HS, EC)
#pragma config ALTVREF = DLT_AV_DLT_CV    // Alternate VREF/CVREF Pins Selection bit->Voltage reference input, ADC =RA9/RA10 Comparator =RA9,RA10
#pragma config IESO = ON    // Internal External Switchover->Enabled

// CONFIG1
#pragma config WDTPS = PS1024    // Watchdog Timer Postscaler Select->1:1024
#pragma config FWPSA = PR32    // WDT Prescaler Ratio Select->1:32
#pragma config FWDTEN = WDT_DIS    // Watchdog Timer Enable->WDT disabled in hardware; SWDTEN bit disabled
#pragma config WINDIS = OFF    // Windowed WDT Disable->Standard Watchdog Timer
#pragma config ICS = PGx3    // Emulator Pin Placement Select bits->Emulator functions are shared with PGEC3/PGED3
#pragma config LPCFG = OFF    // Low power regulator control->Disabled
#pragma config GWRP = OFF    // General Segment Write Protect->Disabled
#pragma config GCP = OFF    // General Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    // JTAG Port Enable->Disabled

#include "mcc.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    INTERRUPT_Initialize();
    TMR2_Initialize();
    TMR1_Initialize();
    RTCC_Initialize();
}

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC PRI; SOSCEN enabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0202 & 0x00FF));
    // RCDIV FRC/1; DOZE 1:1; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x0000;
    // TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL disabled; RODIV Base clock value/16384; ROSSLP disabled; 
    REFOCON = 0x0E00;
}

/**
 End of File
*/