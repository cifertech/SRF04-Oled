#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define CommonSenseMetricSystem 


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

const int trigPin = D6;
const int echoPin = D5;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  #ifdef CommonSenseMetricSystem
  float distance = duration*0.034/2;
  #endif
  #ifdef ImperialNonsenseSystem
  float distance = (duration/2) / 73.914;
  #endif
  
  return distance;
}
void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  display.clearDisplay();
}

void loop(){
  display.display();
  display.clearDisplay();
  display.setCursor(10,20);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println(distance());
  display.setCursor(90,20);
  display.setTextSize(3);
  
  display.println("cm");
  
  delay(5);
}
