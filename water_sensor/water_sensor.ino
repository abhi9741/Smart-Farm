int WET= 16; // Wet Indicator at Digital pin D0

int DRY= 2;  // Dry Indicator at Digital pin D4
int sense_Pin = 0; // sensor input at Analog pin A0

int value = 0;
void setup() {
   Serial.begin(9600);
   pinMode(WET, OUTPUT);
   pinMode(DRY, OUTPUT);
   delay(2000);
}

void loop() {

   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);

        if(value<50)
        {
            digitalWrite(WET, HIGH);
            digitalWrite(DRY, LOW);
        }
       else
       {
           digitalWrite(DRY,HIGH);
            digitalWrite(WET,LOW);
       }

       delay(1000);

      

       
}
