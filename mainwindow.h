#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "network.h"
#include "stoptimestablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_searchTextEdit_textChanged();

    void on_routeComboBox_currentIndexChanged(int index);

    void on_tripComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    /// The network we fetched
    bht::Network myNetwork;

    /// Model for displayed routes
    QStringListModel routesModel;

    /// Model for displayed trips
    QStringListModel tripsModel;

    /// Model for displayed stop times
    StopTimesTableModel stopTimesModel;

    /// Shown routes with route id and to route display name pairs
    std::vector<std::pair<std::string, std::string>> routes;

    /// Shown trips with trip id and to trip display name pairs
    std::vector<std::pair<std::string, std::string>> trips;

    /**
     * @brief getStringListForDisplayNames Extract display names from the second item out of a vector of pairs
     * @param items Vector of pairs where the second item is the display name
     * @return Resulting string list
     */
    QStringList getStringListForDisplayNames(const std::vector<std::pair<std::string, std::string>>& items);

    /**
     * @brief updateStopTimesTable Update the displayed items in the stop times table
     * @param needle Search word to apply for filtering
     * @param tripId Currently selected trip id
     */
    void updateStopTimesTable(std::string needle, std::string tripId);
};
#endif // MAINWINDOW_H