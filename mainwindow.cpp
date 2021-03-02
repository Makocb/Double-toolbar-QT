#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);

    //this is nessesary
    this->ui->toolBar_2->layout()->setSpacing(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_splitter_splitterMoved(int pos, int /*index*/, bool windowResized)
{
    if (((pos>this->ui->listWidget->minimumSize().width()) &&
        (pos<(this->width() - this->ui->listWidget_2->minimumSize().width()))) || windowResized)
    {
        this->ui->toolBar->setMaximumSize(pos, ui->toolBar->rect().height());
        this->ui->toolBar->setMinimumSize(pos, ui->toolBar->rect().height());
    }
    //ui->toolBar->resize(pos, ui->toolBar->rect().height());
    //ui->toolBar_2->move(pos, 21);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* /*e*/)
{
    if (toolbar_dragged)
    {
        toolbar_dragged = false;
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QList<int> currentSizes = this->ui->splitter->sizes();
    if ((this->ui->toolBar_2->underMouse()) &&
        (event->buttons() == Qt::LeftButton) &&
        (event->pos().x() < (currentSizes[0]+20)))
    {
        this->ui->toolBar_2->movableChanged(true);
        toolbar_dragged = true;
        this->setCursor(Qt::SizeHorCursor);
    }
    else if ((this->ui->toolBar->underMouse()) &&
             (event->buttons() == Qt::LeftButton) &&
             (event->pos().x() > (currentSizes[0]-20)))
    {
        this->ui->toolBar->movableChanged(true);
        toolbar_dragged = true;
        this->setCursor(Qt::SizeHorCursor);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    QList<int> currentSizes = this->ui->splitter->sizes();
    if (toolbar_dragged)
    {
        QList<int> currentSizes = this->ui->splitter->sizes();
        currentSizes[0] = event->pos().x();
        currentSizes[1] = this->width() - event->pos().x();
        this->ui->splitter->setSizes(currentSizes);
        emit on_splitter_splitterMoved(event->pos().x(), 1, false);

    }
    else if ((event->pos().y() > (2+this->ui->toolBar->y())) &&
             (event->pos().y() < (this->ui->toolBar->height()-2+this->ui->toolBar->y())) &&
             (event->pos().x() < (currentSizes[0]+5)) &&
             (event->pos().x() > (currentSizes[0]-10)))
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    QList<int> currentSizes = this->ui->splitter->sizes();
    this->ui->toolBar_2->adjustSize();
    emit on_splitter_splitterMoved(currentSizes[0], 1,true);
    killTimer(event->timerId());
    timerId = 0;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{

        if (timerId)
        {
            killTimer(timerId);
            timerId = 0;
        }
        // delay beetween ends of resize and your action
        timerId = startTimer(1);

    QMainWindow::resizeEvent(event);
}
