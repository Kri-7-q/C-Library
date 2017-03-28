#ifndef COLORBOOL_H
#define COLORBOOL_H

#include "console_global.h"

class CONSOLESHARED_EXPORT ColorBool {
public:
    ColorBool();
    ColorBool(const bool boolean);

    bool operator == (const ColorBool& other) const;
    bool operator == (const bool boolean) const;
    void operator = (const ColorBool& other);
    void operator = (const bool boolean);

private:
    bool m_bool;
};

#endif // COLORBOOL_H
