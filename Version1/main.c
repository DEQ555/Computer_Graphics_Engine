
#include "enginerender.h"

#define SS_ANCHO 640
#define SS_ALTO  480

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );

	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}