/**
 * @file test_creationclass.h
 */

/*****************************************************************************
**  $Id: test_creationclass.h 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#ifndef DL_CREATIONCLASS_H
#define DL_CREATIONCLASS_H

#include "dl_creationadapter.h"

#include <QList>

/**
 * This class takes care of the entities read from the file.
 * Usually such a class would probably store the entities.
 * this one just prints some information about them to stdout.
 *
 * @author Andrew Mustun
 */
typedef struct Vertexdxf_{
    bool    active;
    double    x;
    double    y;
    double    z;
    double    r;
    double  bulge;
    int     direction; //2022-0808 何晓东改，增加了这个变量用来描述圆弧方向
}Vertexdxf;

typedef struct Vertexdxfparm_{
    bool    active;
    double    x;
    double    y;
    double    z;
    double    r;
    double  bulge;
}Vertexdxfparm;

class Dl_CreationClass : public DL_CreationAdapter {
public:
    Dl_CreationClass(long precision);
    QList<Vertexdxf>dxflist;
    bool  actionflag;
    Vertexdxf lastVertex;
    long dxfprecision;
    virtual void addLayer(const DL_LayerData& data);
    virtual void addPoint(const DL_PointData& data);
    virtual void addLine(const DL_LineData& data);
    virtual void addArc(const DL_ArcData& data);
    virtual void addCircle(const DL_CircleData& data);
    virtual void addPolyline(const DL_PolylineData& data);
    virtual void addVertex(const DL_VertexData& data);
    virtual void add3dFace(const DL_3dFaceData& data);

    void addfile(const char* text,int size);

    void printAttributes();
    void Dl_myclose();
};

#endif
