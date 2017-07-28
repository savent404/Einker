#ifndef DTA_H
#define DTA_H

#include "BMP.h"

class DTA : public BMP
{
public:
    DTA(const QString &path);
    ~DTA();

    bool check();
    bool convert(const QString &path);
private:
    uint8_t _convert(uint8_t[]);
};

#endif // DTA_H
