/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC24FJ128GA310
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.32
        MPLAB             :  MPLAB X 3.61
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

//#include "../../mcc_generated_files/mcc.h"
#include "../includes/includes.h"

/*
                         Main application
 */
int main(void)
{
    uint8_t str[4]={0};
    uint8_t i=0,j=0;
    // initialize the device
    SYSTEM_Initialize();

    lcd_init();
    lcd_disp_clear_buffer();
    lcd_show_string((uint8_t*)"77777777");
    lcd_show_string_sm((uint8_t*)"123");
    lcd_show_string_ex((uint8_t*)"123");
    lcd_disp_refresh();
	asm("NOP");
	ads1148_init_all();
	asm("NOP");    
    ads1148_test();
    while (1)
    {
        // Add your application code
        str[3]='\0';
        str[0]=LCDDigitalIndexTable[i];
        str[1]=LCDDigitalIndexTable[i];
        str[2]=LCDDigitalIndexTable[i];
        lcd_show_string_sm(str);
        str[0]=LCDDigitalTableIndexEx[j];
        str[1]=LCDDigitalTableIndexEx[j];
        str[2]=LCDDigitalTableIndexEx[j];
        lcd_show_string_ex(str);
        i++;
        j++;
        if(i>42-1)i=0;
        if(j>62-1)j=0;
        lcd_disp_refresh();
        delay_ms(300);
        
    }

    return -1;
}
/**
 End of File
*/