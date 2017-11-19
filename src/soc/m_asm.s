.section .text
.global _flash_unlock_pm
_flash_unlock_pm:
	push	W0
	disi	#5
	mov		#0x55,W0
	mov		W0, NVMKEY
	mov		#0xAA, W0
	mov		W0, NVMKEY
	bset	NVMCON, #15
	nop
	nop
	btsc	NVMCON, #15
	bra		$-2
	pop		W0
	return	
.end