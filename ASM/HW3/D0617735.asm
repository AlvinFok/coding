START     START   0
REG_L     RESW    1            save the JSUB address
          LDS     #3           set the index distence
         +JSUB    INIT
INDEX     WORD    0            index of input which is recording which group of number we are doing (0 is group one) -- (6 is group 2)...
ANSID     WORD    0            index of ans array
GCD_LOOP +JSUB    GCD
          LDA     INDEX
          ADD     #6           move the index to the next group of number
          STA     INDEX
          LDA     ANSID
          ADD     #6           the index of ans also add 6 because the design of the array store gcd and then lcd ,so index 0 is gcd of group number1 ,index 3 is lcd of group nomber1, index 6 is gcd of group number2 and so on
          STA     ANSID
          LDA     #30          the total index is 30 because the input array have 10 numbers
          COMP    INDEX
          JGT     GCD_LOOP
          CLEAR   A
          STA     INDEX        reset those indexs for lcm computing
          STA     ANSID
LCM_LOOP  +JSUB   LCM
          LDA     #30
          COMP    INDEX
          JGT     LCM_LOOP


LCM       STL      REG_L
          LDX      INDEX
          LDA      INPUT,X
          STA      NUM1
          ADDR     S,X
          LDA      INPUT,X
          STA      NUM2
          ADDR     S,X
          STX      INDEX
          LDA      NUM1
FACTOR    RESW     1
          LDX      ANSID
          LDA      ANS,X
          STA      FACTOR
          ADDR     S,X
          STX      ANSID

          LDA      NUM1
          DIV      FACTOR
          STA      NUM1
          LDA      NUM2
          DIV      FACTOR
          MUL      NUM1
          MUL      FACTOR

          STA      ANS,X
          ADDR     S,X
          STX      ANSID
          J        @REG_L



ANS       RESW    5*2
GCD       STL     REG_L
          LDX     INDEX

          LDA     INPUT,X        load the array into NUM1 and NUM2
          STA     NUM1
          ADDR    S,X
          LDA     INPUT,X
          STA     NUM2
REMAIN    RESW    1
NUM1      RESW    1
NUM2      RESW    1
QUOTIENT  RESW    1
LOOP      LDA     NUM1
          DIV     NUM2
          STA     QUOTIENT       NUM1/NUM2 and get quotient

          LDA     NUM2           remainder = num1 - num2*quotient
          MUL     QUOTIENT
          LDL     NUM1
          SUBR    A,L
          STL     REMAIN         save the remainder into REMAIN
          LDA     NUM2
          STA     NUM1
          STL     NUM2
          LDA     #0
          COMP	  REMAIN
          JLT	  LOOP           the remainder greater than 0  then loop again

          LDA     NUM1           find the GCD and it is in NUM1
          LDX     ANSID          
          STA     ANS,X          save the gcd into ANS array
          JEQ	  @REG_L          junm back to the main

INPUT     RESW    5*2
INIT      STL     REG_L
          LDA     #15          initialing vlaues
          STA     INPUT,X
          ADDR    S,X
          LDA     #30
          STA     INPUT,X
          ADDR    S,X
          LDA     #34
          STA     INPUT,X
          ADDR    S,X
          LDA     #51
          STA     INPUT,X
          ADDR    S,X
          LDA     #60
          STA     INPUT,X
          ADDR    S,X
          LDA     #21
          STA     INPUT,X
          ADDR    S,X
          LDA     #199
          STA     INPUT,X
          ADDR    S,X
          LDA     #99
          STA     INPUT,X
          ADDR    S,X
          LDA     #63
          STA     INPUT,X
          ADDR    S,X
          LDA     #63
          STA     INPUT,X
          ADDR    S,X
          J       @REG_L      jump back to the next line of the main after "+JSUB INIT"


          END     START
          
