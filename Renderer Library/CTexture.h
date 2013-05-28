#ifndef __CTEXTURE_H
#define __CTEXTURE_H

#include <string>
#include "glew\include\GL\glew.h"
#include "glfw\include\GL\glfw.h"


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
    mBPP(0)
  { 
    loadFromDisk(mPath.c_str());
  }


  CTexture(std::string pth) : mPath(pth)
  {
    loadFromDisk(mPath.c_str()); }

  virtual ~CTexture() {}

  std::string getPath() { return mPath;};
  std::string setPath(std::string pa) { mPath = pa; return mPath;};

private:

  bool loadFromDisk(const char * string);

  std::string mPath;

  bool mIsMipMapped;
  bool mIsFlipped;
  bool mIsClamped;

  //Enums for convenienve
  ETexFilterType mTextureFilter;
  ETexFormatType mTexFormat; 
  ETexType mTexUsageType;
  
  GLFWimage mImageRaw; //info and pointer to image
  int mBPP; // Image Color Depth In Bits Per Pixel

};


#endif