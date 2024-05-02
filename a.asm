.model small
.stack 200h
	
include a.inc

.const
	
	file_length     dw      1000h
	

include d.inc


	fixed_counter   dw 3000h
	var_counter     dw  ?
	
	mode            db ?
	speed           dw ?
	file_number     dw ?
	direction       db ?

	file_start      dw ?
	file_end        dw ?
.code

start:
	
	mov ax,@data
	mov ds,ax
main proc
	
	clear_screen    
	lea     dx,intro_msg        
	print_string
	key_press
	setup_8255
mode_select:
	clear_screen    
	lea     dx,main_menu1
	print_string
	read_RP_keys
	
	cmp     mode,'e'
	je      start

	cmp     mode,'r'
	je      record_audio
	cmp     mode,'p'
	je      playback_audio
		
	clear_screen
	mov     ax,4c00h
	int     21h

	
record_audio:
	clear_screen    
	lea     dx,main_menu2
	print_string
	read_file_keys
	
	cmp   	byte ptr file_number,'e'
	je      mode_select
	
	clear_screen    
	lea     dx,rec_start_msg
	print_string
	key_press
	cmp     al,27
	je      record_audio
	
	pos_cursor	
	lea     dx,recording
	print_string
	jmp setup_rec_file

setup_rec_file:
	cmp	file_number,'6'
	jz 	big_file1

	mov	bx,file_length
	mov	ax,file_number
	add	bx,ax
	mov	file_start,ax
	mov	file_end,bx
	jmp	input_audio

big_file1:
	mov	file_start,2000h
	mov	file_end,5000h	

input_audio:	

	record1 

	clear_screen
	lea     dx,rec_stop_msg
	print_string
	key_press
	jmp mode_select



playback_audio:         
	clear_screen    
	lea     dx,main_menu2
	print_string
	read_file_keys2

	cmp     byte ptr file_number,'e'
	je      mode_select

speed_select:        
	clear_screen
	lea     dx,main_menu3   
	print_string
	read_speed_keys

	cmp     byte ptr speed,'e'
	je      playback_audio

	mov     ax,speed
	cmp     al,0
	je      same_speed
	cmp     ah,1
	je      slower
	mov     bx,fixed_counter
	and     ax,0fh
speed_up:
	shr     bx,1
	dec     al
	cmp     al,0
	jnz     speed_up                
	mov     var_counter,bx
	jmp     dir_select
slower:
	mov     bl,al
	mov     ax,fixed_counter
	and     bx,0fh
slow_down:
	shl     ax,1
	dec     bl
	cmp     bl,0
	jnz     slow_down
	mov     var_counter,ax
	jmp     dir_select
same_speed:
	mov     ax,fixed_counter
	mov     var_counter,ax

dir_select:
	clear_screen
	lea     dx,main_menu4
	print_string
	read_direction_keys
	
	cmp direction,'e'        
	je speed_select     

	clear_screen    
	lea     dx,play_start_msg
	print_string
	key_press
	cmp     al,27        
	je      dir_select

	pos_cursor
	lea     dx,playing
	print_string

	cmp     direction,0
	je      play_forward
	cmp     direction,1
	je      play_reverse
	
	lea     dx,error_msg
	print_string
	key_press
	jmp     playback_audio                          

play_forward:
	cmp	file_number,'6'
	jz	big_file2

	mov	bx,file_length
	mov	ax,file_number
	add	bx,ax
	mov	file_start,ax
	mov	file_end,bx
	jmp	output_audio_fwd		

big_file2:
	mov	file_start,2000h
	mov	file_end,5000h

output_audio_fwd:
	playback_forward        
	jmp     stop_playing


play_reverse:
	cmp	file_number,'6'
	jz	big_file3

	mov	bx,file_length
	mov	ax,file_number
	add	bx,ax
	sub	ax,1000h
	sub	bx,1000h	
	mov	file_start,bx
	mov	file_end,ax
	jmp	output_audio_rev		

big_file3:
	mov	file_start,4000h
	mov	file_end,1000h

output_audio_rev:
	playback_reverse                        

stop_playing:
	clear_screen
	lea     dx,play_stop_msg
	print_string
	key_press
	jmp mode_select

	
	clear_screen
	mov     ax,4c00h
	int     21h

main endp

end start

	
