#include <QCoreApplication>
#include <QDebug>

#include "ImageLoader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ImageLoader loader;
    qDebug()<<loader.GetCachePath();
    QObject::connect(&loader, &ImageLoader::ImageLoaded,
                     [&](const QUrl& url, const QString &path){
        qDebug()<<"load image url:"<<url<<" filepath:"<<path;
    });
    loader.LoadImage(QUrl("http://media.wired.com/photos/5b899992404e112d2df1e94e/master/pass/trash2-01.jpg"));
    loader.LoadImage(QUrl("http://d27jswm5an3efw.cloudfront.net/app/uploads/2019/12/how-to-make-a-url-for-a-picture-on-your-computer-25.png"));
    return a.exec();
}
