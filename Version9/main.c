
#include "enginerender.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define SS_ANCHO 640
#define SS_ALTO  480
#define SM_ANCHO (SS_ANCHO>>1)
#define SM_ALTO  (SS_ALTO>>1)



typedef struct {int x,y,z;}Vector3D;

typedef struct{int a,b,c,d;}Triangle;

#include "Vertex.h"

#define __AREA(A,B,C) (((C.x) - (A.x)) * ((B.y) - (A.y)) - ((C.y) - (A.y)) * ((B.x) - (A.x)))


const int TriangleWire( Vector3D A, Vector3D B, Vector3D C, int color ){

	if(__AREA(A,B,C)>=0)return 0;
	Linea( A.x,A.y, B.x,B.y, color );
	Linea( B.x,B.y, C.x,C.y, color );
	Linea( C.x,C.y, A.x,A.y, color );
	return 1;
}


Vector3D *VWorld = NULL;

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );

	VWorld = (Vector3D*)malloc( CubeVerticesLen * sizeof(Vector3D) );

	int CameraX = 0;
	int CameraY = 0;
	int CameraZ = 9000;
	int fov = 9;
	int shift = 0;

	int ffac = (1 << (fov + 12));
	shift = fov - 8;

	for (int i = 0; i < CubeVerticesLen; ++i)
	{

		CubeVertices[i].x += CameraX;
		CubeVertices[i].y += CameraY;
		CubeVertices[i].z += CameraZ;

		fov = ffac / CubeVertices[i].z;

		VWorld[i].x = ( (CubeVertices[i].x * fov + (1 << 11)) >> 12 ) + SM_ANCHO;
		VWorld[i].y = SM_ALTO - ( (CubeVertices[i].y * fov + (1 << 11)) >> 12 );
		VWorld[i].z = fov >> shift;

	}

	Vector3D A,B,C;
	unsigned int DrawTriangleCount = 0;

	for (int i = 0; i < CubeFacesLen; ++i)
	{
		A = VWorld[CubeFaces[ i ].a];
		B = VWorld[CubeFaces[ i ].b];
		C = VWorld[CubeFaces[ i ].c];
		DrawTriangleCount+=TriangleWire(A,B,C,0xff0000ff);
	}

	free(VWorld),VWorld=NULL;

	printf("DRAW'S TRIANGLES: %i\n", DrawTriangleCount );

	getch();

	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}