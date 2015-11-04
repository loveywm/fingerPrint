#ifndef WIDGET1_H
#define WIDGET1_H

#include <QWidget>


#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>

#include "./inc/fvs.h"


namespace Ui {
class widget1;
}

class widget1 : public QWidget
{
    Q_OBJECT

public:
    explicit widget1(QWidget *parent = 0);
    ~widget1();


private:
    Ui::widget1 *ui;
    QString filename,filename1,filename2;
    //QString bmpfilename;

    bool genPic;
    QString bmpfilename;
    const static int defaultSetSize=1200;
    double radius;
    //QLabel *originLabel,*directionLabel,*maskLabel,*enhanceLabel,*binarizeLabel,*thinningLabel,*minutiaLabel;
    FvsMinutiaSet_t minutiaSet;

private slots:
    void openFile();
    //void processImage();

    void on_pushButton_direction_clicked();
    void on_pushButton_mask_clicked();
    void on_pushButton_enhance_clicked();
    void on_pushButton_binarize_clicked();
    void on_pushButton_thinning_clicked();
    void on_pushButton_6_clicked();
};

#endif // WIDGET1_H
