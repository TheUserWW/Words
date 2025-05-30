#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <QString>




// 定义语言枚举
enum Language {
    Chinese,
    English
};


extern Language currentLanguage; // 在main.cpp中定义

// 声明一个语言变化的信号，需要配合 Qt 的信号槽机制使用
extern void languageChanged();


namespace Translations {
    // 根据当前语言选择返回对应的翻译文本
    inline QString tr(const QString& chinese, const QString& english) {
        return currentLanguage == Chinese ? chinese : english;
    }

    // MainWindow
    // 将所有常量改为内联函数
    inline const QString& MAIN_WINDOW_TITLE() {
        static QString title = tr("单词学习", "Words");
        return title;
    }
    inline const QString& WORD_INPUT_PLACEHOLDER() {
        static QString placeholder = tr("输入单词", "Enter word");
        return placeholder;
    }
    inline const QString& MEANING_INPUT_PLACEHOLDER() {
        static QString placeholder = tr("输入词义", "Enter meaning");
        return placeholder;
    }
    inline const QString& ADD_BUTTON_TEXT() {
        static QString text = tr("添加", "Add");
        return text;
    }
    inline const QString& DELETE_BUTTON_TEXT() {
        static QString text = tr("删除选中单词", "Delete selected word");
        return text;
    }
    inline const QString& TEST_BUTTON_TEXT() {
        static QString text = tr("测试单词", "Test words");
        return text;
    }
    
    // Menu
    inline const QString& MENU_SETTINGS() {
        static QString text = tr("设置", "Settings");
        return text;
    }
    inline const QString& ACTION_SETTINGS() {
        static QString text = tr("设置", "Settings");
        return text;
    }
    inline const QString& ACTION_CHINESE() {
        static QString text = tr("中文", "Chinese");
        return text;
    }
    inline const QString& ACTION_ENGLISH() {
        static QString text = tr("English", "English");
        return text;
    }
    
    // TestDialog
    inline const QString& TEST_DIALOG_TITLE() {
        static QString text = tr("单词测试", "Word Test");
        return text;
    }
    inline const QString& SUBMIT_BUTTON_TEXT() {
        static QString text = tr("提交", "Submit");
        return text;
    }
    
    // 其他常量
    inline const QString& PLAY_PRONUNCIATION() {
        static QString text = tr("播放发音", "Play Pronunciation");
        return text;
    }
    inline const QString& FEMALE_VOICE() {
        static QString text = tr("女声", "Female Voice");
        return text;
    }
    inline const QString& MALE_VOICE() {
        static QString text = tr("男声", "Male Voice");
        return text;
    }
    inline const QString& WORD_COLUMN() {
        static QString text = tr("单词", "Word");
        return text;
    }
    inline const QString& MEANING_COLUMN() {
        static QString text = tr("词义", "Meaning");
        return text;
    }
    inline const QString& ACTION_COLUMN() {
        static QString text = tr("操作", "Action");
        return text;
    }
    inline const QString& EMPTY_WORD_LIST_WARNING() {
        static QString text = tr("单词列表为空，请先添加单词", "Word list is empty, please add words first");
        return text;
    }
    inline const QString& TEST_SETTINGS_TITLE() {
        static QString text = tr("测试设置", "Test Settings");
        return text;
    }
    inline const QString& TEST_MODE_GROUP() {
        static QString text = tr("测试模式", "Test Mode");
        return text;
    }
    inline const QString& WORD_TO_MEANING_MODE() {
        static QString text = tr("单词→词义", "Word→Meaning");
        return text;
    }
    inline const QString& MEANING_TO_WORD_MODE() {
        static QString text = tr("词义→单词", "Meaning→Word");
        return text;
    }
    inline const QString& START_TEST_BUTTON_TEXT() {
        static QString text = tr("开始测试", "Start Test");
        return text;
    }
    inline const QString& INSUFFICIENT_WORDS() {
        static QString text = tr("单词数量不足，至少需要4个单词", "Insufficient words, at least 4 words required");
        return text;
    }
    inline const QString& SELECT_ANSWER_PROMPT() {
        static QString text = tr("请选择一个答案", "Please select an answer");
        return text;
    }
    inline const QString& CORRECT_ANSWER() {
        static QString text = tr("回答正确!", "Correct answer!");
        return text;
    }
    inline const QString& WRONG_ANSWER() {
        static QString text = tr("回答错误! 正确答案是: %1", "Wrong answer! The correct answer is: %1");
        return text;
    }
    inline const QString& OPEN_CSV_DIALOG_TITLE() {
        static QString text = "打开CSV文件";
        return text;
    }
    inline const QString& FILE_OPEN_ERROR() {
        static QString text = "文件打开错误";
        return text;
    }
    inline const QString& FILE_OPEN_ERROR_MESSAGE() {
        static QString text = "无法打开文件，请检查文件是否存在或是否有权限访问";
        return text;
    }
    inline const QString& SAVE_CSV_DIALOG_TITLE() {
        static QString text = "保存CSV文件";
        return text;
    }
    inline const QString& FILE_SAVE_ERROR() {
        static QString text = "文件保存错误";
        return text;
    }
    inline const QString& FILE_SAVE_ERROR_MESSAGE() {
        static QString text = "无法保存文件，请检查路径是否有效";
        return text;
    }
    inline const QString& FILE_CREATE_ERROR() {
        static QString text = tr("文件创建错误", "File Creation Error");
        return text;
    }
    inline const QString& FILE_CREATE_ERROR_MESSAGE() {
        static QString text = tr("无法创建CSV文件", "Cannot create CSV file");
        return text;
    }
    inline const QString& ABOUT_TITLE() {
        static QString text = tr("关于", "About");
        return text;
    }
    inline const QString& SOFTWARE_TITLE() {
        static QString text = tr("Words", "Words");
        return text;
    }
    inline const QString& VERSION_TEXT() {
        static QString text = tr("版本: %1", "Version: %1");
        return text;
    }
    inline const QString& AUTHOR_HOMEPAGE() {
        static QString text = tr("作者主页", "Author Homepage");
        return text;
    }
    inline const QString& LICENSE_TEXT() {
        static QString text = tr("本软件使用GNU General Public License v3.0协议", 
                                "This software is licensed under GNU General Public License v3.0");
        return text;
    }

    inline const QString& FULL_LICENSE_TEXT() {
        static QString text = tr(
            "This program is free software: you can redistribute it and/or modify\n"
            "it under the terms of the GNU General Public License as published by\n"
            "the Free Software Foundation, either version 3 of the License, or\n"
            "(at your option) any later version.\n\n"
            "This program is distributed in the hope that it will be useful,\n"
            "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
            "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
            "GNU General Public License for more details.\n\n"
            "You should have received a copy of the GNU General Public License\n"
            "along with this program.  If not, see <https://www.gnu.org/licenses/>.",
            
            "本程序是自由软件：您可以自由地重新分发和/或修改\n"
            "根据自由软件基金会发布的GNU通用公共许可证的条款，\n"
            "许可证版本3，或（根据您的选择）任何更高版本。\n\n"
            "本程序分发是希望它有用，\n"
            "但没有任何担保；甚至没有适销性或特定用途适用性的默示担保。\n"
            "详情请参阅GNU通用公共许可证。\n\n"
            "您应该已经收到了一份GNU通用公共许可证的副本\n"
            "如果没有，请访问<https://www.gnu.org/licenses/>。"
        );
        return text;
    }
    inline const QString& GITHUB_TEXT() {
        static QString text = tr("TheUserWW", "Visit GitHub Homepage");
        return text;
    }
}

#endif // TRANSLATIONS_H
