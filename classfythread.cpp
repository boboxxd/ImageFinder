#include "classfythread.h"
#include <QDir>
#include<QStringList>
#include <QDebug>
#include<QFileInfo>
Classfythread::Classfythread()
{

}

void Classfythread::run()
{
    static int index=0;
    emit sendtxt("in thread : "+path);
    QDir dir(path);
    if(!QDir("1k").exists())
        dir.mkdir("0k");
    if(!QDir("0k").exists())
        dir.mkdir("1k");
    QStringList filters;
    filters<<"*.jpg"<<"*.JPG"<<"*.jpeg"<<"*.JPEG";
    dir.setNameFilters(filters);
    QStringList list(dir.entryList());
    image_count=list.count();
    for(auto i=list.begin();i!=list.end();i++)
    {
        finish_count=index;
        rest_count=image_count-index;
        jpgname=dir.absoluteFilePath(*i);; //图片文件名
        txtname=jpgname+".txt";//txt 文件名


    if(QFile(txtname).exists())
    {
        int txtsize=QFileInfo(txtname).size();
        if(txtsize)
        {
            //这是1k
            qDebug()<<"1k"<<jpgname;

            if(iscopy==true)
            {
                //拷贝
                ++index;
                qDebug()<<"拷贝";
                const char * cmd1=QString("cp "+jpgname+" "+dir.absolutePath()+"/1k/").toLocal8Bit();
                if(!system(cmd1))
                {
                    emit sendtxt("拷贝"+jpgname+"成功");
                }
                const char * cmd2=QString("cp "+txtname+" "+dir.absolutePath()+"/1k/").toLocal8Bit();
                if(!system(cmd2))
                {
                    emit sendtxt("拷贝"+txtname+"成功");
                }
            }else{
                //移动
                qDebug()<<"移动";
                ++index;
                const char * cmd1=QString("mv "+jpgname+" "+dir.absolutePath()+"/1k/").toLocal8Bit();
                if(!system(cmd1))
                {
                    emit sendtxt("移动"+jpgname+"成功");
                }
                const char * cmd2=QString("mv "+txtname+" "+dir.absolutePath()+"/1k/").toLocal8Bit();
                if(!system(cmd2))
                {
                    emit sendtxt("移动"+txtname+"成功");
                }

            }

        }else
        {
            //这是0k

            qDebug()<<"0k"<<jpgname;
            if(iscopy==true)
            {
                //拷贝
                qDebug()<<"拷贝";
                ++index;
                const char * cmd1=QString("cp "+jpgname+" "+dir.absolutePath()+"/0k/").toLocal8Bit();
                if(!system(cmd1))
                {
                    emit sendtxt("拷贝"+jpgname+"成功");
                }
                const char * cmd2=QString("cp "+txtname+" "+dir.absolutePath()+"/0k/").toLocal8Bit();
                if(!system(cmd2))
                {
                    emit sendtxt("拷贝"+txtname+"成功");
                }

            }else{
                //移动
                qDebug()<<"移动";
                ++index;
                const char * cmd1=QString("mv "+jpgname+" "+dir.absolutePath()+"/0k/").toLocal8Bit();
                if(!system(cmd1))
                {
                    emit sendtxt("移动"+txtname+"成功");
                }
                const char * cmd2=QString("mv "+txtname+" "+dir.absolutePath()+"/0k/").toLocal8Bit();
                if(!system(cmd2))
                {
                    emit sendtxt("移动"+txtname+"成功");
                }

            }
        }

    }else
    {
        //qDebug()<<txtname<<"is not exists!";
    }

    }
}

void Classfythread::getmethod(bool way)
{
    iscopy=way;
}

void Classfythread::getpath(QString m_path)
{
    path=m_path;
}



Classfythread::~Classfythread()
{

}
