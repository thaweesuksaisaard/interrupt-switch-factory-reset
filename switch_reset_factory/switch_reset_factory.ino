#define LED1 2
#define LED2 15
#define sw_button 35

uint8_t count = 0;
uint8_t second = 0;

hw_timer_t *timer;
void IRAM_ATTR onTimer()
{
  if(digitalRead(sw_button) == 1)
  {
   timerAlarmDisable(timer);
  }
  else{
    // 1 count equal 1 second
    count++;
    Serial.print("Count = "); Serial.println(count);
    if(count == 5){
      Serial.println("Factory reset");
      ESP.restart();
    }
  }
}


void IRAM_ATTR isr()
{
  count = 0;
  if(digitalRead(sw_button) == 0)
  {
    second = 1;
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, second*1000000, true);
    timerAlarmEnable(timer);     
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start");
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(sw_button, INPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  attachInterrupt(sw_button, isr, FALLING);
 
}

void loop() {
 
}
