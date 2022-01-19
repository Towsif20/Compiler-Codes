.model small
.stack 100h
.data
a3 dw ?
b3 dw ?
c3 dw ?
t0 dw ?
t1 dw ?
t2 dw ?
t3 dw ?
t4 dw ?
t5 dw ?
t6 dw ?
t7 dw ?
t8 dw ?
g_return dw ?
a2 dw ?
b2 dw ?
main_return dw ?
x1 dw ?
y1 dw ?
t9 dw ?
t10 dw ?
t11 dw ?
t12 dw ?
t13 dw ?
.code
	push ax
	push bx
	push cx
	push dx
	push a3
	push b3
	push c3
	mov t0, 1
	mov ax, a3
	cmp ax, t0
	je L0
	mov t1, 0
	jmp L1
L0:
	mov t1, 1
L1:
	mov ax, t1
	cmp ax, 0
	je L2
	mov t2, 1
	mov ax, t2
	mov _return, ax
	jmp LReturn
L2:
	mov t3, 1
	mov ax, a3
	sub ax, t3
	mov t4, ax
	mov t5, 1
	mov t6, 2
	mov ax, t4
	mov a3, ax
	mov ax, t5
	mov b3, ax
	mov ax, t6
	mov c3, ax
	call f
	mov ax, f_return
t7, ax
	mov ax, a3
	mov bx, t7
	mov dx, 0
mul bx
	mov t8, ax
	mov ax, t8
	mov _return, ax
	jmp LReturn
LReturn:
	pop c3
	pop b3
	pop a3
	pop dx
	pop cx
	pop bx
	pop ax
	ret
f endp
	push ax
	push bx
	push cx
	push dx
	push a2
	push b2
LReturng:
	pop b2
	pop a2
	pop dx
	pop cx
	pop bx
	pop ax
	retg endp
main proc
 mov ax, @data
	mov ds, ax
	mov t9, 6
	mov ax, t9
	mov y1, ax
	mov t10, 2
	mov t11, 3
	mov ax, y1
	mov a3, ax
	mov ax, t10
	mov b3, ax
	mov ax, t11
	mov c3, ax
	call f
	mov ax, f_return
t12, ax
	mov ax, t12
	mov x1, ax
	mov ax, x1
	call outdec
	mov t13, 0
	mov ax, t13
	mov main_return, ax
	jmp LReturnmain
 LReturnmain:
	mov ah, 4ch
	int 21h
OUTDEC PROC  
		    PUSH AX 
		    PUSH BX 
		    PUSH CX 
		    PUSH DX  
		    CMP AX,0 
		    JGE BEGIN 
		    PUSH AX 
		    MOV DL,'-' 
		    MOV AH,2 
		    INT 21H 
		    POP AX 
		    NEG AX 
		    
		    BEGIN: 
		    XOR CX,CX 
		    MOV BX,10 
		    
		    REPEAT: 
		    XOR DX,DX 
		    DIV BX 
		    PUSH DX 
		    INC CX 
		    OR AX,AX 
		    JNE REPEAT 
		    MOV AH,2 
		    
		    PRINT_LOOP: 
		    POP DX 
		    ADD DL,30H 
		    INT 21H 
		    LOOP PRINT_LOOP 
		    
		    MOV AH,2
		    MOV DL,10
		    INT 21H
		    
		    MOV DL,13
		    INT 21H
			
		    POP DX 
		    POP CX 
		    POP BX 
		    POP AX 
		    ret 
		OUTDEC ENDP 
		END MAIN
