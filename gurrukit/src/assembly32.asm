[BITS 32]
	segment .text

	global _find_kernel32
	global _find_function32
	global _random_byte
	global _GetCPUID
	global _nGetCPUID
	global _iswOw64
	global _getsystem_imagebase
	
	;
	;	Retreive API Functions
	;
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			  ; Get kernel base + find function by HASH.
			  ; Use modified "GREY-CORNER" method
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			_find_kernel32:
				xor ecx, ecx			; set ecx to 0
				mov esi, [fs:ecx + 0x30]	; esi = &(PEB) ([FS:0x30])
				mov esi, [esi + 0x0C]		; esi = PEB->Ldr
				mov esi, [esi + 0x1C]		; esi = PEB->Ldr.InInitOrder
			next_module:
				;mov ebp, [esi + 0x08]		; ebp = InInitOrder[X].base_address - original
				mov eax, [esi + 0x08]		; ebx = InInitOrder[X].base_address - modified to put in ebx
				mov edi, [esi + 0x20]		; ebp = InInitOrder[X].module_name (unicode)
				mov esi, [esi]                  
				cmp [edi + 0x18], cx		; aniway fix for compatibility with win2k modulename[12] == 00 ?
				jne next_module       
				ret


			_find_function32:
				pushad			      
				mov   ebp, [esp + 0x24]       
				mov   eax, [ebp + 0x3c]       
				mov   edx, [ebp + eax + 0x78] ; Export table relative offset
				add   edx, ebp                
				mov   ecx, [edx + 0x18]       
				mov   ebx, [edx + 0x20]       
				add   ebx, ebp                
			find_function_loop:
				jecxz find_function_finished  ; Jump to the end if ecx is 0
				dec   ecx                     
				mov   esi, [ebx + ecx * 4]    
				add   esi, ebp                

				
			compute_hash:
				xor   edi, edi                
				xor   eax, eax                
				cld                           
			compute_hash_again:
				lodsb                         
				test  al, al                  
				jz    compute_hash_finished   ; ZF = 0 flag verify
				ror   edi, 0x4a                ; ror crypto key in this case (0x1d)
				add   edi, eax                
				jmp   compute_hash_again      
			compute_hash_finished:         


			find_function_compare:           
				cmp   edi, [esp + 0x28]      
				jnz   find_function_loop     
				mov   ebx, [edx + 0x24]      
				add   ebx, ebp               
				mov   cx, [ebx + 2 * ecx]    
				mov   ebx, [edx + 0x1c]      
				add   ebx, ebp               
				mov   eax, [ebx + 4 * ecx]   
				add   eax, ebp               
				mov   [esp + 0x1c], eax      
			find_function_finished:
				popad     
				ret


				
				
	;
	;	SYS.c
	;
			_getsystem_imagebase:
				mov edi, edi
				mov ebp, esp
				mov eax, [fs:0x30]
				mov eax, [eax+0x08]
				mov eax, eax
				ret

			

	;
	;	MISC.C
	;				

			_random_byte:
				mov edi, edi
				mov ebp, esp
				xor edx, edx
				mov edx, [ebp+4]
				rdtsc
				adc eax, edx
				mov esi, [ebp+8]
				adc eax, esi
				mov esi, [ebp+12]
				mul esi
				adc eax, edx
				;mov esi, 0xFF
				mul esi
				mov edx, eax
				xor eax, eax
				mov al, dl
				ret

		
			_nGetCPUID:
				mov edi, edi
				mov ebp, esp
				xor eax, eax
				mov eax, 1
				CPUID
				mov esi, eax
				xor eax, eax
				add eax, esi
				add eax, ebx
				add eax, ecx
				add eax, edx
				ret

			_GetCPUID:
				mov edi, edi
				mov ebp, esp
				mov esi, [ebp+4]
				mov eax, 1
				CPUID
				mov [esi+0], eax
				mov [esi+4], ebx
				mov [esi+8], ecx
				mov [esi+12], edx
				mov eax, esi
				ret
				
				
			_iswOw64:
				mov edi, edi
				mov ebp, esp
				xor eax, eax
				mov eax, [fs:0xC0]
				cmp al, 0
				je  _end_iswOw64
				mov eax, 1	
				_end_iswOw64:
					ret
				
				
				