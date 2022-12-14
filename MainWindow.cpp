#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    this->setWindowIcon(QIcon(":/Images/Icon/favicon.gif"));
    this->setMinimumSize(MAIN_SIZE_X,MAIN_SIZE_Y);
    this->setMouseTracking(true);
    this->setWindowTitle("Xor 7 Atlantis");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QWidget:focus{outline:none;}");
    m_rsideLabel->setCursor(Qt::SizeHorCursor);
    m_rbottomLabel->setCursor(Qt::SizeFDiagCursor);
    m_bottomLabel->setCursor(Qt::SizeVerCursor);
    m_background->setStyleSheet(QString(
        "border-radius:%1px;background-color:rgb(255,255,255);").arg(qCeil(ZOOM(8))));
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(ZOOM(8));
    shadow->setColor(Qt::black);
    shadow->setOffset(0);
    m_background->setGraphicsEffect(shadow);
    connect(m_body,&MainWidget::closeWindow,this,&MainWindow::close);
    connect(m_body,&MainWidget::minimizeWindow,this,&MainWindow::minimizeWindow);
    connect(this,&MainWindow::closeWindow,this,[=](){
        visible=false;
        running=true;
        emit minimizeWindow();
    });
    connect(this,&MainWindow::minimizeWindow,this,[=](){
        flash=true;
        quint16 x=this->x(),y=this->y();
        this->setMinimumSize(0,0);
        QPropertyAnimation *transparentAnimation=new QPropertyAnimation(this,"windowOpacity",this);
        transparentAnimation->setEasingCurve(QEasingCurve::Linear);
        transparentAnimation->setDuration(256);
        transparentAnimation->setKeyValueAt(0, 1);
        transparentAnimation->setKeyValueAt(0.5, 0);
        transparentAnimation->setKeyValueAt(1, 0);
        connect(transparentAnimation,&QPropertyAnimation::finished,this,[=](){
            flash=false;
            this->showMinimized();
            if(!visible) this->hide();
            if(running) qApp->quit();
            this->setWindowOpacity(1);
        });
        transparentAnimation->start();
    });
}
void MainWindow::mousePressEvent(QMouseEvent *event){
    if(flash){
        event->accept();
        return;
    }
    QPoint p=event->pos();
    quint64 left=UNZOOM(p.x()),
            right=UNZOOM(width()-left),
            top=UNZOOM(p.y()),
            bottom=UNZOOM(height()-top);
    m_windowAction=Action::RESIZE;
    if(top<=m_sideWidth.top){
        m_cursorPosFlag=CursorPosFlag::TITLE;
        m_windowAction=Action::MOVE;
    }else if(bottom<=m_sideWidth.bottom){
        if(right<=m_sideWidth.right)
            m_cursorPosFlag=CursorPosFlag::RBOTTOM;
        else m_cursorPosFlag=CursorPosFlag::BOTTOM;
    }else if(right<=m_sideWidth.right)
        m_cursorPosFlag=CursorPosFlag::RSIDE;
    else {
        m_cursorPosFlag=CursorPosFlag::BODY;
        m_windowAction=Action::NOTHING;
    }
    if(m_windowAction==Action::NOTHING)
        event->ignore();
    else {
        if(m_windowAction==Action::MOVE)
            m_movePos = event->globalPosition() - pos();
        else{
            m_resizeLocation = geometry();
            m_resizePos = event->globalPosition();
        }
        event->accept();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(m_windowAction==Action::MOVE){
        QPointF p=event->globalPosition() - m_movePos;
        this->move(p.x(),p.y());
        event->accept();
    }else if(m_windowAction==Action::RESIZE){
        quint32 dx = event->globalPosition().x() - m_resizePos.x();
        quint32 dy = event->globalPosition().y() - m_resizePos.y();
        QRect rc = m_resizeLocation;
        if(m_cursorPosFlag==CursorPosFlag::RSIDE)
            rc.setRight(rc.right() + dx);
        else if(m_cursorPosFlag==CursorPosFlag::BOTTOM)
            rc.setBottom(rc.bottom() + dy);
        else if(m_cursorPosFlag==CursorPosFlag::RBOTTOM){
            rc.setRight(rc.right() + dx);
            rc.setBottom(rc.bottom() + dy);
        }
        setGeometry(rc);
        update();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_windowAction=Action::NOTHING;
    event->ignore();
}
void MainWindow::closeEvent(QCloseEvent *event){
    emit closeWindow();
    event->ignore();
}
void MainWindow::resizeEvent(QResizeEvent *event){
    m_background->resize(this->size().width()-2*ZOOM(8),
                         this->size().height()-2*ZOOM(8));
    m_background->move(ZOOM(8),ZOOM(8));
    m_body->resize(this->size().width()-2*ZOOM(8),
                   this->size().height()-2*ZOOM(8));
    m_body->setParent(m_background);
    m_titleLable->resize(this->size().width(),ZOOM(m_sideWidth.top));
    m_rsideLabel->move(this->size().width()-ZOOM(m_sideWidth.right),
                       m_sideWidth.top);
    m_rsideLabel->resize(ZOOM(m_sideWidth.right),
                         this->size().height());
    m_rbottomLabel->move(this->size().width()-ZOOM(m_sideWidth.right),
                        this->size().height()-ZOOM(m_sideWidth.bottom));
    m_rbottomLabel->resize(ZOOM(m_sideWidth.right),
                           ZOOM(m_sideWidth.bottom));
    m_bottomLabel->move(0,
                        this->size().height()-ZOOM(m_sideWidth.bottom));
    m_bottomLabel->resize(this->size().width()-ZOOM(m_sideWidth.right),
                          ZOOM(m_sideWidth.bottom));
    m_background->show();
    m_rsideLabel->show();
    m_bottomLabel->show();
    m_rbottomLabel->show();
    m_titleLable->show();
    QBitmap mask(this->size());
    mask.fill();
    QPainter maskp(&mask);
    maskp.setRenderHint(QPainter::Antialiasing, true);
    maskp.setPen(Qt::NoPen);
    maskp.setBrush(Qt::black);
    maskp.drawRoundedRect(mask.rect(),ZOOM(8),ZOOM(8));
    setMask(mask);
    event->ignore();
}
//void MainWindow::moveEx(QWidget *w,quint16 x,quint16 y,qint16 mx,qint16 my,quint16 msec,const QEasingCurve &easing,bool control){
//    QPropertyAnimation *Animation=new QPropertyAnimation(w,"pos",w);
//    Animation->setDuration(msec);
//    Animation->setStartValue(QPoint(x,y));
//    Animation->setEndValue(QPoint(mx,my));
//    Animation->setEasingCurve(easing);
//    Animation->start();
//    connect(Animation,&QPropertyAnimation::stateChanged,w,[=](){
//        if(control) flash=false;
//        w->hide();
//        w->move(x,y);
//    });
//    return;
//}
