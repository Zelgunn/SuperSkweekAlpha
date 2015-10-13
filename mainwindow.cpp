#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle("Super Skweek v0.0 (alpha)");
    setWindowState(Qt::WindowFullScreen);

    new QShortcut(tr("Right"), this, SLOT(onRight()));
    new QShortcut(tr("Left"), this, SLOT(onLeft()));
    new QShortcut(tr("Up"), this, SLOT(onUp()));
    new QShortcut(tr("Down"), this, SLOT(onDown()));

    const Grid *grid = m_game.level(0)->grid();
    QRect rect = QApplication::desktop()->screenGeometry();
    m_appearance.setAppearance(rect.width() - PADDING * 2, rect.height(), grid->width(), grid->height());

    m_timer = new QTimer(this);
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    QObject::connect(&m_game, SIGNAL(gameReady()), this, SLOT(onGameReady()));
    m_timer->start(16);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onGameReady()
{
    m_game.startGame();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);

    paintBackground(painter);
    paintGame(painter);

    if(!m_game.isStarted())
        paintWaitingSign(painter);

    paintProgressionBar(painter);

    painter->end();
}

void MainWindow::paintBackground(QPainter *painter)
{
    static QImage image("C:/Users/degva_000/Documents/C++/build-SSkweek_Alpha-Desktop_Qt_5_5_0_MinGW_32bit-Debug/debug/images/TEST.png");
    QRect rect = QApplication::desktop()->screenGeometry();
    int w = rect.width();
    int h = rect.height();

    painter->setBrush(QColor(0,0,0));
    painter->drawRect(rect);

    while(m_stars.size() < 1000)
    {
        m_stars.append(new QPoint(qrand()%w, qrand()%h));
        m_starsSpeed.append(qrand()%3 + 1);
    }

    QPoint *tmp;
    painter->setBrush(QColor(255,255,255));
    painter->setPen(QColor(255,255,255));


    for(int i = 0; i < m_stars.size(); i++)
    {
        tmp = m_stars.at(i);
        painter->drawPoint(*tmp);
        tmp->setY(tmp->y() - m_starsSpeed.at(i));
        if(i==0)
        {
            painter->drawImage(*tmp, image);
            if(tmp->y() < - image.height())
            {
                tmp->setY(h);
                tmp->setX(qrand()%w - image.width()/2);
            }
        }
        else if(tmp->y() <= 0)
        {
            m_stars.removeAt(i);
            m_starsSpeed.removeAt(i);
            i--;
        }
    }
}

void MainWindow::paintGame(QPainter *painter)
{
    paintMap(painter);
    paintPlayer(painter);
}

void MainWindow::paintMap(QPainter *painter)
{
    Tile *tile;
    const Grid *grid = m_game.level(0)->grid();

    int theight = m_appearance.tileHeight();
    int twidth = m_appearance.tileWidth();
    int dy = m_appearance.dy()/2;

    for(uint i=0; i<grid->width(); i++)
    {
        for(uint j=0; j<grid->height(); j++)
        {
            tile = Tile::tile(grid->tileAt(i,j));
            painter->drawImage(i * twidth + PADDING,
                              j * theight + dy,
                              tile->resizedTexture(twidth, theight));
        }
    }
}

void MainWindow::paintPlayer(QPainter *painter)
{
    int dy = m_appearance.dy()/2;
    int theight = m_appearance.tileHeight();

    const Player *player = m_game.level(0)->player();
    QImage pImage = player->appearance()->scaled(theight, theight);
    painter->drawImage(player->position().x * m_appearance.width() + PADDING - pImage.width() / 2,
                      player->position().y * m_appearance.height()+ dy - pImage.height() / 2,
                      pImage);

    player = m_game.level(0)->player2();
    pImage = player->appearance()->scaled(theight, theight);
    painter->drawImage(player->position().x * m_appearance.width() + PADDING - pImage.width() / 2,
                      player->position().y * m_appearance.height()+ dy - pImage.height() / 2,
                       pImage);
}

void MainWindow::paintWaitingSign(QPainter *painter)
{
    static int dynamicWait = 0;
    const int dynamicSpeed = 30;

    QString message = "En attente de joueur";
    for(int i=0; i<dynamicWait/dynamicSpeed; i++) message = message.append('.');
    dynamicWait = ((dynamicWait + 1) % (dynamicSpeed * 4));

    QFont font("Times", 30, QFont::Bold);
    painter->setFont(font);

    int w = m_appearance.width() * 3/5;
    int h = m_appearance.height() / 10;
    QRect rect;
    rect.setX((m_appearance.width() - w)/2 + PADDING);
    rect.setY((m_appearance.height() - h)/2);
    rect.setWidth(w);
    rect.setHeight(h);

    painter->setBrush(QBrush(QColor(255,255,255,100)));

    painter->drawRect(rect);
    painter->drawText(rect, Qt::AlignCenter, message);
}

void MainWindow::paintProgressionBar(QPainter *painter)
{
    QRect screen = QApplication::desktop()->screenGeometry();
    QRect rect1, rect2;

    rect1.setX(m_appearance.width() + PADDING * 2);
    rect1.setY(m_appearance.dy()/2);
    rect1.setWidth(screen.width() - m_appearance.width() - PADDING * 3);
    rect1.setHeight(m_appearance.height());

    painter->setBrush(QColor(225, 93, 151, 100));
    painter->drawRect(rect1);

    double ratio = m_game.level(0)->playerTileRatio();

    rect2 = rect1;
    rect2.setY(rect1.y() + rect1.height()*(1 - ratio));

    painter->setBrush(QColor(0, 170, 255, 100));
    painter->drawRect(rect2);
}

void MainWindow::onRight()
{
    movePlayer(GameObject::Right);
}

void MainWindow::onUp()
{
    movePlayer(GameObject::Up);
}

void MainWindow::onLeft()
{
    movePlayer(GameObject::Left);
}

void MainWindow::onDown()
{
    movePlayer(GameObject::Down);
}

void MainWindow::movePlayer(GameObject::Directions direction)
{
    m_game.movePlayer(direction);
}
