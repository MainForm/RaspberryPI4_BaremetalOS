#include "interrupt.h"
#include "HAL_GIC.h"

#include <stddef.h>

static IRQ_Handler_Callback IRQ_Handler_Callbacks[IRQ_MAXIMUM_COUNT];

void IRQ_AttachInterrupt(int gic_num,int irq_num, IRQ_Handler_Callback callback){

    if(IRQ_IsEnableInterrupt(irq_num) == false){
       HAL_GIC_EnableInterrupt(gic_num, irq_num);
    }

    IRQ_Handler_Callbacks[irq_num] = callback;
}

bool IRQ_IsEnableInterrupt(int irq_num){
    return IRQ_Handler_Callbacks[irq_num] != NULL ? true : false;
}

void IRQ_CallHandlerCallback(int irq_num){
    if(IRQ_MAXIMUM_COUNT <= irq_num){
        return;
    }

    if(IRQ_Handler_Callbacks[irq_num] == NULL){
        return;
    }

    IRQ_Handler_Callbacks[irq_num]();
}