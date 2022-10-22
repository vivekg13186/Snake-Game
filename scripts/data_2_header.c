#include "raylib.h"

int main ()
{
	Image img = LoadImage("../assets/Asset.png");
	ExportImageAsCode(img, "../src/image_data.h");
	UnloadImage(img);
   
     
 

	Wave eat =LoadWave("../assets/eat.ogg");
	ExportWaveAsCode(eat, "../src/eat_sound_data.h"); 

	Wave fail =LoadWave("../assets/fail.ogg");
	ExportWaveAsCode(fail, "../src/fail_sound_data.h"); 
}