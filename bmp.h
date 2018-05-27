#ifndef BMP_H
#define BMP_H

#include <QFile>

#pragma pack(push)
#pragma pack(2)

typedef struct _BMP_Header_Structure{
    char bfType[2];		//位图文件类型
    uint32_t bfSize;	//位图文件大小
    uint16_t Reserved1;	//保留
    uint16_t Reserved2;	//保留
    uint32_t bfOffBits; //位图数据起始位置
}BMP_Header_Typedef_t;

typedef struct _BMP_Info_Structure {
    uint32_t biSize;	//本结构体占用字节
    int32_t biWith;	//位图宽度
    int32_t biHeight;	//位图高度
    uint16_t biPlanes;	//目标设备的级别
    uint16_t biBitCount;//像素位数
    uint32_t biCompression;//压缩类型
    uint32_t biSizeImage;//位图大小，包含字节对齐的空字节
    uint32_t biXPelsPerMeter;//位图水平分辨率
    uint32_t biYPelsPerMeter;//位图垂直分辨率
    uint32_t biClrUsed;	//位图实际使用的颜色表中的颜色数
    uint32_t biClrImportant;//位图显示过程中重要的颜色数
} BMP_Info_Typedef_t;

typedef struct _BMP_ColorMap_Structure {
    uint8_t rgbB;
    uint8_t rgbG;
    uint8_t rgbR;
    uint8_t Reserved;
} BMP_ColorMap_Typedef_t;

#pragma pack(pop)

typedef uint32_t BMP_ColorMapCount_Typedef_t;

class BMP : public QFile
{
public:
    BMP(const QString &);
    ~BMP();

    int getLineOffset(int);
    int getBMPInformation();
    int getWith();
    int getHeight();
    int getBitPerPixel();
    int getClrUsed();
private:
    BMP_Header_Typedef_t BMP_Header;
    BMP_Info_Typedef_t   BMP_Info;
    BMP_ColorMap_Typedef_t *pBMP_ColorMap;
    BMP_ColorMapCount_Typedef_t BMP_ColorMapCount;
};

#endif // BMP_H
