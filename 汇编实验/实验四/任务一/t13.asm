.386
STACK SEGMENT USE16 STACK
DB 200 DUP(0)
STACK ENDS
CODE SEGMENT  USE16
     ASSUME CS:CODE,SS:STACK
START:XOR AX,AX
      MOV DS,AX
	  XOR BX,BX
	  XOR CX,CX
	  MOV BX,DS:[4C]
	  MOV CX,DS:[4E]	
	  MOV AH,4CH
	  INT 21H
CODE ENDS
END START