#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DiagramItem.hpp"

#include <QMainWindow>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QButtonGroup;
class QLineEdit;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();

private slots:
    void backgroundButtonGroupClicked(QAbstractButton *button);
    void buttonGroupClicked(QAbstractButton *button);
    void deleteItem();
    void pointerGroupClicked();
    void bringToFront();
    void sendToBack();
    void itemInserted(DiagramItem *item);
    void sceneScaleChanged(const QString &scale);
    void about();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    QWidget *createBackgroundCellWidget(const QString &text,
                                        const QString &image);
    QWidget *createCellWidget(const QString &text, DiagramItem::DiagramType type);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *editToolBar;
    QToolBar *pointerToolbar;

    QComboBox *sceneScaleCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QAction *fillAction;
    QAction *lineAction;
};

#endif // MAINWINDOW_H
