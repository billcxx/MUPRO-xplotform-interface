#ifndef READIMAGE_H
#define READIMAGE_H

#include <QDialog>

namespace Ui {
class readImage;
}

class readImage : public QDialog
{
    Q_OBJECT

public:
    explicit readImage(QWidget *parent = 0);
    ~readImage();

private:
    Ui::readImage *ui;
};

#endif // READIMAGE_H
