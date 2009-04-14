/**
 * File: GUI/gui.cpp - Implementation of GUI in MiptVis
 * Copyright (C) 2009  Lev Rumyantsev, Ivan Mashintsev
 */
#include "gui_impl.h"


/**
 * Test function for Qt. It create a window with text "Qt works!"
 */
bool showGraph( int argc, char * argv[], Graph * graph)
{
    QApplication app( argc, argv);
    QLabel *label = new QLabel( "Qt works!");
    label->show();
    app.exec();
    return true;
}

/** 
 * Test scene with rectangles and text
 */
bool showScene( int argc, char * argv[], Graph * graph)
{
    QApplication app2( argc, argv);
    Scene * scene = new Scene();
    scene->setSceneRect( QRectF( 0, 0, 550, 500));
    QGraphicsView * view = new QGraphicsView( scene);
    view->setWindowTitle
        ( "Double click on a free space to create a node. And double click on a text to edit it");
    view->show();
    app2.exec();
    return true;
}