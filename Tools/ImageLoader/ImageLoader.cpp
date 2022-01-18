#include "ImageLoader.h"

#include <QNetworkReply>
#include <QDir>
#include <QDebug>

ImageLoader::ImageLoader(QObject *parent):
    QObject(parent)
{
    SetCachePath(QDir::currentPath());
    m_manager = new QNetworkAccessManager(this);
    connect(m_manager, &QNetworkAccessManager::finished,
            this, &ImageLoader::OnRequestFinished);
}

ImageLoader::ImageLoader(const QString &cachePath, QObject *parent):
    ImageLoader(parent)
{
    SetCachePath(cachePath);
}

void ImageLoader::LoadImage(const QUrl &url)
{
    if (!LoadImageFromLocalCache(url)) {
        LoadImageFromNetwork(url);
    }
}

const QString &ImageLoader::GetCachePath() const
{
    return m_cachePath;
}

void ImageLoader::SetCachePath(const QString &CachePath)
{
    m_cachePath = CachePath;
    QDir dir;
    if (!dir.exists(m_cachePath)) {
        dir.mkpath(m_cachePath);
    }
}

void ImageLoader::OnRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        const QUrl &url = reply->url();
        const QString &filePath = m_cachePath + QDir::separator() + MD5(url);
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            emit ImageLoaded(url, filePath);
            file.close();
        }
    }
    reply->deleteLater();
}

void ImageLoader::LoadImageFromNetwork(const QUrl &url)
{
    QNetworkRequest request;
    request.setUrl(url);
    m_manager->get(request);
}

bool ImageLoader::LoadImageFromLocalCache(const QUrl &url)
{
    bool res = false;
    const QString &filePath = m_cachePath + QDir::separator() + MD5(url);
    if (QFileInfo::exists(filePath)) {
        emit ImageLoaded(url, filePath);
        res = true;
    }
    return res;
}

QString ImageLoader::MD5(const QUrl &url)
{
    return QString(QCryptographicHash::hash(url.toString().toStdString().c_str(),
                                             QCryptographicHash::Md5).toHex());
}
