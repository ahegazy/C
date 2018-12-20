; 8086 Assembly code
; searches for an id in the stored IDs and then verify its password,
; returns 1 if the ID & password are right , 0 else.
; Tested on emu8086 emulator

.MODEL SMALL

.DATA    
    IDs DB "010101" , "020202" , "030303" , "040404" , "050505","060606" , "070707" , "080808" , "090909" , "101010", "111111" , "121212" , "131313" , "141414" , "151515","161616" , "171717" , "181818" , "191919" , "202020"    
	PASS  DB "0101" , "0202" , "0303" , "0404" , "0505" , "0606" , "0707" , "0808" , "0909" , "1010","1111" , "1212" , "1313" , "1414" , "1515" , "1616" , "1717" , "1818" , "1919" , "2020"

	IPID DB 7,?, 7 dup('.')  ; 6 digits 
	IPASS DB 5,?, 5 dup('.')

DATA ENDS

.CODE
    INIT:       MOV AX , DATA
                MOV DS , AX
    
    IP:         LEA DX , IPID
                CALL SCANWORD
                CALL PRINTLINE
                LEA DX , IPASS
                CALL SCANWORD
                CALL PRINTLINE

    CHKIP:      ;check i/p id or password cahacters count
                CMP IPID[1],6 
                JNZ DENIED
                CMP IPASS[1],4
                JNZ DENIED
                XOR BX,BX
                XOR AX,AX
                
    INITUSR:    CMP BX,120 ; checked all users 20 * 6 digits a user
                JZ  DENIED
                INC AH  ;store user index in AH
                LEA SI,IDs+BX ; BX should be 4 byte to be added to the variable
                LEA DI,IPID+2
                ADD BX,6
                MOV CX,6 
                
    CHKUSR:     MOV AL,[SI]
                CMP AL,[DI]
                JNZ INITUSR ; digit # is not equal check other one
                INC SI
                INC DI
                LOOP CHKUSR
                
    INITPASS:   MOV BL,4
                MOV AL,AH
                DEC AL
                CBW
                MUL BL ; password index is stored at AX
                MOV BX,AX
                MOV CX,4
                LEA DI,IPASS+2 ; address of 1st i/p char
                LEA SI,PASS+BX ; address of IDx user
                
                
    CHECKPASS:  MOV AL,[SI]
                CMP AL,[DI]
                JNZ DENIED
                INC SI
                INC DI
                LOOP CHECKPASS
                JMP ALLOWED
          
    ALLOWED:    MOV DL , 049
                CALL PRINTCHAR
                HLT
            
    DENIED:     MOV DL , 048
                CALL PRINTCHAR
                HLT
  
CODE ENDS                                                                                                                                                                    

PRINTLINE PROC
                MOV DL,0AH
                CALL PRINTCHAR
                MOV DL, 0DH                
                CALL PRINTCHAR
                RET
PRINTLINE ENDP

PRINTCHAR PROC
                MOV AH , 2
                INT 21H
                RET
PRINTCHAR ENDP

SCANWORD PROC
                MOV AH, 0ah ;input mode
                INT 21h
                RET
SCANWORD ENDP