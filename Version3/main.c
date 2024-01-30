
#include "enginerender.h"

#include <stdlib.h>

#define SS_ANCHO 640
#define SS_ALTO  480

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );


	for (int y = 0; y < SS_ALTO; ++y)
	{
		for (int x = 0; x < SS_ANCHO; ++x)
		{
			int c = ( (x+y) * (y-x) ) | 0xff0000ff;
			Punto( x, y, c );
		}
	}



	for (int i = 0; i < 100; ++i)
	{
		Linea( rand() % SS_ANCHO,rand() % SS_ALTO, rand() % SS_ANCHO,rand() % SS_ALTO, 0xfffff000 );
	}



	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}