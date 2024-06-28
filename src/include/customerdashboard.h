#ifndef CUSTOMERDASHBOARD_H
#define CUSTOMERDASHBOARD_H

#include <QMainWindow>
#include "commonincludes.h"

namespace Ui {
class customerdashboard;
}

class customerdashboard : public QMainWindow {
    Q_OBJECT

public:
    explicit customerdashboard(QWidget *parent = nullptr);
    ~customerdashboard();

private:
    Ui::customerdashboard *ui;
};

#endif // CUSTOMERDASHBOARD_H
