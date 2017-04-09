#include "mainwindow.h"
#include "scribblearea.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scribbleArea = new ScribbleArea;
    resize(741, 541);
    setWindowTitle("QuadTree2");

    QVBoxLayout *vbox = new QVBoxLayout();

    QFrame *frame1 = new QFrame(this);
    frame1->setFrameStyle(QFrame::Box);
    frame1->setGeometry(10,10,521,521);

    QFrame *frame2 = new QFrame(this);
    frame2->setFrameStyle(QFrame::Box);
    frame2->setGeometry(541,10,190,521);

    nbrSpinBox = new QSpinBox(this);
    nbrSpinBox->setRange(0, 50);
    nbrSpinBox->setValue(10);
    nbrLabel = new QLabel(tr("Number of Points:"));
    nbrLabel->setBuddy(nbrSpinBox);

    radSpinBox = new QSpinBox(this);
    radSpinBox->setRange(0, 500);
    radSpinBox->setValue(100);
    radLabel = new QLabel(tr("Radius of Selection:"));
    radLabel->setBuddy(radSpinBox);

    QPushButton *random = new QPushButton("Randomize", this);
    QPushButton *select = new QPushButton("Select", this);
    QPushButton *clear = new QPushButton("Clear", this);
    QPushButton *close = new QPushButton("Close", this);
    label = new QLabel("", this);

    vbox->setSpacing(3);
    vbox->addStretch(1);
    vbox->addWidget(nbrLabel);
    vbox->addWidget(nbrSpinBox);
    vbox->addWidget(random);
    vbox->addWidget(radLabel);
    vbox->addWidget(radSpinBox);
    vbox->addWidget(select);
    vbox->addWidget(clear);
    vbox->addWidget(close);
    vbox->addWidget(label, 0, Qt::AlignLeft | Qt::AlignTop);
    vbox->addStretch(1);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(scribbleArea, 0, 0, 1, 1);
    frame1->setLayout(mainLayout);

    QGridLayout *controlLayout = new QGridLayout;
    controlLayout->addLayout(vbox, 0, 0, 1, 1);
    frame2->setLayout(controlLayout);

    connect(random, &QPushButton::clicked, this, &MainWindow::randomize);
    connect(select, &QPushButton::clicked, this, &MainWindow::select);
    connect(clear, &QPushButton::clicked, this, &MainWindow::clear);
    connect(close, &QPushButton::clicked, qApp, &QApplication::quit);

    startTimer(100);
}

void MainWindow::timerEvent(QTimerEvent *e){

    Q_UNUSED(e);
    QPoint p = scribbleArea->mapFromGlobal(QCursor::pos());
    label->setText("Mouse position: " + QString::number(p.x()) + "," + QString::number(p.y()));
}

void MainWindow::randomize()
{
    int nbr = nbrSpinBox->value();
    (*scribbleArea).clearImage();
    (*scribbleArea).random(nbr);
}

void MainWindow::select()
{
    int nbr = radSpinBox->value();
    (*scribbleArea).selection(nbr);
}

void MainWindow::clear()
{
    (*scribbleArea).clearImage();
    update();
}
