#include "maincontrol.h"
#include "ui_maincontrol.h"
#include "QDebug"


uchar g_BitmapBuffer[1920*1080*4] = {0};
static QImage g_cameraImage( g_BitmapBuffer, 1920, 1080, QImage::Format_Indexed8 );

MainControl::MainControl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainControl)
{
    ui->setupUi(this);
    QString filedir=QCoreApplication::applicationDirPath();
//    QWidget::showFullScreen();
    preview = false;
    gtsthread = new GtsThread(this);
    mythread = new QThread();
    gtsthread->moveToThread(mythread);
    connect(this,SIGNAL(GTSDoEmit(int,int,double,double)),gtsthread,SLOT(GTSDoProc(int,int,double,double)),Qt::QueuedConnection);
    connect(gtsthread,SIGNAL(SendStatus(int,int,double,double)),this,SLOT(ShowStatus(int,int,double,double)),Qt::QueuedConnection);
    mythread->start();
    emit GTSDoEmit(GTSINIT);
    emit GTSDoEmit(GTSCLEAR);

    fileListWidget = new QListWidget(this);
    connect(fileListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
                this, SLOT(slotDirShow(QListWidgetItem*)));
    fileListWidget->hide();
    ui->LePrjShow->setText(filedir);
    QIntValidator v( -500, 500, this );
    ui->LeMainSpc->setValidator( &v );

}

MainControl::~MainControl()
{
    qDebug()<<"~MainControl";
    if(gtsthread!=NULL)
    {

        mythread->quit();
        mythread->wait();
        delete gtsthread;
        gtsthread = NULL;
    }
    delete ui;
}

//退出程序
void MainControl::on_BtMianExit_clicked()
{
    //todo samething
    if(preview)
    {
        Camtask->DestroyThread();
        QThread::msleep(300);
        delete Camtask;
        preview = false;
    }
    if(gtsthread!=NULL)
    {

        mythread->quit();
        mythread->wait();
        delete gtsthread;
        gtsthread = NULL;
    }
    exit(0);
}

//预览回显
void MainControl::display(int index )
{
    QPixmap fitpixmap = QPixmap::fromImage(g_cameraImage).scaled(ui->CamView->width(), ui->CamView->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->CamView->setPixmap( fitpixmap );
}

//从测试页面返回
void MainControl::DisplayMainUi()
{
    this->show();
    if(preview)
    {
        Camtask->ResumeThread();
    }
    if(gtsthread == NULL)
    {
        gtsthread = new GtsThread(this);
        mythread = new QThread();
        gtsthread->moveToThread(mythread);
        connect(this,SIGNAL(GTSDoEmit(int,int,double,double)),gtsthread,SLOT(GTSDoProc(int,int,double,double)),Qt::QueuedConnection);
        connect(gtsthread,SIGNAL(SendStatus(int,int,double,double)),this,SLOT(ShowStatus(int,int,double,double)),Qt::QueuedConnection);
        mythread->start();
        emit GTSDoEmit(GTSINIT);
        emit GTSDoEmit(GTSCLEAR);
    }
}
void MainControl::ShowStatus(int index,int code,double value0,double value1)
{
    int nRet = -1;
    switch (index)
    {
        case GTSINIT:

        break;
        case GTSCLEAR:

        break;
        case GTSGOHOME:

        break;
        case GTSGOZERO:

        break;
        case GTSGOUP:

        break;
        case GTSGODOWN:

        break;
        case GTSJOGAX1EABLE:

        break;
        case GTSJOGAX2EABLE:

        break;
        case GTSJOGAX3EABLE:


        break;
        case GTSJOGAX1CONF:

        break;
        case GTSJOGAX2CONF:

        break;
        case GTSJOGAX3CONF:

        break;
        case GTSCRDPRM:
            if(code == 1)
            {
                if(dxfworklist.size() == dxfindex)
                {
                    dxfindex = 0;
                    dxfworklist.clear();
                    ui->BtMainStar->setStyleSheet("");
                    break;
                }
                int spc = ui->LeMainSpc->text().toInt();
                if(spc == 0)
                {
                    spc = 10;
                }
                for(;dxfindex < dxfworklist.size();)
                {
                    Vertexdxf val = dxfworklist.at(dxfindex);

                    qDebug()<<"x:"<<val.x<<"y:"<<val.y<<"z:"<<val.z<<"r:"<<val.r;
                    if(val.r == 0)//直线
                    {
                        nRet = gtsthread->AddCrdPrmLine(val.x*1000,val.y*1000,spc,0.1,0);
                    }
                    else// 圆弧
                    {
                        nRet = gtsthread->AddCrdPrmR(val.x*1000,val.y*1000,val.r*1000,0,spc,0.1,0);
                    }
                    if(nRet<0)
                    {
                        break;
                    }
                    dxfindex++;
                }
                emit GTSDoEmit(GTSCRDPRM,1);
            }
            else
            {
                ui->LbX->setText("X:    "+QString::number(value0, 'f', 3));
                ui->LbY->setText("Y:    "+QString::number(value1, 'f', 3));
                ui->LbZ->setText("Z:    0.000");
            }
        break;
        default:
        break;
    }
    return;
}

// 进入测试页面
void MainControl::on_Bttestcontrol_clicked()
{
    if(preview)
    {
        Camtask->StopThread();
    }
    if(gtsthread!=NULL)
    {
        mythread->quit();
        mythread->wait();
        delete gtsthread;
        gtsthread = NULL;
    }
    this->hide();
    TestControl*TsCtrol = new TestControl;
    connect(TsCtrol,SIGNAL(showMainUi()),this,SLOT(DisplayMainUi()),Qt::QueuedConnection);
    TsCtrol->show();
}

//设置页面
void MainControl::on_BtMainSet_clicked()
{

}

void MainControl::on_BtPreviewMain_clicked()
{

    if(!preview)
    {
        Camtask = new CamThread(this);
        connect(Camtask,SIGNAL(showimage(int)),this,SLOT(display(int)),Qt::QueuedConnection);
        Camtask->start();
        preview = true;
        ui->BtPreviewMain->setText(QString::fromLocal8Bit("停止预览"));
    }
    else
    {
        Camtask->DestroyThread();
        QThread::msleep(300);
        disconnect(Camtask,SIGNAL(showimage(int)),0,0);
        delete Camtask;
        preview = false;
        ui->BtPreviewMain->setText(QString::fromLocal8Bit("开始预览"));
    }
    return;

}



void MainControl::on_BtMainStar_clicked()
{
    int nRet = -1;
    int spc = 0;
    int dimension       =   2;//为二维坐标系
    double synVelMax    =   500;
    double synAccMax    =   1;
    int evenTime        =   50;
    int profile0        =   1;
    int profile1        =   2;
    int setOriginFlag   =   1;
    long originPos0      =   100;
    long originPos1      =   100;

    nRet = gtsthread->CrdPrmSet(dimension,synVelMax, synAccMax, evenTime, profile0, profile1, setOriginFlag, originPos0, originPos1);
    qDebug()<<"CrdPrmSet"<<nRet;

    emit GTSDoEmit(GTSJOGAX1EABLE,1);
    emit GTSDoEmit(GTSJOGAX2EABLE,1);
    emit GTSDoEmit(GTSJOGAX3EABLE,1);
    Dl_CreationClass* creationClass = new Dl_CreationClass(1000);
    DL_Dxf* dxf = new DL_Dxf();

    QString filedir = ui->LePrjShow->text();
    if (!dxf->in(filedir.toStdString(), creationClass))
    {
        qDebug()<< "open "<<filedir<<"fail";
        return;
    }
    creationClass->Dl_myclose();
    dxfworklist.append(creationClass->dxflist);

    spc = ui->LeMainSpc->text().toInt();
    if(spc == 0)
    {
        spc = 10;
    }
    if(dxfworklist.size()>0)
    {
        for(dxfindex   = 0;dxfindex < dxfworklist.size();)
        {
            Vertexdxf val = dxfworklist.at(dxfindex);

            qDebug()<<"x:"<<val.x<<"y:"<<val.y<<"z:"<<val.z<<"r:"<<val.r;
            if(val.r == 0)//直线
            {
                nRet = gtsthread->AddCrdPrmLine(val.x*1000,val.y*1000,spc,0.1,0);
            }
            else// 圆弧
            {
                nRet = gtsthread->AddCrdPrmR(val.x*1000,val.y*1000,val.r*1000,val.direction,spc,0.1,0);// 2022-0808 何晓东增加了圆弧的方向
            }
            if(nRet < 0)
            {
                break;
            }
            dxfindex++;
        }
        emit GTSDoEmit(GTSCRDPRM,1);
        ui->BtMainStar->setStyleSheet("background-color:rgb(0,255,0)");
    }

    delete dxf;
    delete creationClass;
}

void MainControl::on_BtMainStop_clicked()
{
    ui->BtMainStar->setStyleSheet("");
    emit GTSDoEmit(GTSCLEAR);
}

void MainControl::on_BtPrjBrowe_clicked()
{
    QStringList stringlist;

        QString rootStr = ui->LePrjShow->text();
        QFileInfo dir(rootStr);
        QDir rootDir(rootStr);
        if(fileListWidget->isHidden())
        {
            if(dir.isDir())
            {
                stringlist << "*";
                list = rootDir.entryInfoList(stringlist);
                showFileInfoList(list);
            }
            else
            {
                QString path;
                int index;
                index = rootStr.lastIndexOf("/");
                path = rootStr.left(index);
                rootDir.setPath(path);
                stringlist << "*";
                list = rootDir.entryInfoList(stringlist);
                ui->LePrjShow->setText(path);
                showFileInfoList(list);
            }
            int x = ui->LePrjShow->geometry().x();
            int w = ui->LePrjShow->geometry().width();
            int y = ui->LePrjShow->geometry().y();
            int h = ui->LePrjShow->geometry().height();

            fileListWidget->setGeometry(x,y+h+5,w,h*7);
            fileListWidget->setMinimumSize(w,h*7);
            fileListWidget->setMaximumSize(w,h*7);
            fileListWidget->show();
            ui->BtPrjBrowe->setText(QString::fromLocal8Bit("取消"));
        }
        else
        {
            ui->BtPrjBrowe->setText(QString::fromLocal8Bit("浏览"));
            fileListWidget->clear();
            fileListWidget->hide();
        }
}



//---用双击浏览器中显示的目录进入下一级，或者返回上一级目录。
void MainControl::showFileInfoList(QFileInfoList list)
{
    int index = 0;
    //--清空列表控件
    fileListWidget->clear();
    //----取出所有项，按照目录，文件方式添加到控件内
    for (int i = 0; i < list.count(); i++)
    {
        QFileInfo tmpFileInfo = list.at(i);
        if (tmpFileInfo.isDir())
        {
            QIcon icon("dir.png");
            QString fileName = tmpFileInfo.fileName();
            QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
            fileListWidget->addItem(tmpListWidgetItem);
        }
        else
        {
            QString fileName = tmpFileInfo.fileName();
            index = fileName.lastIndexOf(".");
            QString typestr = fileName.right(fileName.size()-index);
            if(typestr == ".dxf"||typestr == ".DXF")
            {
                QIcon icon("file.png");
                QListWidgetItem*tmpListWidgetItem = new QListWidgetItem(icon, fileName);
                fileListWidget->addItem(tmpListWidgetItem);
            }
        }
    }
}

//----根据用户的选择显示下一级目录下的文件，
void MainControl::slotDirShow(QListWidgetItem *Item)
{
    //----保存下一级目录名
    QString string = Item->text();
    QString Path;
    QDir dir;
    Path = ui->LePrjShow->text();
    if(Path.right(1)!="/")
    {
        Path.append("/");
    }
    //----设置路径为当前目录路径
    dir.setPath(Path);

    QFileInfo fileinfo(Path+string);
    if(fileinfo.isDir())
    {
        //-----重新设置路径
        dir.cd(string);
        //----更新当前显示路径， 这里获取的是绝对路径
        ui->LePrjShow->setText(dir.absolutePath());
        //---显示当前文件目录下的所有文件
        slotShow(dir);
    }
    else
    {
        ui->BtPrjBrowe->setText(QString::fromLocal8Bit("浏览"));
        ui->LePrjShow->setText(Path+string);
        fileListWidget->clear();
        fileListWidget->hide();
    }
}

//--显示当前目录下的所有文件
void MainControl::slotShow(QDir dir)
{
     QStringList stringList;
     stringList << "*";
     QFileInfoList InfoList = dir.entryInfoList(stringList, QDir :: AllEntries, QDir :: DirsFirst);
     showFileInfoList(InfoList);
}
