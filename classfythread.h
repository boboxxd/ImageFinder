#ifndef CLASSFYTHREAD_H
#define CLASSFYTHREAD_H
#include <QThread>
#include <QString>
#include<QMutex>
class Classfythread : public QThread
{
    Q_OBJECT
public:
    static Classfythread *Create()
    {
        static Classfythread thread;
        return &thread;
    }

   void run();
   Classfythread();
   virtual ~Classfythread();
   QString path;
   QString txtname=0;
   QString jpgname=0;
   int image_count=0;//图片总数
   int finish_count=0;//完成图片数
   int rest_count=0;//剩余图片数
   bool iscopy=true;

signals:
   void sendtxt(QString);

public slots:
   void getmethod(bool);
   void getpath(QString);
};

#endif // CLASSFYTHREAD_H
