#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QImage"
#include "QPainter"
#include "QBrush"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->createButton,SIGNAL(clicked()),this,SLOT(onCreateClicked()));
    QObject::connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(onSaveButton()));
    QObject::connect(ui->pathButton,SIGNAL(clicked()),this,SLOT(onPathButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::removePink(QImage * image)
{
    for (int i = 0; i < image->width(); i++)
        for (int j = 0; j < image->height(); j++)
        {
            QRgb rgb = image->pixel(i,j);
            if ((qGreen(rgb) <= 1) && (qRed(rgb) >= 254) && (qBlue(rgb) >= 254))
                image->setPixel(i,j,0x00000000);
        }
}

void MainWindow::onCreateClicked()
{
    QString str = ui->pathEdit->text();
    QImage currentImage;
    QImage * image = new QImage(ui->widthBox->value() * ui->stepsBox->value(),ui->heightBox->value() * 8,QImage::Format_ARGB32);
    QPainter painter(image);
    painter.setBackground(QBrush(QColor(0,0,0,0)));
    painter.eraseRect(0,0,ui->widthBox->value() * 9,ui->heightBox->value() * 8);
    for (int i = 0; i < 8; i++)
        for (int j = 0;j < ui->stepsBox->value(); j++)
        {
            currentImage.load(str + "/" + QString::number(i) + "/" + QString::number(j),"PNG");
            removePink(&currentImage);
            painter.drawImage(
                  QRect(ui->widthBox->value() * j,ui->heightBox->value() * i,ui->widthBox->value(),ui->heightBox->value()),
                  currentImage,
                  QRect(ui->xStartBox->value(),ui->yStartBox->value(),
                        ui->xEndBox->value() - ui->xStartBox->value(),
                        ui->yEndBox->value() - ui->yStartBox->value()));
        }
    image->save(ui->saveEdit->text());
}

void MainWindow::onSaveButton()
{
    QString dir = QFileDialog::getSaveFileName(this, tr("SaveFile"),"");
    ui->saveEdit->setText(dir);
}

void MainWindow::onPathButton()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"", QFileDialog::ShowDirsOnly
    | QFileDialog::DontResolveSymlinks);
    ui->pathEdit->setText(dir);
}
