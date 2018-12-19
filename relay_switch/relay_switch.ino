int in = A3;
int out =7;
int val=0;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
   Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(out,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
 //Serial.print("hello world");
 val = analogRead(in);
 if (val>200){
   digitalWrite(out,1);
  }
 else {
   digitalWrite(out,0);
  }
}
