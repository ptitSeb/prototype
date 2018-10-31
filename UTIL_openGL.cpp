#include "UTIL_openGL.h"
unsigned int textureMem=0;
namespace UTIL_GL
{
//================================================================================================//
									/***************
									** 2D helpers **
									****************/
//================================================================================================//
	namespace GL2D
	{
		void SetOrtho(float w, float h)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glFrustum(0,w,h,0,1,3);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0,0,-2);
			glScalef(2,2,2);
		}
		void DrawQuad(float sx, float sy, float ex, float ey)
		{
			glBegin(GL_QUADS);
			glVertex2f(sx,sy);
			glVertex2f(ex,sy);
			glVertex2f(ex,ey);
			glVertex2f(sx,ey);
			glEnd();
		}
		void DrawTextureQuad(float sx, float sy, float ex, float ey)
		{
			glBegin(GL_QUADS);
			glTexCoord2f(0,1);	glVertex2f(sx,sy);
			glTexCoord2f(1,1);	glVertex2f(ex,sy);
			glTexCoord2f(1,0);	glVertex2f(ex,ey);
			glTexCoord2f(0,0);	glVertex2f(sx,ey);
			glEnd();
		}
		void DrawWireBox(float sx, float sy, float ex, float ey)
		{
			glBegin(GL_LINE_LOOP);
			glVertex2f(sx,sy);
			glVertex2f(ex,sy);
			glVertex2f(ex,ey);
			glVertex2f(sx,ey);
			glEnd();
		}
	}
//================================================================================================//
									/************************
									** texture enviroment **
									************************/
//================================================================================================//
	void TextureWrap(const unsigned int s, const unsigned int t)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
	}
	void TextureFilter(const unsigned int min, const unsigned int mag)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}
//================================================================================================//
									/*******************
									** image loading **
									*******************/
//================================================================================================//
	namespace Image
	{

		GLuint LoadImage(std::string name)
		{
			unsigned int width, height;
			return LoadImage(name, width, height);
		}
		GLuint LoadImage(std::string name, unsigned int& width, unsigned int& height)
		{
			unsigned int  bpp;
			unsigned char* data = LoadImageData(name, width, height, bpp);
			if(!data) {
				return 0;
			}

			GLuint ID;
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
			switch(bpp)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
				break;
			default:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
				break;
			}

			stbi_image_free(data);

			return ID;
		}
		GLuint LoadImage(std::string name, const int min, const int mag, const int wrapx, const int wrapy)
		{
			unsigned int  width,height,bpp;
			unsigned char* data = LoadImageData(name.c_str(), width, height, bpp);
			if(!data) {
				return 0;
			}

			unsigned int ID=0;
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1,&ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			TextureFilter(min,mag);
			TextureWrap(wrapx,wrapy);
			switch(bpp)
			{
			case 3:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
				break;
			default:
				glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
				break;
			}
			glDisable(GL_TEXTURE_2D);
//printf("Loadimage \"%s\" %ix%ix%i\n", name.c_str(), width, height, bpp);
			stbi_image_free(data);
			return ID;
		}
		unsigned char*  LoadImageData(std::string name, unsigned int& width, unsigned int& height, unsigned int& bpp)
		{
			int x,y,n;
			unsigned char* data = stbi_load(name.c_str(), &x, &y, &n, 0);
			if(!data) {
				string str = "Failed to load image: " + name + "!\n";
				gLog.OutPut(str);
				return 0;
			}
			textureMem += (x*y*4);
			string str = "Image Loaded: " + name + "\n";
			gLog.OutPut(str);

			width = x;
			height = y;
			bpp = n;

			return data;
		}
	}

//================================================================================================//
									/***************
									 ** shortcuts **
									 ***************/
//================================================================================================//
	void BindTexture(const unsigned int type, unsigned int id)
	{
		glEnable(type);
		glBindTexture(type,id);
	}
	void SetBlend(const unsigned int src, const unsigned int dst)
	{
		glEnable(GL_BLEND);
		glBlendFunc(src,dst);
	}
	void AlphaTest(const unsigned int func, float alpha)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(func,alpha);
	}
	void DepthTest(const unsigned int func)
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(func);
	}
	void StencilTest(const unsigned int func, int ref, unsigned int mask)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(func,ref,mask);
	}
#ifdef EXTENSION_SUPPORT_1_1 
	void BindMultiTexture(const unsigned int channel, unsigned int id)
	{
		glActiveTextureARB(channel);
		glBindTexture(channel, id);
	}
#endif
}

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_JPEG
//#define STBI_NO_PNG
#define STBI_NO_BMP
//#define STBI_NO_PSD
#define STBI_NO_TGA
#define STBI_NO_GIF
#define STBI_NO_HDR
#define STBI_NO_PIC
#define STBI_NO_PNM
#include "stb_image.h"