#ifndef __CTEXTURE_H
#define __CTEXTURE_H

#include <string>
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_opengl.h"


static const char *DEFAULT_ASSET_TEXTURE = "C:/Users/dragonerdriftr/Documents/Pet/defaultNoAsset.bmp";

class CTexture 
{

  enum ETexType 
  {
    DIFFUSE, NORMAL, SPECULAR, OPACITY, ALPHA
  };

  enum ETexFormatType 
  {
    UNKNOWN, BMP, GIF, JPG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV
  };

  enum ETexFilterType 
  {
    NOFILTER, BILINEAR, TRILINEAR
  };

public:
  CTexture()  
    : mPath(DEFAULT_ASSET_TEXTURE),
    mIsMipMapped(false),
    mIsFlipped(false),
    mIsClamped(true),
    mTextureFilter(NOFILTER),
    mTexUsageType(DIFFUSE),
    mWidth(0),
    mHeight(0),
    mType(GL_NONE),
    mBPP(0),
    mSDLsurf(NULL)
  { 
    mSDLsurf = loadFromString(mPath.c_str());
  }

  CTexture(std::string pth) : mPath(pth){ mSDLsurf = loadFromString(mPath.c_str()); }

  virtual ~CTexture() {SDL_FreeSurface(mSDLsurf);}

  std::string getPath() { return mPath;};
  std::string setPath(std::string pa) { mPath = pa; return mPath;};
  SDL_Surface* getSDL_Surface() { return mSDLsurf;}

private:

  SDL_Surface* loadFromString(const char * string);

  std::string mPath;
  SDL_Surface* mSDLsurf;

  bool mIsMipMapped;
  bool mIsFlipped;
  bool mIsClamped;

  //Enums for convenienve
  ETexFilterType mTextureFilter;
  ETexFormatType mTexFormat; 
  ETexType mTexUsageType;

  int mTextureID; // Texture ID Used To Select A Texture
  int mWidth; // Image Width
  int mHeight; // Image Height
  int mType; // Image Type (GL_RGB, GL_RGBA)
  int mBPP; // Image Color Depth In Bits Per Pixel

};


#endif