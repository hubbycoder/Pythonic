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

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

/*
 * Every Method call: debug
 * Signals Slots: Info
 */



int main(int argc, char *argv[])
{
    // https://doc.qt.io/qt-5/qtglobal.html#qSetMessagePattern
    qSetMessagePattern("%{type} : %{function}() - %{message}");
    // https://doc.qt.io/qt-5/qloggingcategory.html
    QLoggingCategory::setFilterRules(QStringLiteral(
                                                    "debug=true\n"
                                                    "info=true\n"

                                                    /* Miscellaneous */

                                                    "Logger.debug=true\n"
                                                    "Logger.info=false\n"
                                                    "Logger.warning=true\n"
                                                    "Logger.critical=true\n"

                                                    "FileDownloader.debug=false\n"
                                                    "FileDownloader.info=false\n"

                                                    /* GUI Elements */

                                                    "MainWindow.debug=true\n"
                                                    "MainWindow.info=false\n"

                                                    "WorkingArea.debug=true\n"
                                                    "WorkingArea.info=true\n"

                                                    "Toolbox.debug=true\n"
                                                    "Toolbox.info=true\n"

                                                    "MenuBar.debug=true\n"
                                                    "MenuBar.info=true\n"

                                                    /* GUI Buttons */

                                                    "MenuBar.NewFileBtn.debug=true\n"
                                                    "MenuBar.NewFileBtn.info=true\n"

                                                    "MenuBar.OpenFileBtn.debug=false\n"
                                                    "MenuBar.OpenFileBtn.info=false\n"

                                                    "MenuBar.SaveBtn.debug=false\n"
                                                    "MenuBar.SaveBtn.info=false\n"

                                                    "MenuBar.SaveAsBtn.debug=false\n"
                                                    "MenuBar.SaveAsBtn.info=false\n"

                                                    "MenuBar.KillProcBtn.debug=false\n"
                                                    "MenuBar.KillProcBtn.info=false\n"

                                                    "MenuBar.StopExecBtn.debug=false\n"
                                                    "MenuBar.StopExecBtn.info=false\n"

                                                    "MenuBar.StartDebugBtn.debug=false\n"
                                                    "MenuBar.StartDebugBtn.info=false\n"

                                                    "MenuBar.RunBtn.debug=false\n"
                                                    "MenuBar.RunBtn.info=false\n"

                                                    /* Toolbox elements */

                                                    "BasicTools.debug=true\n"
                                                    "BasicTools.info=true\n"

                                                    /* Master Classes */

                                                    "BaseLabel.debug=false\n"
                                                    "BaseLabel.info=false\n"

                                                    "BaseButton.debug=false\n"
                                                    "BaseButton.info=false\n"

                                                    "ElementIconBar.debug=false\n"
                                                    "ElementIconBar.info=false\n"

                                                    "ToolMaster.debug=true\n"
                                                    "ToolMaster.info=true\n"

                                                    "ElementMaster.debug=false\n"
                                                    "ElementMaster.info=false\n"

                                                    /* Element Buttons  */

                                                    "EditElementBtn.debug=false\n"
                                                    "EditElementBtn.info=false\n"

                                                    "DebugElementBtn.debug=false\n"
                                                    "DebugElementBtn.info=false\n"

                                                    "DeleteElementBtn.debug=false\n"
                                                    "DeleteElementBtn.info=false\n"

                                                    /* Elements */

                                                    "StartElement.debug=false\n"
                                                    "StartElement.info=false\n"

                                                    "PlaceholderElement.debug=true\n"
                                                    "PlaceholderElement.info=true\n"

                                                    ));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
