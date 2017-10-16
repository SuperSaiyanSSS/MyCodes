DATA SEGMENT
    ARRAY DB 9, 8, 19, 100, 96 DUP(0)
    I DW 0
    J DW 0
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
    MAIN PROC FAR
        PUSH DS
        PUSH AX
        SUB AX, AX                       ;because we can just use MOV XL, [BX+SI] 
                                         ; SO I swap the AX and BX
        MOV AX, DATA
        MOV DS, AX
        SUB AX, AX
        
        PUSH BX
        PUSH CX
        PUSH DX
        MOV AX, 0
        MOV CX, 0
        MOV DX, 0
        
        MOV AH, 0
        MOV AL, 0
        
        START_BIG_LOOP:
           
           CMP [I], 10
           JGE START_BIG_END
           
           SMALL_LOOP:
               SUB BX, BX
               
               CMP [J], 10
               JGE SMALL_NED
               
               MOV BX, OFFSET ARRAY
               
               MOV SI, [I]
               
               MOV DH, [BX+SI]
               
               MOV SI, [J]
               MOV DL, [BX+SI]
               
               CMP DH, DL
               
               JGE NO_NEED_SWAP
               
               MOV CH, DH
               MOV DH, DL
               MOV DL, CH
               
               NO_NEED_SWAP:
                               
                   MOV SI, [I]
                   MOV [ARRAY+SI], DH 
                   
                   MOV SI, [J]
                   MOV [ARRAY+SI], DL
                 
                   MOV CX, 0
                   MOV DX, 0
                   ADD [J], 1
                   
                   JMP SMALL_LOOP
                   
                   SMALL_NED:
                       
                       MOV [J], 0
                       ADD [I], 1
                       JMP START_BIG_LOOP
         
       START_BIG_END:
          MOV CX, 0
          MOV CL, [ARRAY]   
          
       mov ax,4c00h
int 21h

          
       RET 
       
      MAIN ENDP
CODE ENDS
END MAIN 
                  