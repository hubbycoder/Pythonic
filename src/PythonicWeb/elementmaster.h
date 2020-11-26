/*
 * This file is part of Pythonic.

 * Pythonic is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Pythonic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Pythonic. If not, see <https://www.gnu.org/licenses/>
 */

#ifndef ELEMENTMASTER_H
#define ELEMENTMASTER_H

#include <QWidget>
#include <QLoggingCategory>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPair>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QSizePolicy>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QStringLiteral>
#include <QMoveEvent>
#include <QSet>
#include "baselabel.h"

#define LABEL_SIZE QSize(140, 47)
#define PLUG_SOCKET_SIZE QSize(47, 47)



struct ChildConfig {
    bool bottomChild;
    bool rightChild;
};

/*! @brief ElementMaster is the base widget for all programming elements
 *
 *  Detailed description follows here.
 *  @author Stephan Avenwedde
 *  @date October 2020
 *  @copyright [GPLv3](../../../LICENSE)
 */


class ElementSocket : public BaseLabel
{
    Q_OBJECT
public:
    explicit ElementSocket(QWidget *parent = nullptr)
        : BaseLabel(QUrl("http://localhost:7000/PlugSocket.png"), PLUG_SOCKET_SIZE, parent)
        , m_connected(false)
    {
        qCDebug(logC, "called");
    };

public slots:

    void connected(bool connectionState);


protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    bool                m_connected;
    QLoggingCategory    logC{"ElementSocket"};
};


class ElementPlug : public BaseLabel
{
    Q_OBJECT
public:
    explicit ElementPlug(QWidget *parent = nullptr)
        : BaseLabel(QUrl("http://localhost:7000/PlugSocket.png"), PLUG_SOCKET_SIZE, parent)
        , m_connected(false)
    {
        qCDebug(logC, "called");
        setContextMenuPolicy(Qt::CustomContextMenu);
    };

public slots:

    void connected(bool connectionState);

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    bool                m_connected;
    QLoggingCategory    logC{"ElementPlug"};
};


class ElementStart : public BaseLabel
{
    Q_OBJECT
public:
    explicit ElementStart(QWidget *parent = nullptr)
        : BaseLabel(QUrl("http://localhost:7000/PlayDefault.png"), PLUG_SOCKET_SIZE, parent)
        , m_running(false)
    {
        qCDebug(logC, "called");
        setContextMenuPolicy(Qt::CustomContextMenu);
    };

    void togggleRunning(bool running);
    bool m_running;

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:

    QLoggingCategory    logC{"ElementPlug"};
};

struct Version {
    int     major;
    int     minor;
};


class ElementMaster : public QWidget
{
    Q_OBJECT
public:

    explicit ElementMaster(
            bool socket,
            bool plug,
            QUrl pixMapPath,
            QString objectName,
            QString filename,
            Version version,
            Version pythonicVersion,
            QString author,
            QString license,
            int gridNo,
            QWidget *parent = nullptr);

    /* Element Configuration */

    //! Unique 32 bit id of each element, automatic set (CONFIG)
    quint32                 m_id;
    //! Indicates if elements accept parent connections
    bool                    m_hasSocket;
    //! Filename for the related Python file (CONFIG)
    QString                 m_filename;
    //! Version of the element: Major:Minor (CONFIG)
    Version                 m_version;
    //! Related version of Pythonic: Major:Minor (CONFIG)
    Version                 m_pythonicVersion;
    //! Author of the element (CONFIG)
    QString                 m_author;
    //! License of the element (CONFIG)
    QString                 m_license;
    //! Number of the grid which holds the element
    int                     m_gridNo;

    //! Debugging is only available in MP mode (CONFIG)
    bool                    m_bDebug{false};
    //! Multiprocessing - if no, the element uses multithreading (CONFIG)
    bool                    m_bMP{false};
    //! Indicates if element should print the output when done (CONFIG)
    bool                    m_showOutput{false};


    /* Internal Configuration */

    //! Indicates if the element has a parent element
    bool                    m_parentConnected{false};
    //! Indicates if the element has a child element
    bool                    m_childConnected{false};

    QSet<ElementMaster*>    m_parents;
    QSet<ElementMaster*>    m_childs;

    //! Generate and return configuration
    QJsonObject             genConfig() const;

    void                    addParent(ElementMaster *parent);
    void                    addChild(ElementMaster *child);

public slots:

    void                    stopHighlight();
    void                    startHighlight();
    void                    checkConnectionState();

signals:

    void remove(ElementMaster *element);
    void plugConnectionHighlight(bool state);
    void socketConnectionHighlight(bool state);


private slots:

    void deleteSelf();
    //void playBtnClicked // on release

private:

    QLoggingCategory        logC{"ElementMaster"};

    //! Layout for IconBar and ElementPicture
    QVBoxLayout             m_layout;
    //! Holds label and position text
    QWidget                 m_innerWidget;
    //! Layout for position-text
    QVBoxLayout             m_innerWidgetLayout;

    QWidget                 m_symbolWidget;
    //! Layout for symbol, socket and plug
    QHBoxLayout             m_symbolWidgetLayout;

public:
    //! Symbol of element
    BaseLabel               m_symbol;
    //! Connector icon
    ElementSocket           m_socket;
    //! Plug icon
    ElementPlug             m_plug;
    //! Start button
    ElementStart            m_startBtn;

private:
    //! Label of the element
    QLabel                  m_labelText{"labe text"};
    //! Backend-configuration of the element
    QJsonObject             m_config;

    QSizePolicy             m_sizePolicy{QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum};


};

// https://stackoverflow.com/questions/2562176/storing-a-type-in-c



#endif // ELEMENTMASTER_H
