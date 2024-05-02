;include for Audio program


setup_8255 MACRO
	mov     dx,203h
	mov     al,90h
	out     dx,al
endm

clear_screen MACRO
	push    ax
	mov     ah,0
	mov     al,3
	int     10h

	mov	ah,1
	mov	ch,20h
	mov	cl,0
	int 	10h	
	pop     ax
endm


pos_cursor MACRO
	mov	bh,0
	mov	dh,8
	mov	dl,0
	mov	ah,2
	int	10h
endm	


key_press MACRO
	mov     ah,08
	int     21h
endm


print_string MACRO
	push    ax
	mov     ax,0
	mov     ah,09
	int     21h
	pop     ax
endm


draw_dot MACRO
	push	ax
	push	dx
	pushf
	mov	ah,02
	mov	dl,'.'
	int	21h
	popf
	pop	dx
	pop	ax
endm


rec_delay MACRO
	push    cx

	mov     cx,fixed_counter
delay1:
	nop
	dec     cx
	cmp     cx,0
	jnz     delay1
	
	pop     cx
endm


play_fwd_delay MACRO
	push    cx

	mov     cx,var_counter
delay2:
	nop
	nop
	nop
	dec     cx
	cmp     cx,0
	jnz     delay2

	pop     cx
endm


play_rev_delay MACRO
	push    cx
	
	mov     cx,var_counter
delay3:
	nop
	nop
	nop
	dec     cx
	cmp     cx,0
	jnz     delay3
	pop     cx
endm



record1 MACRO
	push    es
	mov     dx,200h
	mov     ax,file_start
next_rec_seg:
	mov     es,ax
	mov     di,0
rec_byte:        
	in      al,dx
	mov     es:[di],al
	rec_delay
	inc     di
	cmp     di,0ffffh
	jnz     rec_byte
	mov     ax,es
	add     ax,1000h
	mov	bx,file_end
	cmp     ax,bx
	jnz     next_rec_seg
	pop     es
endm


playback_forward MACRO
	push    es
	mov     dx,201h
	mov     ax,file_start
next_play_seg:
	mov     es,ax
	mov     di,0
play_byte:        
	mov     al,es:[di]
	out     dx,al
	play_fwd_delay
	inc     di
	cmp     di,0ffffh
	jnz     play_byte
	mov     ax,es
	add     ax,1000h        
	mov	bx,file_end
	cmp     ax,bx
	jnz     next_play_seg
	pop     es        
endm


playback_reverse MACRO
	push    es
	mov     dx,201h
	mov     ax,file_start
next_play_seg2:
	mov     es,ax
	mov     di,0ffffh
play_byte2:        
	mov     al,es:[di]
	out     dx,al
	play_rev_delay
	dec     di
	cmp     di,0
	ja      play_byte2
	mov     ax,es
	sub     ax,1000h        
	mov	bx,file_end
	cmp     ax,bx
	jnz     next_play_seg2
	pop     es
endm



read_RP_keys MACRO
	push    ax
	mov     ah,08
RP1:    
	int     21h
	cmp     al,27
	je      esc1
	cmp     al,'r'
	je      RP2
	cmp     al,'R'
	je      RP2
	cmp     al,'p'
	je      RP3
	cmp     al,'P'
	je      RP3
	cmp     al,'q'
	je      RP4
	cmp     al,'Q'
	je      RP4
	jmp     RP1     

esc1:   mov     mode,'e'
	jmp     RP5
RP2:    
	mov     mode,'r'
	jmp     RP5
RP3:    
	mov     mode,'p'
	jmp     RP5
RP4:
	mov     mode,'q'
RP5:    
	pop     ax
	
endm    


read_file_keys MACRO
	push    ax
	mov     ah,08
file_num1:
	int     21h
	cmp     al,27
	je      esc2
	cmp	al,'6'
	je	file12
	cmp     al,'1'
	jb      file_num1
	cmp     al,'3'
	ja      file_num1
	sub	al,30h
	inc	al
	mov	bx,0
	mov	bl,al
	mov	ax,1000h
	mul	bx
	mov     file_number,ax
	jmp     file1
esc2:        
	mov     byte ptr file_number,'e'
	jmp	file1
file12:
	mov	byte ptr file_number,'6'
file1:        
	pop     ax
endm

read_file_keys2 MACRO
	push    ax
	mov     ah,08
file_num2:
	int     21h
	cmp     al,27
	je      esc3
	cmp	al,'6'
	je	file22
	cmp     al,'1'
	jb      file_num2
	cmp     al,'3'
	ja      file_num2
	sub	al,30h
	inc	al
	mov	bx,0
	mov	bl,al
	mov	ax,1000h
	mul	bx
	mov     file_number,ax
	jmp     file2
esc3:        
	mov     byte ptr file_number,'e'
	jmp	file2
file22:
	mov	byte ptr file_number,'6'
file2:        
	pop     ax
endm


read_speed_keys MACRO
	push    ax
	mov     ah,08
sp0:
	int     21h
	cmp     al,27
	je      esc4
	cmp     al,'s'
	je      sp1
	cmp     al,'S'
	je      sp1
	cmp     al,'d'
	je      sp2
	cmp     al,'D'
	je      sp2
	cmp     al,'f'
	je      sp3
	cmp     al,'F'
	je      sp3
	cmp     al,'g'
	je      sp4
	cmp     al,'G'
	je      sp4
	cmp     al,'h'
	je      sp5
	cmp     al,'H'
	je      sp5
	jmp     sp0
esc4:
	mov     byte ptr speed,'e'
	jmp     sp6
sp1:    
	mov     speed,102h
	jmp     sp6
sp2:
	mov     speed,101h
	jmp     sp6
sp3:    
	mov     speed,000h
	jmp     sp6
sp4:
	mov     speed,001h
	jmp     sp6
sp5:    
	mov     speed,002h
sp6:
	pop     ax
endm


read_direction_keys MACRO
	push    ax
	mov     ah,08
dir0:   
	int     21h
	cmp     al,27        
	je      esc5
	cmp     al,'<'
	je      dir1
	cmp     al,','
	je      dir1
	cmp     al,'>'
	je      dir2
	cmp     al,'.'
	je      dir2
	jmp     dir0
esc5:
	mov     direction,'e'
	jmp     dir3
dir1:
	mov     direction,1
	jmp     dir3
dir2:
	mov     direction,0
dir3:
	pop     ax
endm
	
