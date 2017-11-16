// 1 - row
// 2 - col

#define DATA1 12
#define DATA2 4

#define LATCH1 11 
#define LATCH2 3

#define CLOCK1 10 
#define CLOCK2 2

#define OE1 8
#define OE2 7

void setup()
{
pinMode(LATCH1,OUTPUT);
pinMode(CLOCK1,OUTPUT);
pinMode(DATA1,OUTPUT);
pinMode(OE1,OUTPUT);

pinMode(LATCH2,OUTPUT);
pinMode(CLOCK2,OUTPUT);
pinMode(DATA2,OUTPUT);
pinMode(OE2,OUTPUT);
randomSeed(analogRead(0));
// data 2 gives +ve
//data 1 gives -ve
test();
}

void loop()
{ //            G                                                 
  byte row[] = {B11000011,B10111101,B10111101,B10101101,B10001101,
                B11111111,
                B11000001,B10111111,B10111111,B10111111,B11000001,
                B11111111,
                B10000011,B11101101,B11101101,B11001101,B10110011,      
                B11111111,
                B11000001,B10111111,B10111111,B10111111,B11000001            
        };
  int k,row_size = 22;
  int col = 0x80,i,j;
  
  //
  
  for(i=0;i<=8+row_size+2;i++)
  {
    for(j=0;j<10;j++)//delay loop
      
      for(k=0;k<=row_size;k++)
      if(i-k >= 0) // this if statement makes sure that all rightmost lights are correctly lit
      led_hexselect(row[k],col >> i-k);
      else
      led_hexselect(0xff,0x00); //off the display // equilise the delay
  }
  
  col= 0x80;
}

void led_select(int row,int col)
{ int col_decode,row_decode;
  int powr=1,powc=1;
  int i;
  
  if(row <= 8 & col <= 8 & row >= 0 & col >= 0)
  {
  for(i=0;i<row-1;i++)
  powr *= 2;
  for(i=0;i<col-1;i++)
  powc *= 2;
  
  
  row_decode = 255 - powr;
  col_decode = powc;
  
  digitalWrite(LATCH1,LOW);
  digitalWrite(OE1,HIGH);
  shiftOut(DATA1,CLOCK1,MSBFIRST,row_decode); //row
  digitalWrite(LATCH1,HIGH);
  digitalWrite(OE1,LOW);
  
  digitalWrite(LATCH2,LOW);
  digitalWrite(OE2,HIGH);
  shiftOut(DATA2,CLOCK2,MSBFIRST,col_decode); //col
  digitalWrite(LATCH2,HIGH);
  digitalWrite(OE2,LOW);
  delayMicroseconds(200);
  }
}

void led_hexselect(int row,int col)
{
  digitalWrite(LATCH1,LOW);
  digitalWrite(OE1,HIGH);
  shiftOut(DATA1,CLOCK1,MSBFIRST,row); //row
  digitalWrite(LATCH1,HIGH);
  digitalWrite(OE1,LOW);
  
  digitalWrite(LATCH2,LOW);
  digitalWrite(OE2,HIGH);
  shiftOut(DATA2,CLOCK2,MSBFIRST,col); //col
  digitalWrite(LATCH2,HIGH);
  digitalWrite(OE2,LOW);
  delayMicroseconds(500);
}

void test(void)
{
byte i,j;

for(i=0;i<=10;i++){
led_hexselect(0x00,0xff);
delay(20);
led_hexselect(0x00,0x00);
delay(20);
}

led_hexselect(0x00,0xff);
delay(500);
led_hexselect(0x00,0x00);
}


