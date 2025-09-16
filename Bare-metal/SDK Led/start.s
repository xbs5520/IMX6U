
.global _start

_start:
# change to SVC mode
# read cpsr to r0
    mrs r0, cpsr        
# clear bit 0 - 4 11111 0X1f (not change other bit)
    bic r0, r0, #0X1f
# set bit 4 - 0 10011 0X13
    orr r0, r0, #0X13
# write to cpsr
    msr cpsr, r0
# set stack point
    ldr sp, =0X80200000
# go to main
    b main
