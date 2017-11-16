// 1 - row negative
// 2 - col positive

#define DATA1 13
#define DATA2 4

#define LATCH1 12
#define LATCH2 3

#define CLOCK1 11
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
// data 2 gives +ve
//data 1 gives -ve
}

  int col;
  byte row;

void loop()
{
  col = 0x01;
  row = B11111110;
  while(col != 0x80){
  led_hexselect(0x00,col);
  col = col << 1;
  led_hexselect(row,0xff);
  row = L_rotate(row);
  delay(50);
  }  
  
  col = 0x80;
  row = B01111111;
  while(col != 0x00){
  led_hexselect(0x00,col);
  col = col >> 1;
  led_hexselect(row,0xff);
  row = R_rotate(row);
  delay(50);
  }


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
  delay(1);
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

byte L_rotate(byte num)
{
int temp;

temp = num & 0x01;
temp = temp << 7;
num = num >> 1;
num = num + temp;
return num;
}

byte R_rotate(byte num)
{
int temp;

temp = num & 0x80;
temp = temp >> 7;
num = num << 1;
num = num + temp;
return num;
}
