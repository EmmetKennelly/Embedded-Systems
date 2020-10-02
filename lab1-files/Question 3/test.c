#include <stdint.h>
 
typedef volatile struct {
 
 
 uint32_t DR;
 uint32_t RSR_ECR;
 uint8_t reserved1[0x10];
 const uint32_t FR;
 uint8_t reserved2[0x4];
 uint32_t LPR;
 uint32_t IBRD;
 uint32_t FBRD;
 uint32_t LCR_H;
 uint32_t CR;
 uint32_t IFLS;
 uint32_t IMSC;
 const uint32_t RIS;
 const uint32_t MIS;
 uint32_t ICR;
 uint32_t DMACR;
} pl011_T;

 
enum {
 RXFE = 0x10,
 TXFF = 0x20,
};
 
pl011_T * const UART0 = (pl011_T *)0x101f1000;
pl011_T * const UART1 = (pl011_T *)0x101f2000;
pl011_T * const UART2 = (pl011_T *)0x101f3000;
 
static inline char upperchar(char c) {
 if((c >= 'a') && (c <= 'z')) {
  return c - 'a' + 'A';
 } else {
  return c;
 }
}
 
static void uart_echo(pl011_T *uart) {
 if ((uart->FR & RXFE) == 0) {
  while(uart->FR & TXFF);
  uart->DR = upperchar(uart->DR);
 }
}


 
void print_uart0(const char *s) {
 while(*s != '\0') { /* Loop until end of string */
 UART0->DR = (unsigned int)(*s); /* Transmit char */
 s++; /* Next char */
 }
}

struct State {

  unsigned long Out;

  unsigned long Time; 

  unsigned long Next[4];};

typedef const struct State STyp;

#define goN   0

#define waitN 1

#define goE   2

#define waitE 3

STyp FSM[4]={

 {0x21,3000,{goN,waitN,goN,waitN}},

 {0x22, 500,{goE,goE,goE,goE}},

 {0x0C,3000,{goE,goE,waitE,waitE}},

 {0x14, 500,{goN,goN,goN,goN}}};

unsigned long S;  // index to the current state

unsigned long Input;

void c_entry() {
S = goN; 
unsigned int light;
int change =0;
int ch;
 for(;;) {
    //emulate this line LIGHT = FSM[S].Out;  // set lights
    light = FSM[S].Out;
    if (change){
       // TODO output lights value
       if (light & 1)
          print_uart0("North Green");
            if (light & 2){
               print_uart0("North Yellow \n");
           }
            if (light & 4){
               print_uart0("North Red \n");
           }
            if (light & 8){
               print_uart0("East Greem \n");
           }
            if (light & 16){
               print_uart0("East Yellow \n");
           }
            if (light & 32){
                print_uart0("East Red  \n"); 
           }
    change =0;
    } while(1){
     LIGHT = FSM[S].Out; 

    SysTick_Wait10ms(FSM[S].Time);
    Input = SENSOR;     
    S = FSM[S].Next[Input]; 
}
   if ((UART0->FR & RXFE) == 0) {
      //while(uart->FR & TXFF);
       int ch  = uart->DR;
       
   if (ch == 'E'){
   printf("Go east" )
   Input = 1;
   FSM.[S].Next[Input];
   }
   if (ch =='N'){
   printf("Go north")
   Input = 2;
   FSM.[S].Next[Input];
    }
  else if (ch == 'U'){
   Input = 3;
   FSM.[S].Next[Input];
   }
   else if (ch == 0){
   Input= 4;
   FSM.[S].Next[Input];
   }
      change =1;
      
    }


    S = FSM[S].Next[Input];  

  
 // uart_echo(UART1);
  //uart_echo(UART2);
 }
}
