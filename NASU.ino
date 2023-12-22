#include <DFRobotDFPlayerMini.h>

#include <SoftwareSerial.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  


#define rad_tes 2
#define arm 3
#define clap 5
#define clapR 4
#define zap 7
#define zapR 6
#define zapSB 9
#define son 8
#define sonR 11
#define sonSB 10

#define RB2_W 21
#define GPS_SP 22
#define RB1_W 23
#define GPS_W 24
#define BAS_T 25
#define RB2_A 26
#define BAS_A 27
#define RB1_A 28
#define BAS_R 27

#define event 42
#define bar 44
#define accel 45
#define zapal 46
#define par 47
#define esup 48
#define Fready 25
#define napr 50
#define flash 51
#define GSMW 52
#define SDW 53

#define otriv 43
#define timer_par 49

#define redy A5
#define ESSP 34
#define key 36
#define startB 38
#define l_deny 40
#define sbros 32

int Prad_tes = 1;
int Parm = 1;
int Pclap = 1;
int PclapR = 1;
int Pzap = 1;
int PzapR = 1;
int PzapSB = 1;
int Pson = 1;
int PsonR = 1;
int PsonSB = 1;
int PTest = 1;

int pk = 0;

int menue_position = 0;
boolean button_state = 1;
boolean clc = 0;
long millis_of_cl = 0;
int menue_stage = 1;
long mill = 0;
boolean sig1 = 0;
boolean pr_bts = 1;
String data = "";
boolean checkb = false;
boolean key_sate = false;
boolean Fready_state = false;
boolean basu_state = 0;
int FASE = 0;
String Stest = "test cycle";
String Slaunch = "launch cycle";


String command = "sent";


boolean lift_off = false;
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
void setup() {
    
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  
  if (!myDFPlayer.begin(Serial1)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(30); 
   
  lcd.init();                       
  lcd.backlight();
  
  pinMode(arm, INPUT);
  pinMode(clap, INPUT);
  pinMode(clapR, INPUT);
  pinMode(zap, INPUT);
  pinMode(zapR, INPUT);
  pinMode(zapSB, INPUT);
  pinMode(son, INPUT);
  pinMode(sonR, INPUT);
  pinMode(sonSB, INPUT);
  pinMode(son, INPUT);
  pinMode(ESSP, INPUT_PULLUP);
  pinMode(key, INPUT_PULLUP);
  pinMode(startB, INPUT_PULLUP);
  pinMode(l_deny, INPUT_PULLUP);
  pinMode(sbros, INPUT_PULLUP);

  pinMode(event, INPUT_PULLUP);

  pinMode(RB2_W, OUTPUT);
  pinMode(GPS_SP, OUTPUT);
  pinMode(RB1_W, OUTPUT);
  pinMode(GPS_W, OUTPUT);
  pinMode(BAS_T, OUTPUT);
  pinMode(RB2_A, OUTPUT);
  pinMode(BAS_A, OUTPUT);
  pinMode(RB1_A, OUTPUT);
  pinMode(BAS_R, OUTPUT);
  pinMode(49, OUTPUT);
  pinMode(bar, OUTPUT);
  pinMode(accel, OUTPUT);
  pinMode(zapal, OUTPUT);
  pinMode(par, OUTPUT);
  pinMode(esup, OUTPUT);
  pinMode(Fready, OUTPUT);
  pinMode(napr, OUTPUT);
  pinMode(GSMW, OUTPUT);
  pinMode(SDW, OUTPUT);
  pinMode(flash, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("NASU V3.0 for M1");
  lcd.setCursor(0,1);
  lcd.print("start 10.12.23");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(">>"+Stest);
  lcd.setCursor(0,1);
  lcd.print(Slaunch);
  pinMode(A4, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(43, OUTPUT);
  while (digitalRead(key) == 0 ){
     lcd.setCursor(0,0);
     lcd.print("ERROR - 1");
     lcd.setCursor(0,1);
     lcd.print("Turn key off");
   
    }
   while((!digitalRead(2))or(!digitalRead(3))or(!digitalRead(4))or(!digitalRead(5))or(!digitalRead(6))or(!digitalRead(7))or(!digitalRead(8))or(!digitalRead(9))or(!digitalRead(10))or(!digitalRead(11))){
    lcd.setCursor(0,0);
     lcd.print("ERROR - 2");
     lcd.setCursor(0,1);
     lcd.print("Turn buttons off");
    }
  lcd.setCursor(0,0);
  lcd.print("NASU is ready");
  lcd.setCursor(0,1);
  lcd.print("to operate - key");
}

void loop() {
  
  if(digitalRead(ESSP)){
    command = "ParFuse";
    lcd.setCursor(0,0);
    lcd.print("ESSP com. order     ");
    }

  if (lift_off){analogWrite(A4, 255);}
  if ((basu_state)and(!Fready_state)){
    digitalWrite(Fready, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Basu OK");
    Fready_state=true;
    }
 if (digitalRead(key)== 0 ){
  if (!key_sate){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("key On - work");
    key_sate = true;
    }
 PGS_BUTT();
 }else{
 if ((digitalRead(key) )and(key_sate)){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("key Off - block");
    key_sate = false;
  }
 }
 Listen();
 


 if ((digitalRead(key)==0)and(checkb)){
  analogWrite(A5, 255);
  }       
}
void PGS_BUTT(){
   if((digitalRead(clap)!=Pclap)and(Pclap == 1)){
    Serial2.println("kon1");
    Serial.println("on");
    Pclap = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("klap press sent");
    delay(100);
    } 
   if((digitalRead(clap)!=Pclap)and(Pclap == 0)){
    Serial2.println("koff1");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("klap depres sent");
    Pclap = 1;
    delay(100);
    } 
     if((digitalRead(clapR)!=PclapR)and(PclapR == 1)){
    Serial2.println("kon2");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("clap open sent");
    PclapR = 0;
    delay(100);
    } 
   if((digitalRead(clapR)!=PclapR)and(PclapR == 0)){
    Serial2.println("koff2");
    Serial.println("off");
    PclapR = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("clap close sent");
    delay(100);
    } 
     if((digitalRead(zap)!=Pzap)and(Pzap == 1)){
    Serial2.println("kon3");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("zap press sent");
    Pzap = 0;
    delay(100);
    } 
   if((digitalRead(zap)!=Pzap)and(Pzap == 0)){
    Serial2.println("koff3");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("zap depress sent");
    Pzap = 1;
    delay(100);
    } 
     if((digitalRead(zapR)!=PzapR)and(PzapR == 1)){
    Serial2.println("kon4");
    Serial.println("on");
    PzapR = 0;
    delay(100);
    } 
   if((digitalRead(zapR)!=PzapR)and(PzapR == 0)){
    Serial2.println("koff4");
    Serial.println("off");
    PzapR = 1;
    delay(100);
    } 
     if((digitalRead(zapSB)!=PzapSB)and(PzapSB == 1)){
    Serial2.println("kon5");
    Serial2.println("koff3");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("zapSB start sent");
    PzapSB = 0;
    delay(100);
    } 
   if((digitalRead(zapSB)!=PzapSB)and(PzapSB == 0)){
    Serial2.println("koff5");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("zapSB stop sent");
    PzapSB = 1;
    delay(100);
    } 
     if((digitalRead(son)!=Pson)and(Pson == 1)){
    Serial2.println("kon6");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Son press sent");
    Pson = 0;
    delay(100);
    } 
   if((digitalRead(son)!=Pson)and(Pson == 0)){
    Serial2.println("koff6");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Son1 depress sent");
    Pson = 1;
    delay(100);
    } 
     if((digitalRead(sonR)!=PsonR)and(PsonR == 1)){
    Serial2.println("kon7");
    Serial.println("on");
    PsonR = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Son2 press sent");
    delay(100);
    } 
   if((digitalRead(sonR)!=PsonR)and(PsonR == 0)){
    Serial2.println("koff7");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Son2 depres sent");
    PsonR = 1;
    delay(100);
    } 
     if((digitalRead(sonSB)!=PsonSB)and(PsonSB == 1)){
    Serial2.println("koff7");
    Serial2.println("koff6");
    Serial2.println("kon8");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sons stop, drop");
    PsonSB = 0;
    delay(100);
    } 
   if((digitalRead(sonSB)!=PsonSB)and(PsonSB == 0)){
    Serial2.println("koff8");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Sons stop drop");
    PsonSB = 1;
    delay(100);
    } 
   if((digitalRead(rad_tes)!=PTest)and(PTest == 0)){
    PTest = 1;
    if (FASE == 0){
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("korobka test");
    }
    if (FASE == 1){
     Serial2.println("sent"); 
      }
    }
    if((digitalRead(rad_tes)!=PTest)and(PTest == 1)){
    PTest = 0;
    Serial2.println("ctest");
    delay(100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("if con. ok work");
    }
    if(( digitalRead(event) == 0)) {
      if (FASE == 0){
      Serial2.println("BTest");
      delay(300);
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("basu test...");
      digitalWrite(53, LOW);
      }
      if (FASE == 1){
      command = "GPS";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GPS reqest");  
        }
      } 

    if((digitalRead(arm)!=Parm)and(Parm == 0)){
    Serial2.println("BDISARM");
    Serial.println("off");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" basu disarmed");
    Parm = 1;
    delay(100);
    } 
     if((digitalRead(arm)!=Parm)and(Parm == 1)){
    Serial2.println("BARM");
    Serial.println("on");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("basu armed");
    Parm = 0;
    delay(100);
    } 
       if(( digitalRead(sbros) == 1)and(pk ==0)) {
  
        Serial2.println("kon4");
       delay(300);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1 piro egnite");
      pk = 1;

      } 

             if(( digitalRead(sbros) == 1)and(pk ==1)) {
  
        Serial2.println("kon5");
       delay(300);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("2 piro egnite");
      pk = 2;

      } 

             if(( digitalRead(sbros) == 1)and(pk ==2)) {
  
      Serial2.println("koff4");
      Serial2.println("koff5");
      delay(300);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("piro shut down");
      pk = 0;

      }

      if(( digitalRead(l_deny) == 1)) {
      Serial2.println("koff1");
      Serial2.println("koff2");
      Serial2.println("koff3");
      Serial2.println("koff4");
      Serial2.println("koff5");
      Serial2.println("koff6");
      Serial2.println("koff7");
      Serial2.println("koff8");

      delay(100);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("All clapan close");
      } 
}

void Listen(){
  if(Serial2.available()>0){
    char a = Serial2.read();
    if((a != char(13) and a != char(10))){
      data = data + a;
      }
                        
    else {

          lcd.setCursor(0,1);
          if( data!="$"){
          Serial.println(data);   
          lcd.print(data);
      }
          
          if(data == "BASU_INIT_OK"){
            basu_state = true;
            digitalWrite(53, HIGH);
            }
            if(data == "LiftOff"){
            lcd.clear();
            lift_off = true;
            FASE = 1;
            Serial2.println("sent");
        lcd.setCursor(0,0);
         lcd.print("LIFTOFF         ");
            }
          if(data == "FusedT"){
            digitalWrite(49, HIGH);
            lift_off = true;
           
           
          lcd.setCursor(0,0);
         lcd.print("TIMER EGNITE       ");
            }
           if(data == "FusedB"){
            digitalWrite(51, HIGH);
            lift_off = true;
           
           
           lcd.setCursor(0,0);
          lcd.print("BAROM EGNITE"      );
            }
            if(data == "BASU_OK"){
            lcd.setCursor(0,0);
         lcd.print("BASU TEST OK            ");
         digitalWrite(53, HIGH);
            }
                if(data == "FusedC"){
            lcd.setCursor(0,0);
         lcd.print("ESSP WORKED           ");
            }
           if ((FASE ==1)and(data =="$")){
            if(command !=""){
             Serial.println(command);
            Serial2.println(command);
            command = "";
            }
            if (command != "GPS"){
            Serial2.println("sent");
            }
            } 
            if(data == "GPS_work"){
            lcd.setCursor(0,0);
         lcd.print("GPS GOT           ");
         Serial2.println("sent");
            }
          data = "";
    }


}
}
