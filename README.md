Gatherer app
============================

This application is made during the Google Summer of Code (GSoC) 2014. It can be used to gather information following a certain template. These templates are stored on a server. The observations can be shown on a map, saved locally and uploaded to the server again.

The app is designed for android and currently only for a Nexus 4 (768 x 1280 pixels).

The (technical) documentation can be found in the wiki.

Project info
============================
This project has three blogposts:
* Startup of GSoC: http://blog.52north.org/2014/05/28/ilwis-mobile-app/
* Mid-term of GSoC: http://blog.52north.org/2014/07/03/ilwis-mobile-midterm-blog/
* End of GSoC: http://blog.52north.org/2014/08/22/ilwis-mobile-final-blog/

The app needs a server to provide the templates an other data. The server code can be foud here: https://github.com/52North/IlwisConnectors/tree/master/gatherer

There is a screencast of the app on youtube:
https://www.youtube.com/watch?v=spc_dXwLOWw

How to use
============================
This application is coded in C++ with QT. QT can be downloaded from http://qt-project.org/downloads and information how to set it up for android can be found at http://qt-project.org/doc/qt-5/androidgs.html.
Open the gatherer.pro file with QT creator to start working.

Licence
============================
This code is published under the General Public Licence Version 2.
It makes use of the following QT classes which fall under the GNU Lesser General Public License version 2.1:
- QFile
- QObject
- QDirIterator
- QTextStream
- QDebug
- QNetworkReply
- QQuickView
- QQmlListProperty
- QList
- QImage
- QXmlStreamReader
- QtQuick/QQuickView
- QApplication
- QtQml
- QQmlComponent
- QQmlContext
- QtQml/QQmlApplicationEngine

And QML:
- QtQuick 2.2
- QtQuick.Controls 1.1
- QtQuick.Dialogs 1.1
- QtPositioning 5.2
- QtQuick.Controls.Styles 1.1
- QtQuick.Layouts 1.1

For details see the LICENSE file.
