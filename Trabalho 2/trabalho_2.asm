global _start
section .data
;INICIALIZA
INICIO db "Digite seu nome: ",0dh,0ah
SIZE_INICIO EQU $-INICIO

;BOAS VINDAS até o nome
BOAS_VINDAS_NOME db "Olá, "
SIZE_BOAS_VINDAS_NOME EQU $-BOAS_VINDAS_NOME

;resto de boas vindas
BOAS_VINDAS_RESTO db "Bem vindo ao programa de CALC IA-32",0dh,0ah
SIZE_BOAS_VINDAS_RESTO EQU $-BOAS_VINDAS_RESTO

;MENU
MENU db "Escolha uma opção:",0dh,0ah
SIZE_MENU EQU $-MENU

SOMA db "- 1: SOMA",0dh,0ah
SIZE_SOMA EQU $-SOMA

SUBT db "- 2: SUBTRAÇÃO",0dh,0ah
SIZE_SUBT EQU $-SUBT

MULT db "- 3: MULTIPLICAÇÃO",0dh,0ah
SIZE_MULT EQU $-MULT

DIVI db "- 4: DIVISÃO",0dh,0ah
SIZE_DIVI EQU $-DIVI

MOD db "- 5: MOD",0dh,0ah
SIZE_MOD EQU $-MOD

SAIR db "- 6: SAIR",0dh,0ah
SIZE_SAIR EQU $-SAIR

FUNC_ESCOLHIDO db "A FUNÇÃO ESCOLHIDA FOI: "
SIZE_FUNC_ESCOLHIDO EQU $-FUNC_ESCOLHIDO

msg_num1 db "Insira o primeiro numero: "
SIZE_msg1 EQU $-msg_num1
msg_num2 db "Insira o segundo numero: "
SIZE_msg2 EQU $-msg_num2
msg_resultado db "O resultado e: "
SIZE_resultado EQU $-msg_resultado
nwln db 0Dh,0Ah
SIZE_nwln EQU $-nwln

section .bss
num1 resb 1
num2 resb 1
resultado resb 16
NOME resb 16
ESCOLHA resb 1

section .text
_start:

; mov eax,
; mov ebx,
; mov ecx,
; mov edx,
; int 80h

;PERGUNTAR E SALVAR O NOME
    mov eax,4
    mov ebx,1
    mov ecx,INICIO
    mov edx,SIZE_INICIO
    int 80h

    mov eax,3
    mov ebx,0
    mov ecx,NOME
    mov edx,16
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

;MENSAGEM DE BOAS VINDAS

    mov eax,4
    mov ebx,1
    mov ecx,BOAS_VINDAS_NOME
    mov edx,SIZE_BOAS_VINDAS_NOME
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,NOME
    mov edx,16
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,BOAS_VINDAS_RESTO
    mov edx,SIZE_BOAS_VINDAS_RESTO
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

;MENU
    mov eax,4
    mov ebx,1
    mov ecx,MENU
    mov edx,SIZE_MENU
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,SOMA
    mov edx,SIZE_SOMA
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,SUBT
    mov edx,SIZE_SUBT
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MULT
    mov edx,SIZE_MULT
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,DIVI
    mov edx,SIZE_DIVI
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MOD
    mov edx,SIZE_MOD
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,SAIR
    mov edx,SIZE_SAIR
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

;LER ESCOLHA DO USUARIO
    mov eax,3
    mov ebx,0
    mov ecx,ESCOLHA
    mov edx,1
    int 80h

    sub BYTE [ESCOLHA],0x30

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

;COMPARAR
;Tentativa de zerar buffer
;    mov eax,0
;    mov ebx,0
;    mov ecx,0
;    mov edx,0

    mov eax,4
    mov ebx,1
    mov ecx,msg_num1
    mov edx,SIZE_msg1
    int 80h

    mov eax,3
    mov ebx,0
    mov ecx,num1
    mov edx,1
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,msg_num2
    mov edx,SIZE_msg2
    int 80h

    mov eax,3
    mov ebx,0
    mov ecx,num2
    mov edx,1
    int 80h

    mov BL,[num2]
    sub BL,0x30

    push WORD [num1]
    push WORD [num2]

    call FUNC_SOMA

    POP WORD [resultado]

    mov eax,4
    mov ebx,1
    mov ecx,msg_resultado
    mov edx,SIZE_resultado
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,resultado
    mov edx,16

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

    mov eax,1
    mov ebx,0
    int 80h

FUNC_SOMA:
    enter 0,0
    ;push ebp
    ;mov ebp,esp
    push AX
    mov AX,[EBP+10]
    add AX,[EBP+8]
    mov [EBP+12],AX
    pop AX
    leave
    ;mov ebp,esp
    ;pop ebp
    ret 4

FUNC_SUBT:
    ret

FUNC_MULTI:
    ret

FUNC_DIVI:
    ret

FUNC_MOD:
    ret

FUNC_SAIR:
    mov eax,1
    mov ebx,0
    int 80h
