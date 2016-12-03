/*  
 *  GPRS/GSM Quadband Module (SIM900)
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  a
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           2.0
 *  Design:            David Gascón 
 *  Implementation:    Alejandro Gallego & Marcos Martinez
 */
 
int8_t answer;
int onModulePin= 4; //sim9000 powerpin
int relayPin= 7; //relaypin
int debugLed= 13; //relaypin


char aux_str[100];


char apn[]="internet";
char user_name[]="";
char password[]="";
char IP_address[]="192.241.226.168";
char port[]="80";

char ip_data[64];

int inComing = 0;
char gprsBuffer[64];

#define DEFAULT_TIMEOUT          5   //seconds
#define DEFAULT_INTERCHAR_TIMEOUT 1500   //miliseconds
void  sim900_read_buffer(char* buffer,int count,  unsigned int timeout = DEFAULT_TIMEOUT, unsigned int chartimeout = DEFAULT_INTERCHAR_TIMEOUT);


void setup(){

    pinMode(onModulePin, OUTPUT);
    pinMode(relayPin, OUTPUT);
    pinMode(debugLed, OUTPUT);
    
    digitalWrite(relayPin, LOW); // make sure relay is off
    digitalWrite(debugLed, LOW); 
    
    Serial.begin(9600); 

    power_on();
    
    delay(3000);
    digitalWrite(debugLed, HIGH);
    
    while( sendATcommand2("AT+CREG?", "+CREG: 0,1", "+CREG: 0,5", 1000)== 0 );

    //Serial.println("Modul ready");
    
    digitalWrite(debugLed, LOW); //means Modul ready

    uint8_t x=0,  answer=0;
    char response[100];

    sendATcommand("AT+CLIP=1", "OK", 2000);
   
}


String getPhoneNumber(String mygprsBuffer){
String temp;

temp=mygprsBuffer.substring(19,31);
//+CLIP: "+905327945990",145,"",,"",0
//Serial.print(temp);
return temp; 
}

void loop(){

   String incomingPhoneNumber;
  
   if((Serial.available() != 0)) {
       inComing = 1;
   }else{ delay(100);}
   
   if(inComing){
      sim900_read_buffer(gprsBuffer,32,DEFAULT_TIMEOUT);
      //Serial.print(gprsBuffer);
      
      if(NULL != strstr(gprsBuffer,"RING")) {
          
          incomingPhoneNumber = getPhoneNumber(gprsBuffer);
          delay(1000);
          sendATcommand("ATH", "OK", 2000);
          sim900_clean_buffer(gprsBuffer,64);
          
       
          if (auth_web(incomingPhoneNumber)){
            digitalWrite(relayPin, HIGH); //relay open for 2.5 sec
            delay(2500);
            digitalWrite(relayPin, LOW);
            //Serial.println("Yetkili Numara");
          } else {
            //Serial.println("Yetkisiz Numara");
          }
         
          
          sendATcommand2("AT+CIPSHUT", "OK", "ERROR", 10000);
          delay(3000);
      }

      
     sim900_clean_buffer(gprsBuffer,32);  
     inComing = 0;
   }  
 
   

}


