.include "xc.inc"

.set Fcy,        40000000

.set US_K,       Fcy/1000000
.set MS_K,       Fcy/10000

    .global _Delay
    .global _Delay_Us

;===============================================
; ms Delay Function
;===============================================
_Delay:

ms_oloop:
    mov #MS_K,w1
ms_iloop:
    nop
    nop
    nop
    nop
    nop

    nop
    nop


    dec     w1, w1
    bra     nz, ms_iloop    
    
    dec     w0,w0
    bra     nz,ms_oloop

    return

;===============================================
; us Delay Function
;===============================================

_Delay_Us:

us_oloop:
    
    .rept (US_K-3)
    nop
    .endr
 
    
    dec     w0,w0
    bra     nz,us_oloop

    return
