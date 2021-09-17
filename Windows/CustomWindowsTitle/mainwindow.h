#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onMenuTestClicked();
private:
    void initMenu();
private:
    Ui::MainWindow *ui;

    // QWidget interface
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};
#endif // MAINWINDOW_H
