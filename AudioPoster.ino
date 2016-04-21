              
              
                /* LUISTERPOSTER CODE  
Luisterposter is een project van Bibliotheekservice Fryslan, gerealiseerd door Studio Marleen Andela - 2015
Maakt gebruik van de Adafruit VS1053 Breakout. Librairy voor deze breakout is hier te downloaden: https://github.com/adafruit/Adafruit_VS1053_Library/archive/master.zip

*/

//-------------ADAFRUIT LIBRARY STUFF ------------------//
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
    
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);
//-----------------------------------------------------//

int trackNum;
float trackFloat;// the current state of the output pin
//mp3 files: 
char* myTracks[]={"track001.mp3", "track002.mp3", "track003.mp3", "track004.mp3", "track005.mp3" };

////
int knop;


void setup() {
  Serial.begin(9600);
  

  if (! musicPlayer.begin()) { 
    while (1);
  
    // Debugging: 
    Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
  }
  
  Serial.println(F("VS1053 found"));
  
  //Debugging:
  //  musicPlayer.sineTest(0x44, 500);    // Make a tone to indicate VS1053 is working
 
  if (!SD.begin(CARDCS)) {
    //Debugging: 
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
    }
    
    // Debugging: 
    Serial.println("SD OK!");
  
    // Set volume for left, right channels. lower numbers == louder volume!
    musicPlayer.setVolume(255,255);

   if (! musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT)){
   Serial.println(F("DREQ pin is not an interrupt pin"));
   }
  }

void(* resetFunc) (void) = 0;//declare reset function at address 0

void loop() {  
  Serial.println("de loop wordt gestart"); 
   if (! musicPlayer.startPlayingFile(myTracks[trackNum])) {  
      Serial.println("Could not open file3");
      resetFunc();
      Serial.println("skipped the while loop");
    }
        
    Serial.println("Started playing track:");
    Serial.println(myTracks[trackNum]);
      
    while (musicPlayer.playingMusic) {
      Serial.println("we zitten in while"); 
      int knopBuff = trackNum; 
      knop = analogRead(A2);
      Serial.println(knop);
      trackFloat = map(knop, 1024,0,4,0     );  
      Serial.println(trackFloat);
      trackNum = (int) trackFloat; 
      if ( knopBuff != trackNum){
      Serial.println("Track wordt gewisselt"); 
      break;}

      int volKnop = analogRead(A1);
      Serial.println(volKnop);
      int volume = map(volKnop,0, 1024, 10, 90);
      musicPlayer.setVolume(volume,volume);
  }
//1;
} 



