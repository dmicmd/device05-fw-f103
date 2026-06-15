.syntax unified
.cpu cortex-m3
.thumb

.global g_pfnVectors
.global Reset_Handler

/* Stack top from linker */
.word _estack

/* Vector table */
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
g_pfnVectors:

.word _estack
.word Reset_Handler
.word NMI_Handler
.word HardFault_Handler
.word MemManage_Handler
.word BusFault_Handler
.word UsageFault_Handler
.word 0
.word 0
.word 0
.word 0
.word SVC_Handler
.word DebugMon_Handler
.word 0
.word PendSV_Handler
.word SysTick_Handler

/* External interrupts (minimal) */
.word 0 /* WWDG */
.word 0 /* PVD */
.word 0 /* TAMPER */
.word 0 /* RTC */
.word 0 /* FLASH */
.word 0 /* RCC */
.word 0 /* EXTI0 */
.word 0 /* EXTI1 */
.word 0 /* EXTI2 */
.word 0 /* EXTI3 */
.word 0 /* EXTI4 */

.type Reset_Handler, %function
Reset_Handler:
    bl main
1:  b 1b

/* Default handlers */
.weak NMI_Handler
.thumb_set NMI_Handler,Default_Handler
.weak HardFault_Handler
.thumb_set HardFault_Handler,Default_Handler
.weak MemManage_Handler
.thumb_set MemManage_Handler,Default_Handler
.weak BusFault_Handler
.thumb_set BusFault_Handler,Default_Handler
.weak UsageFault_Handler
.thumb_set UsageFault_Handler,Default_Handler
.weak SVC_Handler
.thumb_set SVC_Handler,Default_Handler
.weak DebugMon_Handler
.thumb_set DebugMon_Handler,Default_Handler
.weak PendSV_Handler
.thumb_set PendSV_Handler,Default_Handler
.weak SysTick_Handler
.thumb_set SysTick_Handler,Default_Handler

Default_Handler:
    b .
