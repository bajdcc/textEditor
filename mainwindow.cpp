#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new TextEditor(this);
    this->setCentralWidget(textEdit);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    setWindowIcon(QIcon(":/images/fileIcon.png"));
    this->setCurrentFile("");
    this->resize(500, 300);
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::newFile()
{
    if(okToContinue())
    {
        textEdit->clear();
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if(okToContinue())
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open MainWindow"), ".",
                                                        tr("All types (*.*);;"
                                                           "Normal text file (*.txt);;"
                                                           "C++ source file (*.h;*.hpp;*.hxx;*.cpp;*.cxx;*.cc)"));
        if(!fileName.isEmpty())
        {
            loadFile(fileName);
        }
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save TextEditor"), ".",
                                                    tr("Normal text file (*.txt);;"
                                                        "C++ source file (*.cpp)"));
    if(fileName.isEmpty())
    {
        return false;
    }
    return saveFile(fileName);
}

void MainWindow::find()
{

}


void MainWindow::cut()
{

}

void MainWindow::copy()
{

}

void MainWindow::paste()
{

}

void MainWindow::deleteText()
{

}

void MainWindow::selectAll()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, QStringLiteral("关于 MainWindow"),
            QStringLiteral("<h2>MainWindow 1.0</h2>"
               "<p>Copyright &copy; 2018 SouthEast University."
               "<p>MainWindow是一个用来展示QAction, QMainWindow, QMenuBar, "
               "QStatusBar, QTableWidget, QToolBar以及其他Qt类用法"
               "<p>本软件仅用来交流讨论，有任何好的建议欢迎联系QQ:1030460698。"));
}

void MainWindow::createActions()
{
    newAction = new QAction(QStringLiteral("新建(&N)"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(QStringLiteral("新建一个文件"));
    connect(newAction, &QAction::triggered,
            this, &MainWindow::newFile);

    openAction = new QAction(QStringLiteral("打开(&O)"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(QStringLiteral("打开一个文件"));
    connect(openAction, &QAction::triggered,
            this, &MainWindow::open);

    saveAction = new QAction(QStringLiteral("保存(&S)"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("保存文件");
    connect(saveAction, &QAction::triggered,
            this, &MainWindow::save);

    saveAsAction = new QAction(QStringLiteral("另存为(&A)..."), this);
    saveAsAction->setStatusTip(QStringLiteral("将文件另存为..."));
    connect(saveAsAction, &QAction::triggered,
            this, &MainWindow::saveAs);

    exitAction = new QAction(QStringLiteral("关闭"), this);
    exitAction->setShortcut(QStringLiteral("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程序"));
    connect(exitAction, &QAction::triggered,
            this, &MainWindow::close);

    cutAction = new QAction(QStringLiteral("剪切(&T)"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(QStringLiteral("剪切文本"));
    connect(cutAction, &QAction::triggered,
            this, &MainWindow::cut);

    copyAction = new QAction(QStringLiteral("复制(&C)"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(QStringLiteral("复制文本"));
    connect(copyAction, &QAction::triggered,
            this, &MainWindow::copy);

    pasteAction = new QAction(QStringLiteral("粘贴(&P)"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(QStringLiteral("粘贴文本"));
    connect(pasteAction, &QAction::triggered,
            this, &MainWindow::paste);

    deleteAction = new QAction(QStringLiteral("删除(&D)"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(QStringLiteral("删除所选文本"));
    connect(deleteAction, &QAction::triggered,
            this, &MainWindow::deleteText);

    selectAllAction = new QAction(QStringLiteral("全选(&L)"), this);
    selectAllAction->setStatusTip(QStringLiteral("全选文本"));
    connect(selectAllAction, &QAction::triggered,
            this, &MainWindow::selectAll);

    findAction = new QAction(QStringLiteral("查找(&F)..."), this);
    findAction->setStatusTip(QStringLiteral("查找文本"));

    fullScreenAction = new QAction(QStringLiteral("切换全屏模式"), this);
    fullScreenAction->setShortcut(QKeySequence::FullScreen);
    fullScreenAction->setStatusTip(QStringLiteral("全屏显示"));

    optionAction = new QAction(QStringLiteral("首选项..."), this);
    optionAction->setStatusTip(QStringLiteral("配置程序"));

    md5Action = new QAction(QStringLiteral("MD5"), this);
    md5Action->setStatusTip(QStringLiteral("MD5校验"));

    updateAction = new QAction(QStringLiteral("升级 MainWindow"), this);
    updateAction->setStatusTip(QStringLiteral("升级应用程序"));

    aboutAction = new QAction(QStringLiteral("关于 MainWindow..."), this);
    aboutAction->setStatusTip(QStringLiteral("显示应用的相关信息"));
    connect(aboutAction, &QAction::triggered,
            this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    // 文件菜单
    fileMenu = menuBar()->addMenu(QStringLiteral("文件(&F)"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    fileMenu->addSeparator();

    fileMenu->addAction(exitAction);

    // 编辑菜单
    editMenu = menuBar()->addMenu(QStringLiteral("编辑(&E)"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);
    editMenu->addAction(selectAllAction);

    // 搜索菜单
    searchMenu = menuBar()->addMenu(QStringLiteral("搜索(&S)"));
    searchMenu->addAction(findAction);

    // 视图菜单
    viewMenu = menuBar()->addMenu(QStringLiteral("视图(&V)"));
    viewMenu->addAction(fullScreenAction);

    // 设置菜单
    settingsMenu = menuBar()->addMenu(QStringLiteral("设置(&T)"));
    settingsMenu->addAction(optionAction);

    // 工具菜单
    toolsMenu = menuBar()->addMenu(QStringLiteral("工具(&O)"));
    toolsMenu->addAction(md5Action);

    // 帮助菜单
    helpMenu = menuBar()->addMenu(QStringLiteral("帮助(&H)"));
    helpMenu->addAction(updateAction);
    helpMenu->addAction(aboutAction);
}

void MainWindow::createContextMenu()
{
    textEdit->addAction(copyAction);
    textEdit->addAction(cutAction);
    textEdit->addAction(pasteAction);
    textEdit->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(QStringLiteral("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(QStringLiteral("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    // 如果有icon的话，显示图标；否则显示文字
    //editToolBar->addAction(selectAllAction);
}

void MainWindow::createStatusBar()
{
    showLabel = new QLabel(QStringLiteral("Normal text file"));
    showLabel->setAlignment(Qt::AlignLeft);
    showLabel->setMinimumSize(showLabel->sizeHint());

    statusBar()->addWidget(showLabel);
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = QStringLiteral("new");

    if(!curFile.isEmpty())
    {
        curFile.replace('/', '\\');
        shownName = curFile;
    }

    setWindowTitle(QStringLiteral("%1[*] - %2")
                   .arg(shownName)
                   .arg(QStringLiteral("TextEditor")));
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int res = QMessageBox::warning(this, QStringLiteral("MainWindow"),
                                       QStringLiteral("The text has been modified.\n"
                                          "Do you want to save your changes?"),
                                       QMessageBox::Yes | QMessageBox::No
                                       | QMessageBox::Cancel);
        if(res == QMessageBox::Yes)
        {
            return save();
        }
        else if(res == QMessageBox::Cancel)
        {
            return false;
        }
    }
    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if(!textEdit->readFile(fileName))
    {
        statusBar()->showMessage(QStringLiteral("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(QStringLiteral("File loaded"), 2000);
    return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!textEdit->writeFile(fileName))
    {
        statusBar()->showMessage(QStringLiteral("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(QStringLiteral("File saved"), 2000);
    return true;
}

// 取文件名  eg:C:/test/test.txt  --->  test.txt
QString MainWindow::strippedName(const QString &fileName)
{
    return QFileInfo(fileName).fileName();
}















