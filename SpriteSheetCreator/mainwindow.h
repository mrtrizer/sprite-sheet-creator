#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    static char * dirs[8];
    void removePink(QImage * image);
    QPushButton * dirButtons[8];

private slots:
    void onCreateClicked();
    void onSaveButton();
    void onPathButton();

};

#endif // MAINWINDOW_H
