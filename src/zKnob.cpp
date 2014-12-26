#include <QtGui/QGraphicsSceneMouseEvent>
#include "../nanovg/nanovg.h"
#include "zKnob.h"
#include "../draw.h"
zKnob::zKnob(QDeclarativeItem *parent)
{
     setFlag(QGraphicsItem::ItemHasNoContents, false);
     setKeepMouseGrab(true);
     m_value = 0.1;
     //setMouseTracking(true); 
}
NVGcontext *initVG();
//
void zKnob::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    printf("paint(%p,%f,%f,%f,%f)\n", this,
            x(),y(),width(),height());
    painter->beginNativePainting();
    glScissor(x(), widget->window()->height()-height()-y(), width(), height());
    glEnable(GL_SCISSOR_TEST);
    glClearColor(0, 0, 0.0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    NVGcontext *vg = (NVGcontext*)initVG();
    //drawButton(vg, "banana", 0, 0, 100, 50);
    printf("view(%f vs %f)\n", widget->window()->height()-height()-y(), y());
    glViewport(x(), widget->window()->height()-height()-y(), width(), height());
    nvgBeginFrame(vg, width(), height(), 1.0);
    //drawButton(vg, "banana", 100, 25, 100, 50);
    //drawOptButton(vg, "opt", 200, 25, 100, 50);
    //drawButtonGrid(vg, 4,4, 300, 0, 100, 100);
    drawAltDial(vg, m_value, 0, 0, width(),height());//400, 0, 100, 100);
    //drawGrid(vg, 8, 8, 500, 0, 200, 200);
    //drawSin(vg,  500, 0, 200, 200);
    //	nvgBeginPath(vg);
    //    float cx = 40.0, cy = 40.0, h = 10.0;
    //    nvgArc(vg, cx, cy, 0.4*h, 0, 1.0/2.0*M_PI, 1);
    //    nvgArc(vg, cx, cy, 0.2*h, 1.0/2.0*M_PI, 0, 2);
    //    nvgClosePath(vg);
    //	nvgFillColor(vg, nvgRGBA(0x11,0x45,0x75,255));
    //	nvgFill(vg);
    nvgEndFrame(vg);
    
}

void zKnob::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    auto p = event->pos();
    printf("mouse: %f %f\n",p.x(), p.y());
}
        
bool zKnob::sceneEvent ( QEvent * event )
{
    printf("EVENT...\n");
    return false;

}
