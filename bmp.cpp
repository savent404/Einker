#include "bmp.h"

BMP::BMP(const QString &filepath)
{
    setFileName(filepath);
}

BMP::~BMP()
{
}

int BMP::getBMPInformation()
{
    if (exists() == false) return -1;
    open(QFile::ReadOnly);
    read((char*)&BMP_Header, (qint64)sizeof(BMP_Header_Typedef_t));
    read((char*)&BMP_Info, (qint64)sizeof(BMP_Info_Typedef_t));
    close();
    return 0;
}

int BMP::getWith()
{
    return BMP_Info.biWith;
}

int BMP::getHeight()
{
    return BMP_Info.biHeight;
}

int BMP::getBitPerPixel()
{
    return BMP_Info.biBitCount;
}

int BMP::getClrUsed()
{
    return BMP_Info.biClrUsed;
}

int BMP::getLineOffset(int line)
{
    if (getHeight() < 0) {
        return BMP_Header.bfOffBits + (BMP_Info.biBitCount * BMP_Info.biWith / 8) * line;
    }

    else {
        return BMP_Header.bfOffBits + (BMP_Info.biBitCount * BMP_Info.biWith / 8) * (BMP_Info.biHeight - line);
    }
}

