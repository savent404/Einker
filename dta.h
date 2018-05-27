#ifndef DTA_H
#define DTA_H

#include "bmp.h"

class DTA : public BMP
{
public:
    DTA(const QString &path);
    ~DTA();

    /*
     * @Retval 1-颜色深度有误 2-图片大小有误
     */
    int8_t check();
    bool convert(const QString &path);
private:
    uint8_t _convert(uint8_t[]);
};

#endif // DTA_H
