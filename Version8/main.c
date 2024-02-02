
#include "enginerender.h"
#include <stdlib.h>
#include <stdio.h>

#define SS_ANCHO 640
#define SS_ALTO  480

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );

	ImageRender IMAGEN2D;

	ImageRenderLoad( &IMAGEN2D, "Soldier.mcd");

	for (int i = 0; i < 100; ++i)
	{
		LineaTexture( rand()%SS_ANCHO,rand()%SS_ALTO, rand()%SS_ANCHO, rand()%SS_ALTO,  rand()%IMAGEN2D.w, rand()%IMAGEN2D.h, rand()%IMAGEN2D.w, rand()%IMAGEN2D.h, &IMAGEN2D );
	}

	ImageRenderFree( &IMAGEN2D );

	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}