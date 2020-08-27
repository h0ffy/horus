[BITS 64]
	_x64gate:
		;xor rax, rax
		;jmp +6
		;db "Gurru",0
		;nop
		push 0x33FFFFFF
		call +5
		add dword [esp], 5
		retf
		pop rax		
	