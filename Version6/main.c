
#include "enginerender.h"
#include <stdlib.h>
#include <stdio.h>

#define SS_ANCHO 640
#define SS_ALTO  480

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );

	ImageRender IMAGEN2D;

	ImageRenderLoad( &IMAGEN2D, "Cube.mcd");
	ImageRenderDraw( &IMAGEN2D, 0,0 );
	ImageRenderFree( &IMAGEN2D );

	ImageRenderLoad( &IMAGEN2D, "Shambler.mcd");
	ImageRenderDraw( &IMAGEN2D, 40,90 );
	ImageRenderFree( &IMAGEN2D );

	// ImageRenderLoad( &IMAGEN2D, "Soldier.mcd");
	// ImageRenderDraw( &IMAGEN2D, 40,90 );
	// ImageRenderFree( &IMAGEN2D );

	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}