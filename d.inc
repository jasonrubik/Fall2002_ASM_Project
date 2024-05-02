.data

	intro_msg       db 0ah,0ah,0dh,'  Audio Recorder and Playback program.',0ah,0dh
			db '  ------------------------------------'
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,'Press any key to begin....'
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Power up the circuit before pressing a key.',24h

	main_menu1      db 0dh,0ah,0ah,0ah,9,'Press R to Record and P to Playback an audio file.'
			db 0dh,0ah,0ah,0ah,0ah,9,'   Q to Quit',0dh,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah
			db '  You must record at least one file first before an attempt at playback.',0ah,0dh,24h
	
	main_menu2      db 0ah,0ah,0ah,0dh,9,'Select a file:  1, 2, or 3.',0dh,0ah,0ah
			db 9,9,9,'Or press 6 to utilize all available memory.'
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,'Each file will be 10 seconds long.'
			db 0dh,0ah,9,'Maximum memory capacity allows for 30 seconds of audio storage.',0dh,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Press ESC to return to previous menu.',24h
	
	main_menu3      db 0ah,0ah,0ah,0dh,9,'Select a playback rate with these keys:'
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,'    S       D       F       G       H'
			db 0dh,0ah,0ah,9,9,'   1/4x    1/2x     1x      2x      4x'
			db 0dh,0ah,0ah,9,9,'<    Slower       Normal      Faster    >',0dh,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Press ESC to return to previous menu.',24h
	
	main_menu4      db 0ah,0ah,0ah,0dh,9,'Reverse or Forward'
			db 0dh,0ah,9,'   <          >',0dh,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah
			db 0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Press ESC to return to previous menu.',24h

	rec_start_msg   db 0ah,0ah,0ah,0ah,0dh,'   Press any key to start recording.',0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Press ESC to return to previous menu.',24h	

	rec_stop_msg    db 0ah,0ah,0dh,'   Recording stopped.',0ah,0ah,0ah,0dh
			db '       Press any key to return to the menu.',0dh,0ah,24h
			

	play_start_msg  db 0ah,0ah,0ah,0ah,0dh,'   Press any key to start playing.',0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah
			db 0dh,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,0ah,9,9,9,9,'Press ESC to return to previous menu.',24h
	
	play_stop_msg   db 0ah,0ah,0dh,'   Playback stopped.',0ah,0ah,0ah,0dh
			db '       Press any key to return to the menu.',0dh,0ah,24h

	recording       db 0ah,0ah,0ah,0ah,0dh,9,9,9,'recording ',24h

	playing         db 0ah,0ah,0ah,0ah,0dh,9,9,9,'playing ',24h

	error_msg       db 0ah,0dh,'        ERROR.  Please try again.',24h
