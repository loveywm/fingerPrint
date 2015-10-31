/*#############################################################################
 * �ļ�����import.cpp
 * ���ܣ�  һЩ������ͼ�����
#############################################################################*/


#include "import.h"

#include <stdio.h>
#define DIB_HEADER_MARKER   ((FvsWord_t) ('M' << 8) | 'B')


/******************************************************************************
  * ���ܣ����ļ��м���ָ��ͼ��
  * ������image       ָ��ͼ��
  *       filename    �ļ���
  * ���أ�������
******************************************************************************/
FvsError_t FvsImageImport(FvsImage_t image, const FvsString_t filename,
                          FvsByte_t bmfh[14], BITMAPINFOHEADER *bmih, RGBQUAD *rgbq) {
    FvsError_t ret = FvsOK;
    FvsByte_t*    buffer;
    FvsInt_t      pitch;
    FvsInt_t      height;
    FvsInt_t      width;
    FvsInt_t i, x, y;
    FvsFile_t	file;
//	FvsByte_t bmfh0[14];
//	BITMAPINFOHEADER bmih0;
    file	  = FileCreate();
    if(FileOpen(file, filename, FvsFileRead) == FvsFailure) {
        ret = FvsFailure;
    }
    if(FileRead(file, bmfh, 14) != 14)
        ret = FvsFailure;
    if(*(FvsWord_t*)bmfh != DIB_HEADER_MARKER)
        ret = FvsFailure;
    if(FileRead(file, bmih, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
        ret = FvsFailure;
    if(bmih->biBitCount != 8)
        ret = FvsFailure;
    if(FileRead(file, rgbq, sizeof(RGBQUAD) * 256) != sizeof(RGBQUAD) * 256)
        ret = FvsFailure;
    if(ret == FvsFailure)
    {
        printf("File format or Read file error");
        return ret;
    }
    else
    {
        ret = ImageSetSize(image, (FvsInt_t)bmih->biWidth, (FvsInt_t)bmih->biHeight);
        if (ret == FvsOK) {
            /* ��û����� */
            buffer = ImageGetBuffer(image);
            pitch  = ImageGetPitch(image);
            height = ImageGetHeight(image);
            width  = ImageGetWidth(image);
            x = *(FvsDword_t*)(bmfh + 10);
            /* �������� */
            for (i = 0; i < height; i++) {
                y = (height - 1 - i) * WIDTHBYTES(width * 8);
                FileSeek(file, x + y);
                FileRead(file, buffer + i * pitch, pitch);
            }
        }
    }
    FileDestroy(file);
    return ret;
}



