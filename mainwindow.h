#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MODE int
#include <QMainWindow>
#include <QButtonGroup>
namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isclassfy=true;//0为0k1k分类；1为找原图
    bool iscopy=true;//0为拷贝；1为找移动
public slots:
    void onopenbtn();
    void onstartbtn();
    void oncancelbtn();
    void onButtonClicked1(int);
    void onButtonClicked2(int);

signals:
    void sendmethod(bool way);
private:
    Ui::MainWindow *ui;
    QButtonGroup buttongroup1,buttongroup2;
};

#endif // MAINWINDOW_H
