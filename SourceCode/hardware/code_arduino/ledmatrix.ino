
#include <arduinoFFT.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

#define SAMPLES 64            
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW   
#define MAX_DEVICES  4   
#define CLK_PIN   13  
#define DATA_PIN  11 
#define CS_PIN    10 
#define  xres 32      
#define  yres 8       
int MY_ARRAY[] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};
//int MY_ARRAY[] =  {0, 1, 3, 7, 15, 31, 63, 127, 253};
int MY_MODE_5[] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023}; 
double vReal[SAMPLES];
double vImag[SAMPLES];
char data_avgs[xres];
int yvalue;
int displaycolumn , displayvalue;
int peaks[xres];
const int buttonPin = 6;   
int state = HIGH;             
int previousState = LOW;  
int displaymode = 2;
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    
int pinCS = 10; 
int numberOfHorizontalDisplays = 1;  
int numberOfVerticalDisplays = 4;   
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays); 
String tape = "ARE YOU READY"; 
int wait = 50; 
int spacer = 2; 
int width = 5 + spacer; 
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);   
arduinoFFT FFT = arduinoFFT();    

                                                          
void setup() {
  ADCSRA = 0b11100101;      
  ADMUX = 0b00000000;       
  pinMode(buttonPin, INPUT);
  mx.begin();         
  delay(50);            
  matrix.setIntensity(8);  
  matrix.setRotation(1);  
}
void loop() {
  if (displaymode != 2) {
    // ++ Sampling
    for (int i = 0; i < SAMPLES; i++)
    {
      while (!(ADCSRA & 0x10));       
      ADCSRA = 0b11100101;                 

      
      int value = ADC - 1024;             
      vReal[i] = value;                  
      
      vImag[i] = 0;
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    int step = (SAMPLES / 2) / xres;
    int c = 0;
    for (int i = 0; i < (SAMPLES / 2); i += step)
    {
      data_avgs[c] = 0;
      for (int k = 0 ; k < step ; k++) {
        data_avgs[c] = data_avgs[c] + vReal[i + k];
      }
      data_avgs[c] = data_avgs[c] / step;
      c++;
    }
    
    for (int i = 0; i < xres; i++)
    {
      data_avgs[i] = constrain(data_avgs[i], 0, 40);          
      data_avgs[i] = map(data_avgs[i], 0, 40, 0, yres);       
      yvalue = data_avgs[i];

      peaks[i] = peaks[i] - 1;  
      if (yvalue > peaks[i])
        peaks[i] = yvalue ;
      yvalue = peaks[i];
      displayvalue = MY_ARRAY[yvalue];
      displaycolumn = 31 - i;
      mx.setColumn(displaycolumn, displayvalue);              
    }
  }  
  else chaychu();

  //displayModeChange ();        
}
void displayModeChange() {
  int reading = digitalRead(buttonPin);
  Serial.println(reading);
  if ((reading == HIGH && previousState == LOW)  && millis() - lastDebounceTime > debounceDelay)
  {
    displaymode = 2;
    
    switch (displaymode) {
      case 1:    
        displaymode = 2;
        for (int i = 0 ; i <= 8 ; i++ ) {
          MY_ARRAY[i] = MY_MODE_5[i];
        }
        break;
      case 2:   
        displaymode = 1;
        for (int i = 0 ; i <= 8 ; i++ ) {
          MY_ARRAY[i] = MY_MODE_5[i];
        }
        break;
    }
    lastDebounceTime = millis();
  }
  previousState = reading;
}

void chaychu() 
{
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ )
  {

    matrix.fillScreen(LOW);

    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; 
    while ( x + width - spacer >= 0 && letter >= 0 ) {
      displayModeChange ();

      if ( letter < tape.length() ) {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }

      letter--;
      x -= width;
    }

    matrix.write(); 

    delay(wait);
  }
}
