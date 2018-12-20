; 8086 Assembly code 
; scramble encryption "Reverse the binary order of the index of each character and print the output on the new order .. "
; IF the reversed new index has now character, it automatically replaces it with a dot [.] ..
; Tested on emu8086 emulator

.MODEL SMALL

.DATA
    BITSCOUNT db 0
    CURRENT_CHAR_IDX db 0
    INPUT_LENGTH db 0
    BUFFER db 255,?, 255 dup('.'); ? uninitialized
		IPMSG DB 0AH , 0DH , "Enter the TEXT to be Encrypted/Decrypted: " , '$'  ;input msg
		OPMSG DB 0AH , 0DH ,0AH , 0DH , "OUTPUT: " , '$' ;output msg

DATA ENDS
                                
.CODE

    INIT:       MOV AX , DATA
                MOV DS , AX
    
                XOR CX,CX ;empty the REGs
                XOR AX,AX
                XOR BX,BX
                XOR DX,DX
    
    WELCOMEMSG: LEA DX , IPMSG
                CALL PRINTWORD
                    
    GETINPUT:   MOV dx, offset buffer
                MOV ah, 0ah ;input mode
                INT 21h
                CMP buffer[1],0 ; reask if no input
                JZ  GETINPUT
                MOV BL,buffer[1] ; store the length of the input
                MOV buffer[2+BX],46 ;put . at the end of the array for missing chars
                MOV offset INPUT_LENGTH,BL ; 1 
                DEC BL 
                
    OUTPUT:     LEA DX , OPMSG
                CALL PRINTWORD
                jmp calBitsNUM      
            
                
    calBitsNUM: ; Calculate number of bits. 
                INC CL         
                SHR Bl,1  ;shift right tell you reach zero (division by 2)
                JNZ calBitsNUM
                MOV [BITSCOUNT],CL ;store the number of bits in the memory.
                jmp GETIPLENGTH

;    FILL: ;fill the rest of the buffer with spaces if < MAX BITS NUM     
; IF WE HAVE 5 [ALNUM] digits, scrambling will be out of range
; so i'll complete them to 8 and set the remainders as dots [.]

    GETIPLENGTH: MOV AL,[INPUT_LENGTH]
                 MOV CL,[BITSCOUNT]

    CheckMAXNUM: ;check if maximum number of bits is the length of the INPUTLENGTH            
                TEST AL,1 ; check the 1st bit if zero
                JNZ CalMaxNUM ; increment by one if not zero                
                SHR AL,1;shift right to check the first bit  
                LOOP CheckMAXNUM                
                jmp swapIDXs
                
    CalMaxNUM:  ;calculate max number in given number of bits 
                INC INPUT_LENGTH
                JMP GETIPLENGTH


    swapIDXs: ; swap the index of the current item with the scrambled index 
                MOV CL,[BITSCOUNT]
                XOR BX,BX        ; Set BX to zero
                mov AL, [CURRENT_CHAR_IDX]  
 
    
    ReverseIdx: ;number in AL reversed in BL 
               RCR    AL,1
               RCL    BL,1
               LOOP   ReverseIdx ; Do # of times equals # of bits 
               MOV Dl,buffer[2 + BX]
               CALL PRINTCHAR
               INC [CURRENT_CHAR_IDX]
               MOV AL,[CURRENT_CHAR_IDX]
               CMP [INPUT_LENGTH],AL
               JNE swapIDXs ;if number of charcters is greater than the current char index ,, jump 
               HLT
CODE ENDS

PRINTCHAR PROC
                MOV AH , 2
                INT 21H
                RET
PRINTCHAR ENDP

PRINTWORD PROC
                MOV AH , 09H
                INT 21H 
                RET
PRINTWORD ENDP