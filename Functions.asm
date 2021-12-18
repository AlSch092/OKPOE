SendPacket PROC
; RCX = SendClass //Only real param in func, we use 3 to make replacing ptr easier
; RDX = Packet Buffer
; R8 = Length
	
	sub rsp, 13F0h ;allocate space

  push rax

  mov rax, rcx ;SendClass
	cmp rax,0
	je ending

  add rax, 1a8h
	mov [rax], rdx ;swap our buffer ptr into their send class .. param 2
	sub rax, 28h 
  mov [rax], r8 ; length, parameter 3

	call dqSendPacketFunction
  
ending:
	pop rax
	add rsp, 13F0h
  ret

SendPacket ENDP

