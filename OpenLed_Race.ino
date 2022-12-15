int value = 0;

                                                            
#include <Adafruit_NeoPixel.h>
#define MAXLED         300 

#define PIN_LED        D3  /
#define PIN_P1         D2   
#define PIN_P2         D1   
#define PIN_S1         D5   
#define PIN_S2         D6   

byte swap1=0;  
byte swap2=0;   


int NPIXELS=MAXLED; // leds on track

#define COLOR1    track.Color(255,0,0)
#define COLOR2    track.Color(0,255,0)


float speed1=0;
float speed2=0;
float dist1=0;
float dist2=0;

byte loop1=0;
byte loop2=0;

byte leader=0;
byte loop_max=5; //total laps race


float ACEL=0.2;
float kf=0.015; //friction constant
float kg=0.003; //gravity constant

int t_sw1=0;
int t_sw2=0;
byte flag_sw1=0;
byte flag_sw2=0;
byte flag_sp1=0;
byte flag_sp2=0;

byte draworder=0;
 
unsigned long timestamp=0;

Adafruit_NeoPixel track = Adafruit_NeoPixel(2*MAXLED, PIN_LED, NEO_GRB + NEO_KHZ800);

int tdelay = 5; 

long lastMsg;

byte t1,t2;

void setup() {
  track.begin(); 
  pinMode(PIN_P1,INPUT_PULLUP); 
  pinMode(PIN_P2,INPUT_PULLUP);  
  pinMode(PIN_S1,INPUT_PULLUP); 
  pinMode(PIN_S2,INPUT_PULLUP);  
  t1=0; t2=1;
  start_race();    

}


void start_race(){for(int i=0;i<2*NPIXELS;i++){track.setPixelColor(i, track.Color(0,0,0));};
                  track.show();
                  delay(2000);
                  track.setPixelColor(12, track.Color(0,255,0));
                  track.setPixelColor(11, track.Color(0,255,0));
                  track.show();
                  track.setPixelColor(12, track.Color(0,0,0));
                  track.setPixelColor(11, track.Color(0,0,0));
                  track.setPixelColor(10, track.Color(255,255,0));
                  track.setPixelColor(9, track.Color(255,255,0));
                  track.show();
                  track.setPixelColor(9, track.Color(0,0,0));
                  track.setPixelColor(10, track.Color(0,0,0));
                  track.setPixelColor(8, track.Color(255,0,0));
                  track.setPixelColor(7, track.Color(255,0,0));
                  track.show();
                  timestamp=0;              
                 };

int dd;


void draw_car1(byte t){
  dd = (t == 1)?0:300; 
  for(int i=0;i<=loop1;i++){track.setPixelColor(((word)dist1 % NPIXELS)+i+dd, track.Color(0,255-i*20,0));}
}
  
void draw_car2(byte t ){
  dd = (t == 1)?0:300; 
  for(int i=0;i<=loop2;i++){track.setPixelColor(((word)dist2 % NPIXELS)+i+dd, track.Color(255-i*20,0,0));}
}

char msg[20];
   
void loop() {

    if ( (flag_sw1==1) && (digitalRead(PIN_P1)==0) ) {flag_sw1=0;speed1+=ACEL;};
    if ( (flag_sw1==0) && (digitalRead(PIN_P1)==1) ) {flag_sw1=1;};
    if ( (flag_sp1==1) && (digitalRead(PIN_S1)==0) ) {flag_sp1=0;t1= !t1;};
    if ( (flag_sp1==0) && (digitalRead(PIN_S1)==1) ) {flag_sp1=1;};
    speed1-=speed1*kf; 
    
   if ( (flag_sw2==1) && (digitalRead(PIN_P2)==0) ) {flag_sw2=0;speed2+=ACEL;};
   if ( (flag_sw2==0) && (digitalRead(PIN_P2)==1) ) {flag_sw2=1;};
   if ( (flag_sp2==1) && (digitalRead(PIN_S2)==0) ) {flag_sp2=0;t2= !t2;};
   if ( (flag_sp2==0) && (digitalRead(PIN_S2)==1) ) {flag_sp2=1;};
    
       
    speed2-=speed2*kf; 

if (dist1>dist2) {leader=1;} 
       else {leader=2;};
       dist1+=speed1;
       dist2+=speed2;
       
  if (t1 == t2 ) {
      if ( leader == 1 && (dist2 + loop2 - 1)>= dist1) dist2=dist1-loop1-5;
      if ( leader == 2 && (dist1 +loop1 -1 )>= dist2) dist1=dist2-loop2-5;     
    }


         
    if (dist1>NPIXELS*loop1) {loop1++;};
    if (dist2>NPIXELS*loop2) {loop2++;};

     
    if (loop1>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(0,255,0));}; track.show();
                                                    loop1=0;loop2=0;dist1=0;dist2=0;speed1=0;speed2=0;timestamp=0;
                                                    start_race(); 
                                                   }
    if (loop2>loop_max) {for(int i=0;i<NPIXELS;i++){track.setPixelColor(i, track.Color(255,0,0));}; track.show();
                                                    loop1=0;loop2=0;dist1=0;dist2=0;speed1=0;speed2=0;timestamp=0;
                                                    start_race();
                                                   }

for(int i=0;i<2*NPIXELS;i++){
      track.setPixelColor(i, track.Color(0,0,0));
      };
      draw_car1(t1);draw_car2(t2); 
          
    track.show(); 
    delay(tdelay);
    
    
}