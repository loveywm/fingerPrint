#include "widget1.h"
#include "ui_widget1.h"


static FvsError_t OverlayDirection(FvsImage_t image, const FvsFloatField_t field) {
    FvsError_t nRet = FvsOK;
    FvsInt_t w      = ImageGetWidth (image);
    FvsInt_t h      = ImageGetHeight(image);
    FvsInt_t pitch, dirp;
    FvsFloat_t theta, c, s;
    FvsByte_t* p;
    FvsFloat_t* orientation;
    FvsInt_t x, y, size, i, j, l;
    size = 8;
    (void)ImageLuminosity(image, 168);
    pitch  = ImageGetPitch (image);
    p      = ImageGetBuffer(image);
    orientation = FloatFieldGetBuffer(field);
    dirp        = FloatFieldGetPitch(field);
    if (p == NULL || orientation == NULL)
        return FvsMemory;
    for (y = size; y < h - size; y += size - 2)
        for (x = size; x < w - size; x += size - 2) {
            theta = orientation[x + y * dirp];
            c = cos(theta);
            s = sin(theta);
            for (l = 0; l < size; l++) {
                i = (FvsInt_t)(x + size / 2 - l * s);
                j = (FvsInt_t)(y + size / 2 + l * c);
                p[i + j * pitch] = 0;
            }
        }
    return nRet;
}

widget1::widget1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget1)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    //ui->scrollArea->setWidgetResizable(true);
    connect(ui->pushButton_openFile, SIGNAL(clicked()), this, SLOT(openFile()));
    //connect(ui->pushButton_Process, SIGNAL(clicked()), this, SLOT(processImage()));
}

widget1::~widget1()
{
    delete ui;
}


void widget1::openFile()
{
    QPixmap tempPic;
    filename = QFileDialog::getOpenFileName(this, "Open bmp Image", QDir::currentPath(), "BMP files(*.bmp)");
    ui->lineEdit_fileName->setText(filename);

    //bmpfilename = filename;
    minutiaSet = MinutiaSetCreate(defaultSetSize);
    bmpfilename = filename;
    genPic = true;
    radius = 4.0;
    char *orifilename = bmpfilename.toLatin1().data();
    tempPic.load(orifilename);
    ui->label_origin->setPixmap(tempPic);
}

void widget1::on_pushButton_direction_clicked()
{
    QPixmap tempPic;
    QString tname;
    //FvsImage_t mask;
    FvsImage_t image;
    FvsImage_t directionimage;
    //FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    //FvsFloatField_t frequency;
    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    //mask = ImageCreate();
    image = ImageCreate();
    directionimage = ImageCreate();
    direction = FloatFieldCreate();
    //frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq))
    {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    //tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    FvsInt_t w  = ImageGetWidth (image);
    FvsInt_t h  = ImageGetHeight(image);
    ImageSetSize(directionimage, w, h);


    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);

    //FingerprintGetFrequency1(image, direction, frequency);
    //FingerprintGetMask(image, direction, frequency, mask);
    //ImageEnhanceGabor(image, direction, frequency, mask, radius);
    OverlayDirection(directionimage, direction);
    //saving file....
    if(genPic)
    {
        tname = bmpfilename + "_dir.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(directionimage, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //directionLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("1");
    }

}

void widget1::on_pushButton_mask_clicked()
{
    QPixmap tempPic;
    QString tname;
    FvsImage_t mask;
    FvsImage_t image;
    //FvsImage_t directionimage;
    //FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    FvsFloatField_t frequency;

    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    mask = ImageCreate();
    image = ImageCreate();
    //directionimage = ImageCreate();
    direction = FloatFieldCreate();
    frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq))
    {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    //tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    //FvsInt_t w  = ImageGetWidth (image);
    //FvsInt_t h  = ImageGetHeight(image);
    //ImageSetSize(directionimage, w, h);

    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);
    FingerprintGetFrequency1(image, direction, frequency);
    FingerprintGetMask(image, direction, frequency, mask);
    //ImageEnhanceGabor(image, direction, frequency, mask, radius);
    //OverlayDirection(directionimage, direction);
    //saving file....
    if(genPic)
    {
        tname = bmpfilename + "_mask.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(mask, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //maskLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("2");
    }
}

void widget1::on_pushButton_enhance_clicked()
{
    QPixmap tempPic;
    QString tname;
    FvsImage_t mask;
    FvsImage_t image;
    FvsImage_t directionimage;
    //FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    FvsFloatField_t frequency;
    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    mask = ImageCreate();
    image = ImageCreate();
    directionimage = ImageCreate();
    direction = FloatFieldCreate();
    frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq)) {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    FvsInt_t w  = ImageGetWidth (image);
    FvsInt_t h  = ImageGetHeight(image);
    ImageSetSize(directionimage, w, h);
    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);
    FingerprintGetFrequency1(image, direction, frequency);
    FingerprintGetMask(image, direction, frequency, mask);
    ImageEnhanceGabor(image, direction, frequency, mask, radius);
    OverlayDirection(directionimage, direction);
    //saving file....
    if(genPic)
    {
        tname = bmpfilename + "_enh.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(image, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //enhanceLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("3");
    }
}

void widget1::on_pushButton_binarize_clicked()
{
    QPixmap tempPic;
    QString tname;
    FvsImage_t mask;
    FvsImage_t image;
    FvsImage_t directionimage;
    //FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    FvsFloatField_t frequency;
    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    mask = ImageCreate();
    image = ImageCreate();
    directionimage = ImageCreate();
    direction = FloatFieldCreate();
    frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq)) {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    FvsInt_t w  = ImageGetWidth (image);
    FvsInt_t h  = ImageGetHeight(image);
    ImageSetSize(directionimage, w, h);
    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);
    FingerprintGetFrequency1(image, direction, frequency);
    FingerprintGetMask(image, direction, frequency, mask);
    ImageEnhanceGabor(image, direction, frequency, mask, radius);
    OverlayDirection(directionimage, direction);
    //saving file....
    ImageBinarize(image, (FvsByte_t)0x80);
    if(genPic)
    {
        tname = bmpfilename + "_bin.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(image, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //binarizeLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("4");
    }
}

void widget1::on_pushButton_thinning_clicked()
{
    QPixmap tempPic;
    QString tname;
    FvsImage_t mask;
    FvsImage_t image;
    FvsImage_t directionimage;
    //FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    FvsFloatField_t frequency;
    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    mask = ImageCreate();
    image = ImageCreate();
    directionimage = ImageCreate();
    direction = FloatFieldCreate();
    frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq)) {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    FvsInt_t w  = ImageGetWidth (image);
    FvsInt_t h  = ImageGetHeight(image);
    ImageSetSize(directionimage, w, h);
    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);
    FingerprintGetFrequency1(image, direction, frequency);
    FingerprintGetMask(image, direction, frequency, mask);
    ImageEnhanceGabor(image, direction, frequency, mask, radius);
    OverlayDirection(directionimage, direction);
    //saving file....

    ImageThinHitMiss(image);
    if(genPic)
    {
        tname = bmpfilename + "_thin.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(image, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //thinningLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("5");
    }

}

void widget1::on_pushButton_6_clicked()
{
    QPixmap tempPic;
    QString tname;
    FvsImage_t mask;
    FvsImage_t image;
    FvsImage_t directionimage;
    FvsMinutiaSet_t minutia = minutiaSet;
    FvsFloatField_t direction;
    FvsFloatField_t frequency;
    FvsByte_t bmfh[14];
    BITMAPINFOHEADER bmih;
    RGBQUAD rgbq[256];
    char *orifilename = bmpfilename.toLatin1().data();
    char *fname;
    mask = ImageCreate();
    image = ImageCreate();
    directionimage = ImageCreate();
    direction = FloatFieldCreate();
    frequency = FloatFieldCreate();
    if(FvsOK != FvsImageImport(image, orifilename, bmfh, &bmih, rgbq)) {
        QMessageBox::information(NULL, "Error", "BMP file error!");
        return;
    }
    tempPic.load(orifilename);
    //originLabel->setPixmap(tempPic);
    FvsInt_t w  = ImageGetWidth (image);
    FvsInt_t h  = ImageGetHeight(image);
    ImageSetSize(directionimage, w, h);
    ImageSoftenMean(image, 3);
    ImageNormalize(image, 100, 10000);
    FingerprintGetDirection(image, direction, 7, 8);
    FingerprintGetFrequency1(image, direction, frequency);
    FingerprintGetMask(image, direction, frequency, mask);
    ImageEnhanceGabor(image, direction, frequency, mask, radius);
    OverlayDirection(directionimage, direction);
    //saving file....

    MinutiaSetExtract(minutia, image, direction, mask);
    if(genPic)
    {
        ImageClear(image);
        MinutiaSetDraw(minutia, image);
        tname = bmpfilename + "_minu.bmp";
        fname = tname.toLatin1().data();
        FvsImageExport(image, fname, bmfh, &bmih, rgbq);
        tempPic.load(fname);
        //minutiaLabel->setPixmap(tempPic);
        ui->label_origin_2->setPixmap(tempPic);
        ui->label_5->setText("6");
    }
}
