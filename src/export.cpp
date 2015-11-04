
/*#############################################################################
 * �ļ�����export.cpp
 * ���ܣ�  ָ��ͼ���������
#############################################################################*/

#include "export.h"

#include <stdio.h>


/******************************************************************************
  * ���ܣ���һ��ָ��ͼ�������һ���ļ����ļ��ĸ�ʽ���ļ�����չ������
  * ������filename  ��Ҫ����ͼ����ļ���
  *       image     ��Ҫ������ͼ��
  * ���أ��������
******************************************************************************/
FvsError_t  FvsImageExport(const FvsImage_t image, const FvsString_t filename,
                           FvsByte_t bmfh[14], BITMAPINFOHEADER *bmih, RGBQUAD *rgbq)
{
    FvsError_t ret = FvsOK;
    FvsByte_t*		buffer;
    FvsInt_t		pitch;
    FvsInt_t		height;
    FvsInt_t		width;
    FvsInt_t		i;
    FvsFile_t	file;
    file	  = FileCreate();
    if(FileOpen(file, filename, (FvsFileOptions_t)(FvsFileWrite | FvsFileCreate)) == FvsFailure) {
        ret = FvsFailure;
    }
    if(FileWrite(file, bmfh, 14) != 14)
        ret = FvsFailure;
    if(FileWrite(file, bmih, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
        ret = FvsFailure;
    if(FileWrite(file, rgbq, sizeof(RGBQUAD) * 256) != sizeof(RGBQUAD) * 256)
        ret = FvsFailure;
    if(ret == FvsFailure) {
        printf("Write file error");
        return ret;
    }
    else
    {
        /* ��û����� */
        buffer = ImageGetBuffer(image);
        pitch  = ImageGetPitch(image);
        height = ImageGetHeight(image);
        width  = ImageGetWidth(image);
        /* �������� */
        for (i = height - 1; i >= 0; i--)
        {
            FileWrite(file, buffer + i * pitch, WIDTHBYTES(pitch * 8));
        }
    }
    FileDestroy(file);
    return ret;
}



