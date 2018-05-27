#include "dta.h"

DTA::DTA(const QString &path) : BMP(path)
{
    getBMPInformation();
}

DTA::~DTA()
{
    close();
}

int8_t DTA::check()
{
    if ( (getBitPerPixel() != 4)||
         (getClrUsed() != 4))
        return 1;
    if ( (abs(getWith()) == 600 && abs(getHeight()) == 800) ||
         (abs(getWith()) == 800 && abs(getHeight()) == 600))
         return 0;
    else return 2;
}

uint8_t DTA::_convert(uint8_t buf[])
{
    uint16_t _buf = *(uint16_t*)buf;
    uint8_t ret = 0;

    ret |= ((_buf & 0x3000) >> 12) << 2;
    ret |= ((_buf & 0x0300) >> 8) << 0;
    ret |= ((_buf & 0x0030) >> 4) << 6;
    ret |= ((_buf & 0x0003) >> 0) << 4;

    return ret;
}

bool DTA::convert(const QString &path)
{
    QFile target(path);

    if (target.exists() && exists() != true) return false;

    open(QFile::ReadOnly);
    target.open(QFile::WriteOnly);

    target.write("AuthorQQ:1326841769", 32);
    target.seek(32);

    for (int32_t line = 0; line < abs(getHeight()); line++)
    {
        seek(getLineOffset(line));
        for (int32_t col = 0; col < abs(getWith()) / getBitPerPixel(); col++)
        {
            uint8_t buf[2];
            read((char*)&buf, 2);
            uint8_t _buf = _convert(buf);
            target.write((char*)&_buf, 1);
        }
    }

    close();
    target.close();

    return true;
}
