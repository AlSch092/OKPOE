.data

nPacketLength dq 0
lpSendBuffer dq 0
lpSendClass dq 0

.code

EXTERN Sleep: PROC

EXTERN lpCreatePacketFunc : dq
EXTERN lpSendPacketFunction : dq
EXTERN lpSendPacketReturnAddress : dq

EXTERN lpEntitySpawnFunctionAddress : dq
EXTERN lpEntitySpawnReturnAddress : dq

EXTERN lpEntityLabelSpawnCallbackAddress : dq
EXTERN lpEntityLabelSpawnReturnAddress : dq

EXTERN lpReduceCPUReturnAddress: dq

EXTERN lpHandleKeypress : dq
EXTERN lpHotkeyHookReturn: dq

EXTERN lpClientMessageReturnAddr: dq
EXTERN lpClientMessageHookFunc : dq

EXTERN lpOnSkillGemLevelUpHookFunc : dq
EXTERN lpOnSkillGemLevelUpReturnAddr : dq

EXTERN lpMinimapIconsHookFunc : dq
EXTERN lpMinimapIconsReturnAddr : dq

EXTERN CPUReducerSleepTime : dq

GetSendClass PROC
	mov rax, lpSendClass
	ret
GetSendClass ENDP

SetCPUReducerTime PROC
	mov CPUReducerSleepTime, rcx
	ret
SetCPUReducerTime ENDP

OutPacketHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    sub rsp,1040h
    push rcx
    push rdx
    push rax
    mov rax, [rbx+1C8h]
    mov nPacketLength, rax
    mov rax, [rbx+1F0h]
    mov lpSendBuffer, rax
    mov rcx, lpSendBuffer
    mov rdx, nPacketLength
	mov lpSendClass, rbx
    call lpCreatePacketFunc
    pop rax
    pop rdx
    pop rcx
    add rsp,1040h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

    mov r8, [rcx+1C8h]
    jmp lpSendPacketReturnAddress

OutPacketHook ENDP

SendPacket PROC
; RCX = SendClass //Only real param in func, we use 3 to make replacing ptr easier
; RDX = Packet Buffer
; R8 = Length
	
	sub rsp, 5F0h ;allocate space

    push rax
	push r14 ;save old buffer
	push r10

    mov rax, rcx ;SendClass
	cmp rax,0
	je ending

    add rax, 1F0h
	
	mov r14, rax ;save old buffer
	mov r14, [r14]

	mov [rax], rdx ;swap our buffer ptr into their send class .. param 2
	sub rax, 28h 

	mov r10, [rax] ;save length into r10

    mov [rax], r8 ; length, parameter 3 into their struct

	call lpSendPacketFunction

	add rax, 1F0h ;restore original data to structure
	mov [rax], r14
	sub rax, 28h
	mov [rax], r10
  
ending:
	pop r10
	pop r14
	pop rax
	add rsp, 5F0h
    ret

SendPacket ENDP

EntitySpawnHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
	         
    sub rsp,28h
	mov rcx, rax
	call lpEntitySpawnFunctionAddress
	add rsp,28h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	add rsp, 50h
	pop r14

	jmp lpEntitySpawnReturnAddress

EntitySpawnHook ENDP

EntityLabelSpawnHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
	         
    sub rsp,28h
	call lpEntityLabelSpawnCallbackAddress
	add rsp,28h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	nop
	mov rax,[rsp+48h]

	jmp lpEntityLabelSpawnReturnAddress

EntityLabelSpawnHook ENDP

CPUReduceHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	push rcx

	sub rsp,280h
	mov rcx, CPUReducerSleepTime ;change to variable
	call Sleep
	add rsp,280h

	pop rcx

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	add r8,04
	mov [rcx+20h],eax
	;mov rdx,r10

	jmp lpReduceCPUReturnAddress
CPUReduceHook ENDP

HotkeyHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	sub rsp,280h
	call lpHandleKeypress
	add rsp,280h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	lea rax,[rsp+98h]
	jmp lpHotkeyHookReturn
HotkeyHook ENDP

ClientMessageHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	sub rsp,280h
	call lpClientMessageHookFunc
	add rsp,280h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	mov [rsp+08],rbx
	jmp lpClientMessageReturnAddr
ClientMessageHook ENDP

;r8 = item gear slot
;r9 = links slot
OnSkillGemLevelUpHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

	sub rsp,280h
	push rcx
	push rdx
	push r8
	mov rcx, r8
	mov rdx, r9
	mov r8, rdi
	call lpOnSkillGemLevelUpHookFunc
	pop r8
	pop rdx
	pop rcx
	add rsp,280h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	push rbx
	sub rsp, 50h

	jmp lpOnSkillGemLevelUpReturnAddr

OnSkillGemLevelUpHook ENDP

MinimapIconsHook PROC

    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15


	sub rsp,280h
	push rcx
	call lpMinimapIconsHookFunc
	pop rcx
	add rsp,280h

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

	mov [rsp+10h],rbx
	jmp lpMinimapIconsReturnAddr

MinimapIconsHook ENDP

END