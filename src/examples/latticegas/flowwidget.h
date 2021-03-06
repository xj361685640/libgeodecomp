#ifndef LIBGEODECOMP_EXAMPLES_LATTICEGAS_FLOWWIDGET_H
#define LIBGEODECOMP_EXAMPLES_LATTICEGAS_FLOWWIDGET_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <QtGui/QColor>
#include <QtGui/QPainter>
#include <QtGui/QWidget>

#include <libgeodecomp/examples/latticegas/simparams.h>
#include <libgeodecomp/misc/fpscounter.h>

/**
 * A simple Qt widget that will render the simulation state in situ.
 */
class FlowWidget : public QWidget, FPSCounter
{
    Q_OBJECT

public:
    FlowWidget() :
        counter(0),
        image(1024, 768, QImage::Format_ARGB32)
    {}

    void paintEvent(QPaintEvent * /* event */)
    {
        QPainter painter(this);

        painter.drawImage(0, 0, image);

        painter.setPen(Qt::green);
        painter.drawText(32, 32, "Frame " + QString::number(counter));
        ++counter;
    }

public slots:
    void ping()
    {
        emit updateImage((unsigned*)image.scanLine(0), image.width(), image.height());
        if (simParamsHost.dumpFrames) {
            dumpFrame();
        }
        update();
        incFrames();
    }

    void info()
    {
        std::cout << "FlowWidget @ " << fps() << " FPS\n";
    }

signals:
    void updateImage(unsigned *image, unsigned width, unsigned height);

private:
    int counter;
    QImage image;

    void dumpFrame()
    {
        std::ostringstream filename;
        filename << "snapshot." << std::setfill('0') << std::setw(4) << counter << ".ppm";
        std::ofstream outfile(filename.str().c_str());
        if (!outfile)
            throw std::runtime_error("Cannot open output file");
        outfile << "P6 " << image.width()
                << " "   << image.height() << " 255\n";

        for (unsigned y = 0; y < image.height(); ++y) {
            for (unsigned x = 0; x < image.width(); ++x) {
                unsigned val = ((unsigned*)image.scanLine(0))[y* image.width() + x];
                unsigned char r = (val >> 16) & 0xff;
                unsigned char g = (val >>  8) & 0xff;
                unsigned char b = (val >>  0) & 0xff;
                outfile << r << g << b;
            }
        }
    }
};

#endif
