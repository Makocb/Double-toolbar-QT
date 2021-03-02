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

private slots:
    void on_splitter_splitterMoved(int pos, int index, bool windowResized  = true);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *event);

    void timerEvent(QTimerEvent *event);
    void resizeEvent(QResizeEvent* event);

private:
    Ui::MainWindow *ui;
    int timerId = 0;
    bool toolbar_dragged = false;
};
#endif // MAINWINDOW_H
