// 1 - row
// 2 - col

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

void loop()
{
int i,j,Stime = 100;

for(i=1;i<=Stime;i++)
{
led_select(3,6);
led_select(3,5);
led_select(3,4);
led_select(4,3);
led_select(5,3);
led_select(6,3);
led_select(7,4);
led_select(7,5);
led_select(7,6);
led_select(6,6);
led_select(5,6);
led_select(5,5);
}

for(i=0;i<=Stime;i++)
{
led_select(3,3);
led_select(4,3);
led_select(5,3);
led_select(6,3);
led_select(7,4);
led_select(7,5);
led_select(6,6);
led_select(5,6);
led_select(4,6);
led_select(3,6);
}

for(i=0;i<Stime;i++)
{
led_select(2,4);
led_select(2,5);
led_select(3,3);
led_select(3,6);
led_select(4,3);
led_select(4,6);
led_select(5,3);
led_select(5,4);
led_select(5,5);
led_select(6,3);
led_select(6,5);
led_select(7,3);
led_select(7,6);
}

for(i=0;i<=Stime;i++)
{
led_select(3,3);
led_select(4,3);
led_select(5,3);
led_select(6,3);
led_select(7,4);
led_select(7,5);
led_select(6,6);
led_select(5,6);
led_select(4,6);
led_select(3,6);
}


}

void led_select(int row,int col)
{ int col_encode,row_encode;
  int powr=1,powc=1;
  int i;
  
  for(i=0;i<row-1;i++)
  powr *= 2;
  for(i=0;i<col-1;i++)
  powc *= 2;
  
  
  row_encode = 255 - powr;
  col_encode = powc;
  
  digitalWrite(LATCH1,LOW);
  digitalWrite(OE1,HIGH);
  shiftOut(DATA1,CLOCK1,MSBFIRST,row_encode); //row
  digitalWrite(LATCH1,HIGH);
  digitalWrite(OE1,LOW);
  
  digitalWrite(LATCH2,LOW);
  digitalWrite(OE2,HIGH);
  shiftOut(DATA2,CLOCK2,MSBFIRST,col_encode); //col
  digitalWrite(LATCH2,HIGH);
  digitalWrite(OE2,LOW);
  delay(1);
}
