#include <Wire.h>
#include "Sodaq_DS3231.h"
# include <Servo.h>
Servo panel;

unsigned long time;
float tiempo = 5000.50;// CADA 5.5 SEGUNDOS AVANZA UN GRADO, HASTA LLEGAR A LOS 150°
unsigned long  t =0;

int pos_default =35;
int pos_default_add=35;
boolean act_1,act_2=false;
char DiaSemana[][4] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab" };

    // La linea fija la fecha, hora y dia de la semana, 
    //se debe suprimir la linea en la segunda carga
    // Ejemplo 2024 octubre 10, 09:35:00  dia 4-Jueves 
    //(0=Dom, 1=Lun, 2=Mar, 3=Mie, 4=Jue, 5=Vie, 6=Sab)
// DateTime dt(2024, 10, 10, 09, 35, 0, 4);

void setup () 
{
    Serial.begin(9600);
    Wire.begin();
    rtc.begin();
   // La linea fija la fecha, hora y dia de la semana, se debe suprimir la linea en la segunda carga 
 //rtc.setDateTime(dt);
  
  panel.attach(2);
  panel.write(35);
}

void loop () 
{
 
  
  int LDR = analogRead(A0);
  
 Serial.print("SENSOR_LDR ");
 Serial.println(LDR);
 
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.date(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.print(' ');
    Serial.print(DiaSemana[now.dayOfWeek()]);
    Serial.println();
   delay(1000); // Se actualiza cada segundo

   if (LDR <=600){
    panel.write(pos_default);
}
if(now.minute()>=36&& now.minute()<46){
  act_1=true;
 
}

  
if ( act_1==true){
       
         time=millis();
        if(time-t > tiempo){
         t=time;
         pos_default_add++;
          }
        if(LDR > 800){
       panel.write (pos_default_add);
       Serial.print("GRADOS SERVO");
       Serial.println(pos_default_add);
        }
}

if(pos_default_add >=150){
  act_1=false;
}
if(pos_default_add >=150 && now.minute()>=46){       
         pos_default_add =35;
         panel.write (pos_default);
         
}
}
