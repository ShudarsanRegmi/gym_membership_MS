#include "homepage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QSpacerItem>

Homepage::Homepage(QWidget *parent) : QWidget(parent) {
    // Main layout for the homepage
    QVBoxLayout *homePageLayout = new QVBoxLayout(this);

    // Hero section
    QLabel *heroImageLabel = new QLabel(this);
    QPixmap heroImage(":assets/images/gym0.jpg");  // Replace with your actual image path
    heroImageLabel->setPixmap(heroImage.scaled(1500, 1500, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    heroImageLabel->setAlignment(Qt::AlignCenter);  // Center the image

    QLabel *homePageTitle = new QLabel("Welcome to the Gym Membership Management System", this);
    homePageTitle->setStyleSheet(
        "font-size: 28px;"
        "font-weight: bold;"
        "color: #2C3E50;"
        "margin-bottom: 20px;"
        "text-align: center;"

        );
    homePageTitle->setAlignment(Qt::AlignCenter);  // Center the title

    QLabel *subTitle = new QLabel("Manage your memberships, track your attendance, and much more!", this);
    subTitle->setStyleSheet(
        "font-size: 18px;"
        "color: #34495E;"
        "margin-bottom: 40px;"
        );
    subTitle->setAlignment(Qt::AlignCenter);  // Center the subtitle

    // Call to action button
    QPushButton *ctaButton = new QPushButton("Get Started", this);
    ctaButton->setFixedSize(200, 70);
    ctaButton->setStyleSheet(
        "background-color: #1ABC9C;"
        "color: white;"
        "font-size: 18px;"
        "border-radius: 20px;"
        "margin-bottom: 30px;"
        );
    ctaButton->setCursor(Qt::PointingHandCursor);

    // Spacer item to push the content up if needed
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Add widgets to the layout
    homePageLayout->addWidget(homePageTitle);
    homePageLayout->addWidget(subTitle);
    homePageLayout->addWidget(heroImageLabel);
    homePageLayout->addItem(spacer);
    homePageLayout->addWidget(ctaButton, 0, Qt::AlignCenter);
    homePageLayout->addItem(spacer);

    // Apply the layout
    setLayout(homePageLayout);
}
