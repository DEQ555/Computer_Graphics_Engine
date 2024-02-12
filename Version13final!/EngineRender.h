#ifndef __TarjetaVideo_H__
#define __TarjetaVideo_H__
#ifdef __cplusplus
extern "C"{
#endif

void CrearBuffer( const int w, const int h );
void CerrarBuffer( void );

void GuardarBufferV( const char Name[] );
void GuardarBufferZ( const char Name[] );


// Apartado de ediciones.
typedef struct{ unsigned char ARGB[4]; }RGBA_;

RGBA_ _RGBA_(unsigned char R, unsigned char G, unsigned char B, unsigned char A );

void Punto( int x, int y, int c );

void Depth( int x, int y, int z );

int GetDepth( int x, int y );

void Linea( int x0, int y0, int x1, int y1, int c );

void LineaLerp( int x0, int y0, int x1, int y1, RGBA_ c0, RGBA_ c1 );

void Imagen2D( int x, int y, void *data, int w, int h );

typedef struct{
	int w,h;
	int* d;
}ImageRender;

void ImageRenderLoad( ImageRender *X, const char Name[] );

void ImageRenderFree( ImageRender *X );

void ImageRenderDraw( ImageRender *X, int x0, int y0 );

int  ImageRenderGetP( ImageRender *X, int x0, int y0 );

void ImageRenderSetP( ImageRender *X, int x0, int y0, int c );

void ImageRenderDrawRCT( ImageRender *X, int x0, int y0, int x1, int y1 );

void LineaTexture( int x0, int y0, int x1, int y1, int u0, int v0, int u1, int v1, ImageRender *X );

typedef struct{int x, y, z;} Vector3D;

typedef struct{int a, b, c;} Triangle;

#ifdef __cplusplus
}
#endif
#endif