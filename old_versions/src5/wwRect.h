#ifndef _WW_RECT_H_
#define _WW_RECT_H_

typedef struct wwRect
{
    int x;
    int y;
    int width;
    int height;
    
}wwRect;

typedef struct wwRectStruct
{
    wwRect rect;
    int visible;
    unsigned short id;
}wwRectStruct;

#endif /* _WW_RECT_H_ */