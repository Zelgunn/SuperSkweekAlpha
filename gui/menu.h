#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QStringList>
#include <QDomElement>

class Menu : public QObject
{
    Q_OBJECT

public:
    enum MenuType {
        SimpleMenu,
        OptionMenu,
        HostGame,
        LocalGame,
        IPGame,
        Tutorial
    };

    Menu(Menu *parent = Q_NULLPTR);
    Menu(const QDomElement &element, Menu *parent = Q_NULLPTR);

    QStringList menusNames() const;
    Menu *menuAt(int index) const;

    QString name() const;
    void setName(const QString &name);

    // Options
    bool isBackMenu() const;
    bool isExitMenu() const;
    bool hasOption(const QString &name);
    bool hasOptions() const;
    void setOptions(const QList<QDomElement> &options);
    void setOption(const QString &name, const QString &value);

    // Multijoueur
    bool isHostGame() const;
    bool isLocalGame() const;
    bool isIPGame() const;

    void appendMenu(Menu *child);
    static Menu *createBackMenu(Menu *parent);
    static Menu *createExitMenu(Menu *parent);

    uint selectedMenu() const;
    void setSelectedMenu(const uint &selectedMenu);
    void selectAboveMenu();
    void selectBelowMenu();

    QList<Menu *> subMenus() const;
    QList<QDomElement> options() const;

    Menu *parent() const;

    MenuType type() const;

protected:
    void defineType();

private:
    QDomElement m_baseElement;
    QList<QDomElement> m_options;
    MenuType m_type;
    Menu *m_parent;
    QString m_name;
    QList<Menu *> m_subMenus;
    int m_selectedMenu;
};

#endif // MENU_H
