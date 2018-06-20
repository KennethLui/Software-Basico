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

FUNC_ESCOLHIDO db "A OPÇÃO ESCOLHIDA FOI: "
SIZE_FUNC_ESCOLHIDO EQU $-FUNC_ESCOLHIDO

;TESTES DE ENTRADA DE FUNÇÃO

MSG_TESTE db 0dh,0ah,"MENSAGEM DE TESTE",0dh,0ah
SIZE_MSG_TESTE EQU $-MSG_TESTE

MSG_SOMA db "SOMA",0dh,0ah
SIZE_MSG_SOMA EQU $-MSG_SOMA

MSG_SUBT db  "SUBTRAÇÃO",0dh,0ah
SIZE_MSG_SUBT EQU $-MSG_SUBT

MSG_MULT db "MULTIPLICAÇÃO",0dh,0ah
SIZE_MSG_MULT EQU $-MSG_MULT

MSG_DIVI db "DIVISÃO",0dh,0ah
SIZE_MSG_DIVI EQU $-MSG_DIVI

MSG_MOD db "MOD",0dh,0ah
SIZE_MSG_MOD EQU $-MSG_MOD

MSG_SAIR db "SAIR DO PROGRAMA",0dh,0ah
SIZE_MSG_SAIR EQU $-MSG_SAIR

;MENSAGENS PARA FUNÇÕES
MAIS db " + "
SIZE_MAIS EQU $-MAIS

MENOS db " - "
SIZE_MENOS EQU $-MENOS

MULTIPLICA db " * "
SIZE_MULTIPLICA EQU $-MULTIPLICA

DIVIDE db " / "
SIZE_DIVIDE EQU $-DIVIDE

MODULO db " % "
SIZE_MODULO EQU $-MODULO

SAI db "FINALIZANDO PROGRAMA",0dh,0ah
SIZE_SAI EQU $-SAI

IGUAL db " = "
SIZE_IGUAL EQU $-IGUAL
;FIM DAS MENSAGENS DE FUNÇÕES

msg_num1 db "Insira o primeiro numero: "
SIZE_msg1 EQU $-msg_num1
msg_num2 db "Insira o segundo numero: "
SIZE_msg2 EQU $-msg_num2
msg_resultado db "O resultado e: "
SIZE_resultado EQU $-msg_resultado
nwln db 0Dh,0Ah
SIZE_nwln EQU $-nwln

section .bss
num1 resb 10
num2 resb 10
resultado resb 100
NOME resb 100
ESCOLHA resb 2

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
    mov edx,100
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
    mov edx,100
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
    mov edx,2
    int 80h

    ;sub BYTE [ESCOLHA],0x30

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

;MOSTRAR A OPÇÃO

    mov eax,4
    mov ebx,1
    mov ecx,FUNC_ESCOLHIDO
    mov edx,SIZE_FUNC_ESCOLHIDO
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,ESCOLHA
    mov edx,2
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,msg_num1
    mov edx,SIZE_msg1
    int 80h

    mov eax,3
    mov ebx,0
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,msg_num2
    mov edx,SIZE_msg2
    int 80h

    mov eax,3
    mov ebx,0
    mov ecx,num2
    mov edx,10
    int 80h

    ;COMPARAR
    sub BYTE [ESCOLHA],0x30

    cmp BYTE [ESCOLHA],1
    jne NOT_SOMA
    call FUNC_SOMA

NOT_SOMA:
    cmp BYTE [ESCOLHA],2
    jne NOT_SUBT
    call FUNC_SUBT

NOT_SUBT:
    cmp BYTE [ESCOLHA],3
    jne NOT_MULTI
    call FUNC_MULTI

NOT_MULTI:
    cmp BYTE [ESCOLHA],4
    jne NOT_DIVI
    call FUNC_DIVI

NOT_DIVI:
    cmp BYTE [ESCOLHA],5
    jne NOT_MOD
    call FUNC_MOD

NOT_MOD:
    cmp BYTE [ESCOLHA],6
    jne NOT_SAIR
    call FUNC_SAIR
NOT_SAIR:
    ;FIM DA COMPARAÇÃO

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
    mov edx,100

    mov eax,4
    mov ebx,1
    mov ecx,nwln
    mov edx,SIZE_nwln
    int 80h

    mov eax,1
    mov ebx,0
    int 80h

FUNC_SOMA:
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_SOMA
    mov edx,SIZE_MSG_SOMA
    int 80h

    ;MOSTRA OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MAIS
    mov edx,SIZE_MAIS
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num2
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,IGUAL
    mov edx,SIZE_IGUAL
    int 80h
    ;TERMINOU DE MOSTRAR OPERAÇÃO
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
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_SUBT
    mov edx,SIZE_MSG_SUBT
    int 80h

    ;MOSTRA OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MENOS
    mov edx,SIZE_MENOS
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num2
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,IGUAL
    mov edx,SIZE_IGUAL
    int 80h
    ;TERMINOU DE MOSTRAR OPERAÇÃO

    ret

FUNC_MULTI:
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_MULT
    mov edx,SIZE_MSG_MULT
    int 80h

    ;MOSTRA OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MULTIPLICA
    mov edx,SIZE_MULTIPLICA
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num2
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,IGUAL
    mov edx,SIZE_IGUAL
    int 80h
    ;TERMINOU DE MOSTRAR OPERAÇÃO

    ret

FUNC_DIVI:
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_DIVI
    mov edx,SIZE_MSG_DIVI
    int 80h

    ;MOSTRA A OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,DIVIDE
    mov edx,SIZE_DIVIDE
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num2
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,IGUAL
    mov edx,SIZE_IGUAL
    int 80h
    ;TERMINOU DE MOSTRAR OPERAÇÃO

    ret

FUNC_MOD:
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_MOD
    mov edx,SIZE_MSG_MOD
    int 80h

    ;MOSTRA OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,num1
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,MODULO
    mov edx,SIZE_MODULO
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,num2
    mov edx,10
    int 80h

    mov eax,4
    mov ebx,1
    mov ecx,IGUAL
    mov edx,SIZE_IGUAL
    int 80h
    ;TERMINOU DE MOSTRAR OPERAÇÃO

    ret

FUNC_SAIR:
    ;MOSTRA MENSAGEM DA FUNÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,MSG_SAIR
    mov edx,SIZE_MSG_SAIR
    int 80h

    ;MOSTRA OPERAÇÃO
    mov eax,4
    mov ebx,1
    mov ecx,SAI
    mov edx,SIZE_SAI
    int 80h

    mov eax,1
    mov ebx,0
    int 80h
