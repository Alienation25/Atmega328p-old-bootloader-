#include <Arduino.h>
#include <GyverEncoder.h>



// управление драйвером 
#define PWMA 6   
#define PWMB 3
#define AIN1 7
#define AIN2 2
#define BIN1 8
#define BIN2 9

// энкодер мотора 
#define ne1  5
#define ne2  2


//управление оптопарами 
#define int1 A5
#define int2 13
#define int3 A4
#define int4 A2

//концевые выключатели
#define maxpos 11
#define minpos 12


//потенциометр
#define potentiometr A0

int motorSpeed = 40; 

void downDC(int motorSpeed,int controldelay){
     digitalWrite(AIN1, HIGH);  
     digitalWrite(AIN2, LOW); 
     digitalWrite(BIN1, HIGH);    // крутим моторы в вниз
     digitalWrite(BIN2, LOW);
     analogWrite(PWMB, motorSpeed);

       digitalWrite(int1,0);
       digitalWrite(int2,1); //порт за контроль вниз
       digitalWrite(int3,0);
       digitalWrite(int4,0);

     delay(controldelay);

}

void upDC(int motorSpeed,int controldelay){
     digitalWrite(AIN1, LOW);      // крутим моторы в верх
     digitalWrite(AIN2, HIGH);    
     digitalWrite(BIN1, LOW);      
     digitalWrite(BIN2, HIGH); 
     analogWrite(PWMB, motorSpeed); 

       digitalWrite(int1,1);//порт за контроль вверх
       digitalWrite(int2,0);
       digitalWrite(int3,0);
       digitalWrite(int4,0);
     
     
     delay(controldelay);
}

void stopDC(){
    digitalWrite(AIN1, LOW);      // крутим моторы в верх
    digitalWrite(AIN2, LOW);    
    digitalWrite(BIN1, LOW);      
    digitalWrite(BIN2, LOW); 
    analogWrite(PWMB, 255); 
}

void maxpositionINT(){// срабатывания концевика и питания по 24V
       stopDC();
       digitalWrite(int1,0);
       digitalWrite(int2,0);
       digitalWrite(int3,1);
       digitalWrite(int4,0);
       delay(5000);
}


void minpositionINT(){//срабатывания концевика и питания по 24V
       stopDC();
       digitalWrite(int1,0);//порт за контроль вверх
       digitalWrite(int2,0);
       digitalWrite(int3,0);
       digitalWrite(int4,1);
       delay(5000);


}










void Homepostion(){//start pos
bool triger = 0;
 while (triger==0){
   if(digitalRead(minpos)!=0){
      downDC(40,0);
      Serial.println("homeposition");
    }else{
      minpositionINT();
      triger=1;  
    }

  }

}


void setup() {
 Serial.begin(9600);

 pinMode(int1,OUTPUT);// int1
 pinMode(int2,OUTPUT);// int2
 pinMode(int3,OUTPUT);// int3 управление оптопарами  
 pinMode(int4,OUTPUT);// int4

 pinMode(maxpos,INPUT); //концевой выключатель максимального положения 
 pinMode(minpos,INPUT);//концевой выключатель нулевого положения 

 pinMode(potentiometr,INPUT);//потенциометр 

 pinMode(PWMA, OUTPUT);  
 pinMode(PWMB, OUTPUT);  
 pinMode(AIN1, OUTPUT);  
 pinMode(AIN2, OUTPUT);  
 pinMode(BIN1, OUTPUT);  
 pinMode(BIN2, OUTPUT); 

  Homepostion();
}




void loop() {
 stopDC();
 if (digitalRead(minpos)==0){
   for(int i=0;i<map(analogRead(potentiometr),0,1023,0,78);i++){//78 max 
     upDC(40,100);
     Serial.println(i);
    if(digitalRead(maxpos)==0){
      maxpositionINT();
      Homepostion();
    }

   }
   Homepostion();
 }else{
   
 }
 


 
 



  
}


/*


 if(digitalRead(maxpos)==0){
    downDC(40,500);
    
 }

 */