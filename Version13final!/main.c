
#include "enginerender.h"
#include <conio.h>
#include <math.h>
#include <stdio.h>

#define SS_ANCHO 640<<1
#define SS_ALTO  480<<1
#define SM_ANCHO (SS_ANCHO>>1)
#define SM_ALTO  (SS_ALTO>>1)

#include "vertex.h"
#include "ScanLine.h"
#include "RasterizeObject.h"


int main(void){

	const int fov = 9;
	CrearBuffer( SS_ANCHO, SS_ALTO );

	// Scale
	for (unsigned int i = 0; i < CubeVerticesLen*3; ++i) CubeVertices[i] *= 2;

	InitScan( SS_ALTO );

	VWorld = (int*)malloc( CubeVerticesLen * 3 * sizeof(int) );

	SetCameraPos( 0,0,9000 );
	RasterModel( CubeVertices, VWorld, fov, 0xff0000ff );

	SetCameraPos( -4900,-1800,9090 );
	RasterModel( CubeVertices, VWorld, fov, 0xff00ffff );
	
	free(VWorld),VWorld=NULL;

	FreeScan();


	printf("DRAW'S TRIANGLES: %i\n", DrawTriangleCount );
	getch();



	GuardarBufferV( "VBuff.bmp" );
	GuardarBufferZ( "ZBuff.bmp" );
	CerrarBuffer();

	return 0;
}