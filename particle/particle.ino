/*
 * @description Utils
 */ 
#include "Structures.h"

/*
 * @description Utils
 */ 
#include "Utils.h"

/*
 * @description Utils
 */ 
#include "Colors.h"

int f;
int t;
unsigned long duration = 10;
float percent;

COLOR current;
PINS pins;
TIMER timer;

void setup() {
    current = {0,0,0};
    
    timer = {0,millis(),1000, 0};
    
    /*
     * set pins
     */
    pins = {A7, A5, A4};
    
    /*
     * pin mode
     */    
    pinMode(pins.r, OUTPUT);
    pinMode(pins.g, OUTPUT);
    pinMode(pins.b, OUTPUT);
    
    /*
     * initial write out
     */        
    analogWrite(pins.r, 255);
    analogWrite(pins.g, 255);
    analogWrite(pins.b, 255);
    
    f = 0;
    t = random(10);
}

void loop() {
    timer.now = millis();
    if(timer.now - timer.timestamp >= timer.interval)
    {
        timer.timestamp = timer.now;
        timer.changed = timer.now + duration;
        f = t;
        t = random(10);
        
      char buffer[100];
    
      (String)sprintf(
        buffer,
        "percent:%d timer.now:%d timer.timestamp:%d timer.changed:%d duration:%d",
        percent,
        timer.now,
        timer.timestamp,
        timer.changed,
        duration
      );
    
      //Particle.publish("dump", buffer);         
      Serial.print(buffer);
    };  
    percent = (((float)timer.timestamp-(float)timer.now)/(float)duration);
    paint();
}

void paint()
{
    COLOR from = colors[f];
    COLOR to = colors[t];
    
    current.r = to.r - from.r;
    current.r = to.r - (current.r*percent);
    
    current.g = to.g - from.g;
    current.g = to.g - (current.g*percent);
    
    current.b = to.b - from.b;
    current.b = to.b - (current.b*percent);  
    
    analogWrite(pins.r, current.r);
    analogWrite(pins.g, current.g);    
    analogWrite(pins.b, current.b);
}
