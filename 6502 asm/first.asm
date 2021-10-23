LDX #$0
STX $100
LDX #$0
STX $101

;page location
LDA #$0
STA $605

loop:
JSR remove
JSR draw
JSR logic
LDA $605
JMP startwait



draw:
CLC
LDA $100
ADC $101
TAX

LDA $605

CMP #$0
BEQ drawline1

CMP #$1
BEQ drawline2

CMP #$2
BEQ drawline3

CMP #$3
BEQ drawline4

drawline1: 
  LDA #$03
  STA $0200,x
  JMP enddrawline
drawline2:
  LDA #$03
  STA $0300,x
  JMP enddrawline
drawline3:
  LDA #$03
  STA $0400,x
  JMP enddrawline
drawline4:
  LDA #$03
  STA $0500,x


enddrawline:

RTS

remove:
CLC
LDA $102
ADC $103
TAX

LDA #$00
STA $0200,x
STA $0300,x
STA $0400,x
STA $0500,x
RTS


logic:

;move y down
LDA $100
STA $102

CMP #$e0
BEQ nextpage
JMP elsenextpage
   nextpage:
   LDY $605
   INY
   TYA
   CMP #$4
   BEQ rolebackpage
   JMP elsenextpage
      rolebackpage:
      LDY #$0

      LDX #$0
      STX $100
      STX $101
   elsenextpage:
   STY $605
LDA $100
CLC
ADC #$20
STA $100

;move x right
LDX $101
STX $103
INX
STX $101 

RTS


startwait:
LDX #$0
JMP wait
RTS

wait:
INX
TXA
CMP #$20
BEQ stopwait
JMP wait

stopwait:
JMP loop