#include "mainwindow.h"

#include <QApplication>
#include "translations.h"
#include <QTranslator>

// 初始化语言变量
Language currentLanguage = Chinese; // 默认中文

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    

    MainWindow w;
    w.show();
    return a.exec();
}
