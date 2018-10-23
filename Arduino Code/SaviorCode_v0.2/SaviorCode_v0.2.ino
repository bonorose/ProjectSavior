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

//----Dispalay Pins

//--------------------Variable Definition
float OpticalReading = 0;
float OpticalMax = 0;
float OpticalMin = 0;

float ResistanceReading = 0;
float ResistanceMax = 0;
float ResistanceMin = 0;

//--------------------Analog Optical Measurement
void OpticalReading()
{
  OpticalReading = AnalogRead(ReadPin1);
      if (OpticalReading > OpticalMax)
      OpticalMax = OpticalReading;

      if (OpticalReading < OpticalMin)
      OpticalMin = OpticalReading;      
}

//--------------------Analog Resistance Measurement
void ResistanceReading()
{
    ResistanceReading = AnalogRead(ReadPin2);
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
