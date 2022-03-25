.386
DATA SEGMENT USE16
BUF DB 2
DATA ENDS
STACK SEGMENT USE16 STACK
DB 200 DUP(0)
STACK ENDS
CODE SEGMENT USE16
ASSUME DS:DATA,SS:STACK,CS:CODE
START:
     MOV AX,DATA
	 MOV DS,AX
LOPA:
     MOV AH,1
     INT 21H
	 SUB AL,30H  ;transfer to ʮ����
	 OUT 70H,AL  ;take out message
	 IN  AL,71H
	 MOV AH,AL
	 AND AL,0FH
	 SHR AH,4
	 ADD AX,3030H ;transfer to ASCII
	 XCHG AH,AL
	 MOV BX,AX
	 LEA SI,BUF
	 MOV WORD PTR [SI+1],BX
	 MOV DL,0AH
	 MOV AH,2
	 INT 21H
	 MOV DL,0DH
	 MOV AH,2
	 INT 21H
	 MOV DL,BL
	 MOV AH,2
	 INT 21H
	 MOV DL,BH
	 MOV AH,2
	 INT 21H
	  MOV DL,0AH
	 MOV AH,2
	 INT 21H
	 MOV DL,0DH
	 MOV AH,2
	 INT 21H
	 JMP LOPA
	 MOV AH,4CH
	 INT 21H
CODE ENDS
END START