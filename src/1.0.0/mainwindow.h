#ifndef MAINWINDOW_H  // 确保与下面的#define一致
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextToSpeech>
#include <QStandardItemModel>
#include <QTextToSpeech>
#include <QMessageBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QApplication>
#include <QStyle>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTranslator>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QTranslator>
#include <QStyledItemDelegate>
#include "translations.h"  // 包含翻译相关功能的头文件

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief 主窗口类，负责单词学习应用的主要界面和功能
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT  // Qt元对象系统宏，启用信号槽机制

public:
    explicit MainWindow(QWidget *parent = nullptr);
    
    /**
     * @brief 析构函数
     */
    ~MainWindow();

private slots:
    void loadCSV();  // 从CSV文件加载单词数据
    void saveCSV();  // 保存单词数据到CSV文件
    void on_addButton_clicked();  // 添加按钮点击槽函数
    void on_playButton_clicked();  // 播放按钮点击槽函数
    void playPronunciation(int row);  // 播放指定行单词的发音
    void on_deleteButton_clicked();  // 删除按钮点击槽函数
    void on_actionSettings_triggered();  // 设置菜单项触发槽函数
    void on_actionEnglish_triggered();  // 切换英文界面槽函数
    void on_actionChinese_triggered();  // 切换中文界面槽函数
    void retranslateUi();  // 重新翻译界面文本
    void on_testButton_clicked();  // 测试按钮点击槽函数
    void changeLanguage(const QString &language);  // 添加这行声明

signals:
    void languageChanged();  // 添加这行信号声明

private:
    Ui::MainWindow *ui;  // UI界面指针
    QStandardItemModel *model;  // 表格数据模型
    QTextToSpeech *speech;  // 文本转语音引擎
    QTranslator *m_translator;  // 添加翻译器指针成员变量
    QAction *actionVoice1;  // 语音1选项
    QAction *actionVoice2;  // 语音2选项
};

/**
 * @brief 自定义表格项委托类，用于在表格中绘制按钮
 */
class ButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针
     */
    explicit ButtonDelegate(QObject *parent = nullptr);
    
    /**
     * @brief 绘制表格项
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    
    /**
     * @brief 处理表格项编辑事件
     */
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void playButtonClicked(int row);  // 播放按钮点击信号
    void themeChanged(bool darkMode);  // 主题变更信号
};
#endif // MAINWINDOW_H
