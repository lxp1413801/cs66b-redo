#include "../includes/includes.h"
volatile uint16_t event=0x00;
volatile uint8_t keyEventCount=0x00;
volatile uint16_t noEventTimeOut=NO_EVENT_TIME_MAX;
/*
void send_event_group_isr(EventGroupHandle_t eventGroup,EventBits_t bits)
{
	BaseType_t xHigherPriorityTaskWoken, xResult;
	xHigherPriorityTaskWoken = pdFALSE;
	xResult = xEventGroupSetBitsFromISR(eventGroup,	bits,&xHigherPriorityTaskWoken );
	if( xResult != pdFAIL ){
	  //portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}   
}

void send_event_group(EventGroupHandle_t eventGroup,EventBits_t bits)
{
	EventBits_t uxBits;
	uxBits=xEventGroupSetBits(eventGroup,bits);
}

void send_thread_main_event(uint16_t bits)
{
    if(threadMainEvent!=NULL){
    //xEventGroupSetBits(threadMainEvent,(EventBits_t)bits);
        xEventGroupSetBitsFromISR(threadMainEvent,(EventBits_t)bits,NULL);
    }

}


*/

void send_thread_main_event_key_down(void)
{
	event |= flg_KEY_DOWN;
	if(keyEventCount<32)keyEventCount++;
}