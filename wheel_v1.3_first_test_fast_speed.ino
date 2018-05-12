/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 STEPPER MOTOR TORQUE CONTROLER BY
______  __                      _____                              __________                                      _________              
___  / / /_____ _______ ___________(_)______ _____  _______        ___  ____/_____ _______________ ______ ________ ______  /_____ ________
__  /_/ / _  _ \__  __ \__  ___/__  / _  __ `/_  / / /_  _ \       __  /_    _  _ \__  ___/__  __ \_  __ `/__  __ \_  __  / _  _ \__  ___/
_  __  /  /  __/_  / / /_  /    _  /  / /_/ / / /_/ / /  __/       _  __/    /  __/_  /    _  / / // /_/ / _  / / // /_/ /  /  __/_(__  ) 
/_/ /_/   \___/ /_/ /_/ /_/     /_/   \__, /  \__,_/  \___/        /_/       \___/ /_/     /_/ /_/ \__,_/  /_/ /_/ \__,_/   \___/ /____/  
                                        /_/                
░░░░░░░░░░░░▄▄
░░░░░░░░░░░█░░█
░░░░░░░░░░░█░░█
░░░░░░░░░░█░░░█
░░░░░░░░░█░░░░█
███████▄▄█░░░░░██████▄                
▓▓▓▓▓▓█░░░░░░░░░░░░░░█
▓▓▓▓▓▓█░░░░░░░░░░░░░░█
▓▓▓▓▓▓█░░░░░░░░░░░░░░█
▓▓▓▓▓▓█░░░░░░░░░░░░░░█
▓▓▓▓▓▓█░░░░░░░░░░░░░░█
▓▓▓▓▓▓█████░░░░░░░░░█
██████▀░░░░▀▀██████▀
01000010 01110010 01100001 01110011 01101001 01101100 01100101 01101001 01110010 01101111 01110011  01110011 01100001 01101111  01100110 01101111 01100100 01100001
42 72 61 73 69 6C 65 69 72 6F 73  73 61 6F  66 6F 64 61 
69 66  79 6F 75  67 6F 74  74 68 69 73  6D 61 73 73 61 67 65  63 6F 6E 67 72 61 74 75 6C 61 74 69 6F 6E 73 2C  79 6F 75  61 72 65  76 65 72 79  63 75 72 69 6F 75 73  62 75 74  6D 69 67 68 74  62 65  73 6D 61 72 74 
 * 
 * program in this version has the duty cicly calculated by the medium of 7 values, and self calibration
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define pulse_ip 7
#define resist 30 //DEFINE PIN 30 AS PULSE TO THE DIGITAL POTENTIOMETER
#define direct 31 // NO USE YET
#define inc 32  //DEFINE PIN 32 AS INCREMENT OR DECREMENT TO THE DIGITAL POTENTIOMETER
#define hold 33 // DEFINE PIN 33 AS HOLD POSITION TO DRIVER
#define warnled 35
#define buzzer 36
#define stepD 13 //DEFINE PIN 13 AS OUTPUT FOR STEP THE DRIVER
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int zphase,ontime, offtime,ontime2,offtime2,duty,percent,pulses,braking,minefect;   // DEFINE VARIABLES USED TO CALCULATE TIME ON, TIM OFF, DUTY AND PERCENTAGE OF TORQUE SENT TO DRIVER
int pwmF; 
float freq,period;

void setup()

{
Serial.begin(115200);
pinMode(pulse_ip,INPUT);
/*for (int i=0; i <= 2; i++)          //SElF CALIBRATION STARTING
  { digitalWrite (warnled, HIGH);   //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
    delay (500);                    //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
    digitalWrite (warnled, LOW);    //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
    delay (500);                    //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
    tone (36, 1000, 300);           //SEND A BUZER TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL/
    }
while(zphase!=1)                        //SELF CALIBRATION OF THE STEERIGN WHEEL
  {   digitalWrite (13, HIGH);         //THE PHASE Z OF THE ENCODER OMROM E6B2-C ONLY GOES UP ONCE PER REVOLUTION, SO THIS IS GOING TO BE THE CENTRE
      digitalWrite (warnled, HIGH);    //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
      delay (100);                     //IF THE WHEEL IS OUT OF CENTRE THE FUNCTION WHILE SEND A PULSE TO PIN 13 , SO THE DRIVER MOVES THE MOTOR IN ONE STEP
     digitalWrite (13, LOW);          //THIS REPEATS UNTIL THE CENTRE BE REACHED AND Z PHASE GOES HIGH, THEN RESET THE DISCOVERY AND CONTINUES THE PROGRAM
     digitalWrite (warnled, LOW);     //FLASH A LED ON PIN 35 TO INFORM THE USER THE SELF CALIBRATION OS STARTING AND NOT TO TOUCH THE WHEEL
    delay (100);    
   }
reset disco in pin nrst
*/        

  minefect = 5;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{   
    ontime = pulseIn(pulse_ip,HIGH);   //READ TIME ON
    offtime = pulseIn(pulse_ip,LOW);   //READ TIME OFF   
    ontime2 = pulseIn(pulse_ip,HIGH);   //READ TIME ON
    offtime2 = pulseIn(pulse_ip,LOW);   //READ TIME OFF
    period = (ontime+ontime2)/2+(offtime+offtime2)/2;           //CALCULATE THE FREQUENCY
    duty = (ontime/period)*100;        //CALCULATE THE DUTY CICLY PERCENTAGE
    percent = constrain(percent, 0, 100);// LIMIT THE PERCENT VARIABLE AS 0 MIN AND 100 MAX

if (duty < minefect)
       {
        noTone (13);    //TEST IF THE PERCENT OF THE DIGITAL POT LESS THEN 5%, IF TRUE TURN OFF THE PULSE OF THE DRIVER
          if (braking != 0)                 //ROUTINE TO BRAKE THE STEPPER
            {digitalWrite (33, HIGH);       // SET DIGITAL PIN 33 HOLD AS HIGHT TO BRAKE THE STEPPER
             digitalWrite(inc, LOW);        // SET DECREMNT MODE TO DIGITAL POT
             tone (resist, 1000, 20);       //SEND 1KHZ TO DIGITAL POT IN ORDER TO MAKE IT ZERO PERCENT
             noTone (resist);               //TO MAKE SURE THE PULSES TO DIGITAL POT ARE STOPPED
             percent = 0;                   //RESET VALUE OF PERCENTAGE
             pulses = 0;                    //RESET COUNTER
             braking = 0;                   // RESET MEMORY
             digitalWrite (33,LOW);         //RELEASE BRAKE 
         }

  }
  
else
{  if (percent > duty)                  //TEST DIFFERENCE BETWEEN PERCENT AND DUTY, AND TAKE THE DECISION WHETHER INCREMENT OR DECREMENT
        { percent --;                   //DECREMENT PERCENT VALUE 
          pulses --;                    //DECREMENT VALUE OF PULSES SO DECRESES THE DRIVER SPEED
          digitalWrite(inc, LOW);       // SET DECREMNT MODE TO DIGITAL POT
          digitalWrite(resist, HIGH);   // SET HIGHT TO PIN 30, TO PULSE AND DECREMENT THE DIGITAL POT
          digitalWrite(resist, LOW);    // SET LOW TO PIN 30 AND FINISH THE PULSE TO DECREMENT
          braking = 1;                  //REGISTER TO INFORM THE WHEEL IS IN MOVIMENT, AND NEEDS TO BREAK AFTER
           }
         
   if (percent < duty) 
                { percent ++;                    //INCREMENT THE VARIABLE PERCENT  TO KNOW THE PERCENT TARGET OF TORQUE
                 pulses ++;                     //INCREMENT VALUE OF PULSES SO INCRESES THE DRIVER SPEED
                 digitalWrite(inc, HIGH);       // SET INCREMNT MODE TO DIGITAL POT
                 digitalWrite(resist, HIGH);   // SET HIGHT TO PIN 30, TO PULSE AND INCREMENT THE DIGITAL POT
                 digitalWrite(resist, LOW);    // SET LOW TO PIN 30 AND FINISH THE PULSE TO INCREMENT                 
                 braking = 1;                 //REGISTER TO INFORM THE WHEEL IS IN MOVIMENT, AND NEEDS TO BREAK AFTER
                      } 
                      
          tone (13, pulses, 5);     //SET A SPEED RELATIVE TO DUTY PERCENTAGE FOR 5 MILE SECS
          }
                 
 Serial.println();                     // serial monitor output
 Serial.println(duty);

 
  }

