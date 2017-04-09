#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrinter>
#include <QPrintDialog>
#endif

#include "scribblearea.h"
#include "pointquadtree.h"

PointQuadtree *tree;
int RR;

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    tree = new PointQuadtree;
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    select = false;
    myPenWidth = 1;
    myPenColor = Qt::black;
}

void ScribbleArea::setPenColor(const QColor &newColor)

{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)

{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
    tree->root = NULL;
    cout << "cleared!" << endl;
}

void ScribbleArea::random(int N)
{
    srand((unsigned)time(0));
    int random1, random2;
    int lowest=0, highest=MAX;
    int range=(highest-lowest)+1;
    for(int i=0; i<N; i++)
    {
        random1 = lowest+int(range*rand()/(RAND_MAX + 1.0));
        random2 = lowest+int(range*rand()/(RAND_MAX + 1.0));

        drawLineTo(QPoint(random1,random2));
    }
}

void ScribbleArea::selection(int R)
{
    if(tree->root!=NULL)
    {
        RR = R;
        select = true;
    }
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        scribbling = true;
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        scribbling = false;
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling && select)
    {
        drawCircle(event->pos());
        scribbling = false;
    }

    else if (event->button() == Qt::LeftButton && scribbling)
    {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawCircle(const QPoint &endPoint)
{
    QPainter painter(&image);
    tmppainter = &painter;
    myPenColor = Qt::black;
    myPenWidth = 1;
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawEllipse(endPoint.x()-RR,endPoint.y()-RR,2*RR,2*RR);
    select = false;
    tree->checkCircle(endPoint.x(),endPoint.y(),RR);
    update();
    modified = true;
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    myPenColor = Qt::blue;
    myPenWidth = 6;
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(endPoint);
    tree->insert(endPoint.x(),endPoint.y());

    myPenColor = Qt::black;
    myPenWidth = 1;
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(endPoint.x(),tree->target->LN,endPoint.x(),tree->target->LS);
    painter.drawLine(tree->target->LW,endPoint.y(),tree->target->LE,endPoint.y());
    update();

    modified = true;
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::print()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}
