//--------------------Libraries
#include <LiquidCrystal.h>
#include <EEPROM.h> //note that atmega328p has 1kb EEPROM

//--------------------Pin Definition

//----Analog
#define OpticalBridge A0
#define ResistorBridge A1

//----Digital
#define WritePin1 7
#define WritePin2 8
#define Display 3
#define TestBtn 9
#define ControlBtn 10

//----Display Pins
//#define RS 12 - Register Select Pin, used to determine where we are writing in the LCD memory: 
//data register which is diplayed on screen OR instruction register which says what to do next
//#define EN 11 - Enable Pin allowing registry writing
//#define D4 5 \
//#define D5 4  - Data pins for writing/reading information from the LCD
//#define D6 3  /
//#define D7 2 /
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;


//--------------------Variable Definition
/**
Need to divide by 4 because analog inputs range from 0 to 1023 and each byte of the EEPROM can only hold a value from 0 to 255.
**/

float OpticalReading = 0;
float OpticalMax = 0;
float OpticalMin = 0;

float ResistanceReading = 0;
float ResistanceMax = 0;
float ResistanceMin = 0;

LiquidCrystal Display(rs, en, d4, d5, d6, d7); //the LCD variable, created specially to control the chipset on the Liquid Crystal 16x2 Display

int MemoryAddr = 0; //used to communicate which byte is being written inside EEPROM

//--------------------Analog Optical Measurement
void OpticalReading()
{
  OpticalReading = AnalogRead(OpticalBridge);//A0 pin
      if (OpticalReading > OpticalMax)
      OpticalMax = OpticalReading;

      if (OpticalReading < OpticalMin)
      OpticalMin = OpticalReading;      
}

//--------------------Analog Resistance Measurement
void ResistanceReading()
{
    ResistanceReading = AnalogRead(ResistorBridge);//A1 pin
      if (ResistanceReading > ResistanceMax)
      ResistanceMax = ResistanceReading;

    if (ResistanceReading < ResistanceMin)
      ResistanceMin = ResistanceReading;
}

//--------------------Optical Measurement Normalization
void OpticalNormalize()
{
    //CHECK HIGH AND LOW VALUES, NOT 0 AND 1
    OpticalReading = map(OpticalReading, OpticalMin, OpticalMax, 0, 1);


    //CHECK HIGH AND LOW VALUES, NOT 0 AND 1
    //In case the sensor value is outside the range seen during calibration
    OpticalReading] = constrain(OpticalReading, 0, 1);  
}

//--------------------Resistance Measurement Normalization
void ResistanceNormalize()
{
    //CHECK HIGH AND LOW VALUES, NOT 0 AND 1
    ResistanceReading = map(ResistanceReading, ResistanceMin, ResistanceMax, 0, 1);


    //CHECK HIGH AND LOW VALUES, NOT 0 AND 1
    //In case the sensor value is outside the range seen during calibration
    ResistanceReading] = constrain(ResistanceReading, 0, 1);  
}

//--------------------Menu Initialization
void MenuInit()
{
  int counter = 0; //
  int tester = 0; // for determining if there is something in the EEPROM
  
  //----Initialize the variable of type LiquidCrystal with 16 columbs and 2 rows (a 16x2 display)  
  Display.begin(16,2);

  //----Cleans display and positions cursor at (0,0) (top-left corner)
  Display.clear();

  //----Boot
  Display.print("Welcome to"); //start writing at location 0,0
  Display.setCursor(0,1); //after writing the first line move cursor to 0,1 (lower row)
  Display.print("Salutare vultus");
  delay(200);

  //----EEPROM Memory Check
  Display.clear(); //clean and reset to 0,0
  Display.print("Memory Check:");
  Display.setCursor(0,1);

  if (tester == 1)
  {
    Display.print("Check Complete");
  }
  
  else
  {
    Display.print("Check Failed");
  }
}


//--------------------EEPROM Check
void MemoryCheck()
{
  
}

//--------------------EEPROM Storage
void MemoryStore(float A, float B) //must adjust if amount of inputs are changes
{

}

//--------------------EEPROM Compare Test Results
void TestCompare(float A,float B)//Must compare results in current variables and memory
{
  float Result;

  return Result;
}


//--------------------Pin and Variable Initilization
void setup() 
{
  //----Analog
  pinMode(OpticalBridge, INPUT);
  pinMode(ResistorBridge, INPUT);
  
  //----Digital
  pinMode(WritePin1, OUTPUT);
  pinMode(WritePin2, OUTPUT);
  pinMode(Display, OUTPUT);

  pinMode(TestBtn,INPUT);
  pinMode(ControlBtn,INPUT);

  //Inital levels
  digitalWrite(WritePin1, LOW);
  digitalWrite(WritePin2, LOW);

  //Initiate Display
  MenuInit();
}

//--------------------Main Code Loop
void loop() 
{

    println("Select action:");
    println("1.Control");
    println("2.Test");
    //replace with lcd.setCursor(0,0);
    //lcd.print("L)Control Sample);
    //lcd.setCursor(0,1);
    //lcd.print("R)Test Sample);
    //
    do
    {
    digitalRead(SignalBtn); 
    digitalRead(ControlBtn); 
    }while(TestBtn == LOW || ControlBtn == LOW)
    
    //ReadingSequence
    OpticalReading();
    ResistanceReading();

    //AnalogNormalization
    OpticalNormalize();
    ResistanceNormalize();
}
