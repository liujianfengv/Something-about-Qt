#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QNetworkAccessManager>

///
/// \brief 图片下载工具类
/// 从网络下载图片，使用链接名的md5值为文件名做本地磁盘缓存
/// 获取图片时优先检查缓存，缓存中不存在的话从网络下载
///
class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(QObject *parent = nullptr);
    ImageLoader(const QString &cachePath, QObject *parent = nullptr);
    ///
    /// \brief 加载图片
    /// \param 图片链接
    ///
    void LoadImage(const QUrl& url);
    ///
    /// \brief 获取缓存路径
    /// \return 缓存路径
    ///
    const QString &GetCachePath() const;
    ///
    /// \brief 设置缓存路径
    /// \param 缓存路径
    ///
    void SetCachePath(const QString &cachePath);
signals:
    ///
    /// \brief 图片加载完成
    /// \param url 图片链接
    /// \param path 图片存储路径
    ///
    void ImageLoaded(const QUrl& url, const QString &path);
private slots:
    void OnRequestFinished(QNetworkReply *reply);
private:
    ///
    /// \brief 从网络下载图片
    /// \param url 图片链接
    ///
    void LoadImageFromNetwork(const QUrl &url);
    ///
    /// \brief 从本地缓存获取图片
    /// \param url 图片链接
    /// \return true: 获取成功
    ///         false: 获取失败，本地无缓存
    ///
    bool LoadImageFromLocalCache(const QUrl &url);

    QString MD5(const QUrl &url);
private:
    ///
    /// \brief 图片缓存路径
    ///
    QString m_cachePath;
    QNetworkAccessManager *m_manager;
};

#endif // IMAGELOADER_H
