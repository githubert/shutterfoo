// I/O-Pin for shutter release
int shutter = 13;
// I/O-Pin for valve release
int valve = 12;
// time between opening and closing the solenoid valve 
// to create a single drop
int drop_time_len = 35;
// serial command
int cmd = 0;
// initial delay
int initial_delay = 3000;

int next_drop = 85;
int collision = 50;

void setup() {                
  pinMode(shutter, OUTPUT);
  pinMode(valve, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
start:
  delay(initial_delay + 1000);
  
  Serial.print("Next Drop ");
  Serial.print(next_drop);
  Serial.print(", Collision ");
  Serial.print(collision);
  Serial.println();

  
  if(Serial.available() > 0) {
    cmd = Serial.read();
    
    switch(cmd) {
          case '.':
            Serial.println("Stopped.");
            
            while(true) {
              delay(100);
              if(Serial.available() > 0) {
                cmd = Serial.read();
                goto start;
              }
            }
            break;
          case 'd':
            initial_delay = Serial.parseInt();
            goto start;
            break;
          case 'n':
            next_drop = Serial.parseInt();
            goto start;
            break;
          case 'c':
            collision = Serial.parseInt();
            goto start;
            break;
    }
  }

  // First drop
  digitalWrite(valve, HIGH);
  delay(drop_time_len);
  digitalWrite(valve, LOW);

  // wait this long before next drop
  delay(next_drop);

  // Second drop
  digitalWrite(valve, HIGH);
  delay(drop_time_len);
  digitalWrite(valve, LOW);

  // wait this long for collision
  delay(collision);

  // take picture
  digitalWrite(shutter, HIGH);
  delay(100);
  digitalWrite(shutter, LOW);
}
