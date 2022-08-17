/*
 * @file Dl_CreationClass.cpp
 */

/*****************************************************************************
**  $Id: Dl_CreationClass.cpp 8865 2008-02-04 18:54:02Z andrew $
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

#include "include/dl_creationclass.h"

#include <iostream>
#include <stdio.h>
#include <QDebug>
#define qDebug QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug

/**
 * Default constructor.
 */
Dl_CreationClass::Dl_CreationClass(long precision)
{
    //dxffp = fopen("dxf.txt","ab+");
    actionflag = false;
    dxflist.clear();
    dxfprecision = precision;
    memset(&lastVertex,0,sizeof(Vertexdxf));
}

void Dl_CreationClass::Dl_myclose()
{

    actionflag = false;
    //close(dxffp);
   // dxffp = NULL;
    return;
}


/**
 * Sample implementation of the method which handles layers.
 */
void Dl_CreationClass::addLayer(const DL_LayerData& data) {
    //printf("LAYER: %s flags: %d\n", data.name.c_str(), data.flags);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles point entities.
 */
void Dl_CreationClass::addPoint(const DL_PointData& data) {
    //printf("POINT    (%6.3f, %6.3f, %6.3f)\n",
    //       data.x, data.y, data.z);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles line entities.
 */
void Dl_CreationClass::addLine(const DL_LineData& data) {
    //printf("LINE     (%6.3f, %6.3f, %6.3f) (%6.3f, %6.3f, %6.3f)\n",
    //       data.x1, data.y1, data.z1, data.x2, data.y2, data.z2);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles arc entities.
 */
void Dl_CreationClass::addArc(const DL_ArcData& data) {
    //printf("ARC      (%6.3f, %6.3f, %6.3f) %6.3f, %6.3f, %6.3f\n",
    //       data.cx, data.cy, data.cz,
    //       data.radius, data.angle1, data.angle2);
    //printAttributes();
}

/**
 * Sample implementation of the method which handles circle entities.
 */
void Dl_CreationClass::addCircle(const DL_CircleData& data) {
    //printf("CIRCLE   (%6.3f, %6.3f, %6.3f) %6.3f\n",
    //       data.cx, data.cy, data.cz,
    //       data.radius);
    //printAttributes();
}


/**
 * Sample implementation of the method which handles polyline entities.
 */
void Dl_CreationClass::addPolyline(const DL_PolylineData& data) {
    //printf("POLYLINE \n");
    //printf("flags: %d\n", (int)data.flags);
    //printAttributes();
qDebug()<<"flags:"<<data.flags;
    if(data.flags == 1)//2022-0808-何晓东128->1
    {
       actionflag = true;
    }

}


/**
 * Sample implementation of the method which handles vertices.
 */
void Dl_CreationClass::addVertex(const DL_VertexData& data) {


    //char line[1024] = {0};
    //sprintf(line,"(%6.3f, %6.3f, %6.3f) %6.3f\n",data.x, data.y, data.z,data.bulge);
    //addfile(line,strlen(line));
    if(actionflag)
    {
        //printf("VERTEX   (%6.3f, %6.3f, %6.3f) %6.3f\n",
        //       data.x, data.y, data.z,
        //       data.bulge);
        Vertexdxf ver;

        ver.x       =   data.x;
        ver.y       =   data.y;
        ver.z       =   data.z;
        ver.bulge   =   data.bulge;
        ver.r       =   0;
        ver.active  =   true;
        ver.direction=  0;
        if(lastVertex.active)
        {
            if(lastVertex.bulge != 0)
            {
                if(lastVertex.bulge > 1 || lastVertex.bulge < -1 ) //2022-0808 这个if条件，何晓东改：如果是优弧，ta则为余切
                {
                    lastVertex.bulge = 1/lastVertex.bulge;  //2022-0808 何晓东改：如果是优弧，ta则为余切
                    ver.r    =   -0.5*sqrt((ver.x-lastVertex.x)*(ver.x-lastVertex.x)+(ver.y-lastVertex.y)*(ver.y-lastVertex.y))/((fabs(2*lastVertex.bulge))/(1+lastVertex.bulge*lastVertex.bulge));
                }
                else    ver.r    =   0.5*sqrt((ver.x-lastVertex.x)*(ver.x-lastVertex.x)+(ver.y-lastVertex.y)*(ver.y-lastVertex.y))/(fabs(2*lastVertex.bulge)/(1+lastVertex.bulge*lastVertex.bulge));
                if(lastVertex.bulge>0) ver.direction =1;
            }//2022-0808 何晓东改：在公示前面加了“-”，因为固高定义的半径是有方向的，需要进行计算
            dxflist.append(ver);
            //printf("VERTEX   (%6.4f, %6.4f, %6.4f,%6.4f) %6.4f\n",ver.x, ver.y, ver.z,ver.r,ver.bulge);

        }
        memcpy(&lastVertex,&ver,sizeof(Vertexdxf));
    }
    //printAttributes();
}


void Dl_CreationClass::add3dFace(const DL_3dFaceData& data) {
    //printf("3DFACE\n");
    //for (int i=0; i<4; i++) {
        //printf("   corner %d: %6.3f %6.3f %6.3f\n",
        //    i, data.x[i], data.y[i], data.z[i]);
    //}
    //printAttributes();
}

void Dl_CreationClass::addfile(const char* text,int size)
{


}

void Dl_CreationClass::printAttributes() {
    return;
    printf("  Attributes: Layer: %s, ", attributes.getLayer().c_str());
    printf(" Color: ");
    if (attributes.getColor()==256)	{
        printf("BYLAYER");
    } else if (attributes.getColor()==0) {
        printf("BYBLOCK");
    } else {
        printf("%d", attributes.getColor());
    }
    printf(" Width: ");
    if (attributes.getWidth()==-1) {
        printf("BYLAYER");
    } else if (attributes.getWidth()==-2) {
        printf("BYBLOCK");
    } else if (attributes.getWidth()==-3) {
        printf("DEFAULT");
    } else {
        printf("%d", attributes.getWidth());
    }
    printf(" Type: %s\n", attributes.getLinetype().c_str());
}
    
    

// EOF
