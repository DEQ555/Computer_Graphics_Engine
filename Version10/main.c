
#include "enginerender.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define SS_ANCHO 640
#define SS_ALTO  480
#define SM_ANCHO (SS_ANCHO>>1)
#define SM_ALTO  (SS_ALTO>>1)

#include "Vertex.h"
#include "RasterizeObject.h"


int main(void){

	const int fov = 9;
	CrearBuffer( SS_ANCHO, SS_ALTO );

	SetCameraPos( 0,0,9000 );


	// Scale
	for (unsigned int i = 0; i < CubeVerticesLen*3; ++i)
		CubeVertices[i] *= 9;


	VWorld = (int*)malloc( CubeVerticesLen * 3 * sizeof(int) );
	RasterModel( CubeVertices, VWorld, fov );
	free(VWorld),VWorld=NULL;


	printf("DRAW'S TRIANGLES: %i\n", DrawTriangleCount );
	getch();



	GuardarBufferV( "VBuff.bmp" );
	CerrarBuffer();

	return 0;
}