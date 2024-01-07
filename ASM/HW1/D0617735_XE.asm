START    START    2000
FIRST    LDA      AA
         ADD      BB
         ADD     #1
         STA      CC
         SUB      DD
         SUB     #2
         STA      EE    
         MUL      AA
         MUL     #3
         STA      FF
         LDA      EE
         DIV      AA
         DIV     #4
         STA      GG
         MUL     #3
         STA      HH
         LDA     #0
         STA      II
         LDA      FF
         COMP     HH
         JEQ      DO
         END      START






AA       WORD     2
BB       WORD     7
CC       RESW     1
DD       WORD     3
EE       RESW     1
FF       RESW     1
GG       RESW     1
HH       RESW     1
II       RESW     1

DO       LDA      GG
         DIV     #6
         STA      II
