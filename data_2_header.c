#include "raylib.h"

int main ()
{
	Image img = LoadImage("assets/Asset.png");
	ExportImageAsCode(img, "image_data.h");
	UnloadImage(img);
   
     
 

	Wave eat =LoadWave("assets/eat.ogg");
	ExportWaveAsCode(eat, "eat_sound_data.h"); 

	Wave fail =LoadWave("assets/fail.ogg");
	ExportWaveAsCode(fail, "fail_sound_data.h"); 
}