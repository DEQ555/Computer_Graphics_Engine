
#include "enginerender.h"

#include <stdlib.h>
#include <stdio.h>

#define SS_ANCHO 640
#define SS_ALTO  480

typedef char _s8;
typedef short _s16;
typedef int _s32;
typedef unsigned char _u8;
typedef unsigned short _u16;
typedef unsigned int _u32;

struct GUB_FVM3D_HEAD{
	_u8       Modo; // En cada bit en binario representara algun modo
	_u32 Num_Tam_V; // Numero de multiplicado Vertices
	_u32 Num_Tam_T; // Numero de multiplicado Vertices Textura
	_u32     Num_V; // Numero de Vertices
	_u32     Num_T; // Numero de Vertices Textura
	_u32     Num_F; // Numero de Faces
	_u32   Num_TEX; // Numero de Texturas
};

struct GUB_FVM3D_OBJECT{
	// Estructura de Cabesera FVM
	struct GUB_FVM3D_HEAD FVM_HEAD;
	_u32 *TEX; // Buffer Texturas
	_s32  *V_; // Buffer Vertices
	_u32  *T_; // Buffer Vertices Textura
	_u32  *F_; // Buffer Faces
};

int _GUB_LOAD_FVM_( struct GUB_FVM3D_OBJECT *X, const char Archivo[] ){
	FILE *f;
	f = fopen( Archivo, "rb" );
	fread( &X->FVM_HEAD, sizeof(struct GUB_FVM3D_HEAD), 1, f );

	X->TEX = (unsigned int*)malloc( (sizeof(unsigned int) * X->FVM_HEAD.Num_Tam_T * X->FVM_HEAD.Num_Tam_T) * X->FVM_HEAD.Num_TEX );
	X->V_ = (int*)malloc( sizeof(int) * X->FVM_HEAD.Num_V * 3);
	X->T_ = (unsigned int*)malloc( sizeof(unsigned int) * X->FVM_HEAD.Num_T * 2 );
	X->F_ = (unsigned int*)malloc( sizeof(unsigned int) * X->FVM_HEAD.Num_F * 8 );

	fread( X->TEX, (sizeof(unsigned int) * X->FVM_HEAD.Num_Tam_T * X->FVM_HEAD.Num_Tam_T) * X->FVM_HEAD.Num_TEX, 1, f );
	fread( X->V_, sizeof(int) * X->FVM_HEAD.Num_V * 3, 1, f );
	fread( X->T_, sizeof(unsigned int) * X->FVM_HEAD.Num_T * 2, 1, f );
	fread( X->F_, sizeof(unsigned int) * X->FVM_HEAD.Num_F * 8, 1, f );
	fclose(f);
	f=NULL;
	return 0;
}

int _GUB_FREE_FVM_( struct GUB_FVM3D_OBJECT *X ){
	// if(!X)return 1;
	free(X->V_),  X->V_  = NULL;
	free(X->T_),  X->T_  = NULL;
	free(X->F_),  X->F_  = NULL;
	free(X->TEX), X->TEX = NULL;
	X->FVM_HEAD.Modo = X->FVM_HEAD.Num_Tam_V = X->FVM_HEAD.Num_Tam_T = X->FVM_HEAD.Num_V = X->FVM_HEAD.Num_T = X->FVM_HEAD.Num_F = X->FVM_HEAD.Num_TEX = 0;
	return 0;
}

void _GUB_READ_FVM_( struct GUB_FVM3D_OBJECT *X ){
	printf("####################################################\n");
	printf("Mode          : %i\n", X->FVM_HEAD.Modo );
	printf("Mult V        : %i\n", X->FVM_HEAD.Num_Tam_V );
	printf("Mult T        : %i\n", X->FVM_HEAD.Num_Tam_T );
	printf("Vertex        : %i\n", X->FVM_HEAD.Num_V );
	printf("Vertex Texture: %i\n", X->FVM_HEAD.Num_T );
	printf("Faces         : %i\n", X->FVM_HEAD.Num_F );
	printf("Textures      : %i\n", X->FVM_HEAD.Num_TEX );
	printf("####################################################\n");
}

int main(void){

	CrearBuffer( SS_ANCHO, SS_ALTO );

	struct GUB_FVM3D_OBJECT Modelo3D;

	_GUB_LOAD_FVM_(&Modelo3D,"Cube.fvm");
	// _GUB_LOAD_FVM_(&Modelo3D,"Shambler.fvm");
	// _GUB_LOAD_FVM_(&Modelo3D,"soldier.fvm");
	_GUB_READ_FVM_(&Modelo3D);

	Imagen2D( 0,0, Modelo3D.TEX, Modelo3D.FVM_HEAD.Num_Tam_T, Modelo3D.FVM_HEAD.Num_Tam_T );

	_GUB_FREE_FVM_(&Modelo3D);

	GuardarBufferV( "VBuff.bmp" );

	CerrarBuffer();

	return 0;
}