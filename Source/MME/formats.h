// formats.h header file

#ifndef _FORMATS_H_
#define _FORMATS_H_
#include<d3dx9.h>

namespace MME {

struct FMTINFO
{
    D3DFORMAT fmt;
    const char* strName;
    //const char* strType;
    //int   nBitsPerTexel;
    //BOOL  bHasAlpha;
    //UINT  idsFmtDesc;
};

static const char* TYPE_UNSIGNED = "Unsigned";
static const char* TYPE_SIGNED   = "Signed";
static const char* TYPE_MIXED    = "Mixed";
static const char* TYPE_FOUR_CC  = "Four CC";
static const char* TYPE_FLOAT    = "Floating-Point";
static const char* TYPE_IEEE     = "IEEE Floating-Point";

const FMTINFO fmtInfoArray[] = 
{
    D3DFMT_A4L4,            "A4L4",           //TYPE_UNSIGNED,   8,     TRUE,   //IDS_FMTDESC_A4L4,
    D3DFMT_A8,              "A8",             //TYPE_UNSIGNED,   8,     TRUE,   //IDS_FMTDESC_A8,
    D3DFMT_L8,              "L8",             //TYPE_UNSIGNED,   8,     FALSE,  //IDS_FMTDESC_L8,
    D3DFMT_P8,              "P8",             //TYPE_UNSIGNED,   8,     FALSE,  //IDS_FMTDESC_P8,
    D3DFMT_R3G3B2,          "R3G3B2",         //TYPE_UNSIGNED,   8,     FALSE,  //IDS_FMTDESC_R3G3B2, 
    D3DFMT_A1R5G5B5,        "A1R5G5B5",       //TYPE_UNSIGNED,   16,    TRUE,   //IDS_FMTDESC_A1R5G5B5, 
    D3DFMT_A4R4G4B4,        "A4R4G4B4",       //TYPE_UNSIGNED,   16,    TRUE,   //IDS_FMTDESC_A4R4G4B4, 
    D3DFMT_A8L8,            "A8L8",           //TYPE_UNSIGNED,   16,    TRUE,   //IDS_FMTDESC_A8L8,
    D3DFMT_A8P8,            "A8P8",           //TYPE_UNSIGNED,   16,    TRUE,   //IDS_FMTDESC_A8P8,
    D3DFMT_A8R3G3B2,        "A8R3G3B2",       //TYPE_UNSIGNED,   16,    TRUE,   //IDS_FMTDESC_A8R3G3B2, 
    D3DFMT_L16,             "L16",            //TYPE_UNSIGNED,   16,    FALSE,  //IDS_FMTDESC_L16,
    D3DFMT_R5G6B5,          "R5G6B5",         //TYPE_UNSIGNED,   16,    FALSE,  //IDS_FMTDESC_R5G6B5, 
    D3DFMT_X1R5G5B5,        "X1R5G5B5",       //TYPE_UNSIGNED,   16,    FALSE,  //IDS_FMTDESC_X1R5G5B5, 
    D3DFMT_X4R4G4B4,        "X4R4G4B4",       //TYPE_UNSIGNED,   16,    FALSE,  //IDS_FMTDESC_X4R4G4B4, 
    D3DFMT_R8G8B8,          "R8G8B8",         //TYPE_UNSIGNED,   24,    FALSE,  //IDS_FMTDESC_R8G8B8, 
    D3DFMT_A2B10G10R10,     "A2B10G10R10",    //TYPE_UNSIGNED,   32,    TRUE,   //IDS_FMTDESC_A2B10G10R10,
    D3DFMT_A2R10G10B10,     "A2R10G10B10",    //TYPE_UNSIGNED,   32,    TRUE,   //IDS_FMTDESC_A2R10G10B10, 
    D3DFMT_A8B8G8R8,        "A8B8G8R8",       //TYPE_UNSIGNED,   32,    TRUE,   //IDS_FMTDESC_A8B8G8R8,
    D3DFMT_A8R8G8B8,        "A8R8G8B8",       //TYPE_UNSIGNED,   32,    TRUE,   //IDS_FMTDESC_A8R8G8B8, 
    D3DFMT_G16R16,          "G16R16",         //TYPE_UNSIGNED,   32,    FALSE,  //IDS_FMTDESC_G16R16,
    D3DFMT_X8B8G8R8,        "X8B8G8R8",       //TYPE_UNSIGNED,   32,    FALSE,  //IDS_FMTDESC_X8B8G8R8,
    D3DFMT_X8R8G8B8,        "X8R8G8B8",       //TYPE_UNSIGNED,   32,    FALSE,  //IDS_FMTDESC_X8R8G8B8, 
    D3DFMT_A16B16G16R16,    "A16B16G16R16",   //TYPE_UNSIGNED,   64,    TRUE,   //IDS_FMTDESC_A16B16G16R16, 
    											//									//
    D3DFMT_CxV8U8,          "CxV8U8",         //TYPE_SIGNED,     16,    FALSE,  //IDS_FMTDESC_CxV8U8,
    D3DFMT_V8U8,            "V8U8",           //TYPE_SIGNED,     16,    FALSE,  //IDS_FMTDESC_V8U8,
    D3DFMT_Q8W8V8U8,        "Q8W8V8U8",       //TYPE_SIGNED,     32,    TRUE,   //IDS_FMTDESC_Q8W8V8U8,
    D3DFMT_V16U16,          "V16U16",         //TYPE_SIGNED,     32,    FALSE,  //IDS_FMTDESC_V16U16,
    D3DFMT_Q16W16V16U16,    "Q16W16V16U16",   //TYPE_SIGNED,     64,    TRUE,   //IDS_FMTDESC_Q16W16V16U16,
    											//									//
    D3DFMT_L6V5U5,          "L6V5U5",         //TYPE_MIXED,      16,    FALSE,  //IDS_FMTDESC_L6V5U5,
    D3DFMT_A2W10V10U10,     "A2W10V10U10",    //TYPE_MIXED,      32,    FALSE,  //IDS_FMTDESC_A2W10V10U10,
    D3DFMT_X8L8V8U8,        "X8L8V8U8",       //TYPE_MIXED,      32,    FALSE,  //IDS_FMTDESC_X8L8V8U8,
    											//									//
    D3DFMT_DXT1,            "DXT1",           //TYPE_FOUR_CC,    4,     TRUE,   //IDS_FMTDESC_DXT1, 
    D3DFMT_DXT2,            "DXT2",           //TYPE_FOUR_CC,    8,     FALSE,  //IDS_FMTDESC_DXT2, 
    D3DFMT_DXT3,            "DXT3",           //TYPE_FOUR_CC,    8,     TRUE,   //IDS_FMTDESC_DXT3, 
    D3DFMT_DXT4,            "DXT4",           //TYPE_FOUR_CC,    8,     FALSE,  //IDS_FMTDESC_DXT4, 
    D3DFMT_DXT5,            "DXT5",           //TYPE_FOUR_CC,    8,     TRUE,   //IDS_FMTDESC_DXT5, 
    D3DFMT_G8R8_G8B8,       "G8R8_G8B8",      //TYPE_FOUR_CC,    16,    FALSE,  //IDS_FMTDESC_G8R8_G8B8,
    D3DFMT_R8G8_B8G8,       "R8G8_B8G8",      //TYPE_FOUR_CC,    16,    FALSE,  //IDS_FMTDESC_R8G8_B8G8,
    D3DFMT_UYVY,            "UYVY",           //TYPE_FOUR_CC,    16,    FALSE,  //IDS_FMTDESC_UYVY,
    D3DFMT_YUY2,            "YUY2",           //TYPE_FOUR_CC,    16,    FALSE,  //IDS_FMTDESC_YUY2,   
												//									//
    D3DFMT_R16F,            "R16F",           //TYPE_FLOAT,      16,    FALSE,  //IDS_FMTDESC_R16F,
    D3DFMT_G16R16F,         "G16R16F",        //TYPE_FLOAT,      32,    FALSE,  //IDS_FMTDESC_G16R16F,  
    D3DFMT_A16B16G16R16F,   "A16B16G16R16F",  //TYPE_FLOAT,      64,    TRUE,   //IDS_FMTDESC_A16B16G16R16F,
												//									//
    D3DFMT_R32F,            "R32F",           //TYPE_IEEE,       32,    FALSE,  //IDS_FMTDESC_R32F,
    D3DFMT_G32R32F,         "G32R32F",        //TYPE_IEEE,       64,    FALSE,  //IDS_FMTDESC_G32R32F,
    D3DFMT_A32B32G32R32F,   "A32B32G32R32F",  //TYPE_IEEE,       128,   TRUE,   //IDS_FMTDESC_A32B32G32R32F, 
};
const int fmtInfoArraySize = sizeof(fmtInfoArray) / sizeof(fmtInfoArray[0]);

const FMTINFO bufferFmtInfoArray[] = 
{
	D3DFMT_D16_LOCKABLE,	"D16_LOCKABLE",
	D3DFMT_D32,				"D32",
	D3DFMT_D15S1,			"D15S1",	
	D3DFMT_D24S8,			"D24S8",	
	D3DFMT_D24X8,			"D24X8",	
	D3DFMT_D24X4S4,			"D24X4S4",	
	D3DFMT_D32F_LOCKABLE,	"D32F_LOCKABLE",
	D3DFMT_D24FS8,			"D24FS8",
	D3DFMT_D32_LOCKABLE,	"D32_LOCKABLE",
	D3DFMT_S8_LOCKABLE,		"S8_LOCKABLE",
	D3DFMT_D16,				"D16",
};

const int bufferFmtInfoArraySize = sizeof(bufferFmtInfoArray) / sizeof(bufferFmtInfoArray[0]);
}//end namespace MME

#endif // _FORMATS_H_