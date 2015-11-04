/*#############################################################################
 * 文件名：import.cpp
 * 功能：  一些基本的图像操作
#############################################################################*/


#include "import.h"

#include <stdio.h>
#define DIB_HEADER_MARKER   ((FvsWord_t) ('M' << 8) | 'B')


/******************************************************************************
  * 功能：从文件中加载指纹图像
  * 参数：image       指纹图像
  *       filename    文件名
  * 返回：错误编号
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
    if(FileOpen(file, filename, FvsFileRead) == FvsFailure)
    {
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


    printf("0x4d bmfh[0]==%p\r\n",bmfh[0]);
    printf("0x42 bmfh[1]==%p\r\n",bmfh[1]);

    printf("bfSize==%d\r\n",(bmfh[5]<<24) | (bmfh[4]<<16) | (bmfh[3]<<8) | bmfh[2]);

    printf("bmfh[2]==%d\r\n",bmfh[2]);
    printf("bmfh[3]==%d\r\n",bmfh[3]);
    printf("bmfh[4]==%d\r\n",bmfh[4]);
    printf("bmfh[5]==%d\r\n",bmfh[5]);

    printf("bfSize==%dKByte\r\n",((bmfh[5]<<24) | (bmfh[4]<<16) | (bmfh[3]<<8) | bmfh[2])/1024);


    printf("bfOffBits==%d\r\n",(bmfh[13]<<24) | (bmfh[12]<<16) | (bmfh[11]<<8) | bmfh[10]);
    printf("bmfh[10]==%d\r\n",bmfh[10]);
    printf("bmfh[11]==%d\r\n",bmfh[11]);
    printf("bmfh[12]==%d\r\n",bmfh[12]);
    printf("bmfh[13]==%d\r\n",bmfh[13]);

    if(((bmfh[13]<<24) | (bmfh[12]<<16) | (bmfh[11]<<8) | bmfh[10]) == 54)
    {
        printf("BMPBit == 24 or BMPBit == 32\r\n");
    }else
    {
        printf("BMPBit <= 8\r\n");
    }


    printf("bmih->biSize==%d\r\n",bmih->biSize);
    printf("bmih->biWidth==%d\r\n",bmih->biWidth);
    printf("bmih->biHeight==%d\r\n",bmih->biHeight);
    printf("bmih->biPlanes==%d\r\n",bmih->biPlanes);
    printf("bmih->biBitCount==%d\r\n",bmih->biBitCount);
    printf("bmih->biCompression==%d\r\n",bmih->biCompression);
    printf("bmih->biSizeImage==%dKbyte\r\n",bmih->biSizeImage/1024);
    printf("bmih->biXPelsPerMeter==%d\r\n",bmih->biXPelsPerMeter);
    printf("bmih->biYPelsPerMeter==%d\r\n",bmih->biYPelsPerMeter);
    printf("bmih->biClrUsed==%d\r\n",bmih->biClrUsed);
    printf("bmih->biClrImportant==%d\r\n",bmih->biClrImportant);



    if(ret == FvsFailure)
    {
        printf("File format or Read file error");
        return ret;
    }
    else
    {
        ret = ImageSetSize(image, (FvsInt_t)bmih->biWidth, (FvsInt_t)bmih->biHeight);
        if (ret == FvsOK)
        {
            /* 获得缓冲区 */
            buffer = ImageGetBuffer(image);
            pitch  = ImageGetPitch(image);
            height = ImageGetHeight(image);
            width  = ImageGetWidth(image);

            //printf("buffer==%dKbyte\r\n",buffer/1024);
            printf("pitch==%d\r\n",pitch);
            printf("height==%d\r\n",height);
            printf("width==%d\r\n",width);


            x = *(FvsDword_t*)(bmfh + 10);
            /* 拷贝数据 */
            for (i = 0; i < height; i++)
            {
                y = (height - 1 - i) * WIDTHBYTES(width * 8);
                FileSeek(file, x + y);
                FileRead(file, buffer + i * pitch, pitch);
            }
        }
    }
    FileDestroy(file);
    return ret;
}



