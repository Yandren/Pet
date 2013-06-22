#ifndef __CTEXTURE_H
#define __CTEXTURE_H

#include <string>

class GLFWImage;

static const char *DEFAULT_ASSET_TEXTURE = "C:/Users/dragonerdriftr/Documents/Pet/Assets/Test/Texture/test.dds";

class CTexture 
{

  enum ETexType 
  {
    DIFFUSE, NORMAL, SPECULAR, OPACITY, ALPHA
  };

  enum ETexFormatType 
  {
    UNKNOWN, BMP, DDS, GIF, JPG, LBM, PCX, PNG, PNM, TGA, TIFF, XCF, XPM, XV
  };

  enum ETexFilterType 
  {
    NOFILTER, BILINEAR, TRILINEAR
  };

public:

  //methods
  CTexture()  
    : mPath(DEFAULT_ASSET_TEXTURE),
    mIsMipMapped(false),
    mIsFlipped(false),
    mIsClamped(true),
    mTextureFilter(NOFILTER),
    mTexUsageType(DIFFUSE),
    mBPP(0)
  { 
    //parse out FormatType here

    loadFromDisk(mPath.c_str());
  }


  CTexture(std::string pth) : mPath(pth)
  {
    //parse out FormatType here, call for the correct loader
    //BREAKTHIS
    loadFromDisk(mPath.c_str()); 
  }

  virtual ~CTexture() {}

  std::string getPath() { return mPath;};
  std::string setPath(std::string pa) { mPath = pa; return mPath;};

private:

  //methods
  bool loadFromDisk(const char * path);

  //template this stufffff
  bool loadDDS(const char * path);
  bool loadTGA(const char * path);


  //members
  std::string mPath;
  bool mIsMipMapped;
  bool mIsFlipped;
  bool mIsClamped;

  //Enums for convenience
  ETexFilterType mTextureFilter;
  ETexFormatType mTexFormat; 
  ETexType mTexUsageType;

  //GLFWimage mImageRaw; //info and pointer to image
  int mBPP; // Image Color Depth In Bits Per Pixel

};


#endif