#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Homepage : public QWidget
{
    Q_OBJECT
public:
    explicit Homepage(QWidget *parent = nullptr);

private:
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QPushButton *ctaButton;  // Call-to-Action button
};

#endif // HOMEPAGE_H
