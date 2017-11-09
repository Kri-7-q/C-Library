#ifndef CONSOLE_GLOBAL_H
#define CONSOLE_GLOBAL_H

#include <QtCore/qglobal.h>


#if defined(CONSOLE_LIBRARY)
#  define CONSOLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CONSOLESHARED_EXPORT Q_DECL_IMPORT
#endif


class CONSOLESHARED_EXPORT TextStyle
{
public:
    enum Effect { Normal, Bold, Italic, Underlined = 4, Blinking, Inverse = 7 };
    enum Color { Black = 30, Red, Green, Brown, Blue, Purple, Cyan, Gray, Standard = 39 };
    enum TextAlign { Left = 0, Center = 2, Rigth = 1 };
};

#endif // CONSOLE_GLOBAL_H
