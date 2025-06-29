#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#ifndef GTFS_DIRECTORY_PATH
#error "Setzen Sie den Pfad zu Ihrem GTFS-Verzeichnis in Zeile 5 in config.h und kommentieren Sie die Zeile ein"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myNetwork(GTFS_DIRECTORY_PATH)
    , stopTimesModel(myNetwork, this)
{
    ui->setupUi(this);
    setWindowTitle(WINDOW_TITLE);

    // Assign models to elements
    ui->routeComboBox->setModel(&routesModel);
    ui->tripComboBox->setModel(&tripsModel);
    ui->stopTimeTableView->setModel(&stopTimesModel);

    // Setup displayed routes
    for (auto &item : myNetwork.getRoutes()) {
        std::string displayName = myNetwork.getRouteDisplayName(item);
        routes.push_back(std::make_pair(item.id, displayName));
    }

    // Sort the results by name
    std::sort(routes.begin(),
              routes.end(),
              [](const std::pair<std::string, std::string>& a, const std::pair<std::string, std::string>& b) {
                  return a.second < b.second;
              }
    );
    routesModel.setStringList(getStringListForDisplayNames(routes));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchTextEdit_textChanged()
{
    // Skip on inactive UI
    if (!ui->searchTextEdit->isEnabled()) {
        return;
    }

    // Update table
    int index = ui->tripComboBox->currentIndex();
    std::string tripId = trips[index].first;
    updateStopTimesTable(ui->searchTextEdit->toPlainText().toStdString(), tripId);
}

void MainWindow::on_routeComboBox_currentIndexChanged(int index) {
    std::string routeId = routes[index].first;

    // Find trips for the selected route
    auto tripsForRoute = myNetwork.getTripsForRoute(routeId);
    trips.clear();
    for (auto &item : tripsForRoute) {
        std::string displayName = myNetwork.getTripDisplayName(item);
        trips.push_back(std::make_pair(item.id, displayName));
    }

    ui->searchTextEdit->setEnabled(false);
    ui->searchTextEdit->clear();
    ui->stopTimeTableView->setEnabled(false);
    stopTimesModel.clear();

    // Enable UI
    ui->tripComboBox->clear();
    ui->tripComboBox->setEnabled(true);
    tripsModel.setStringList(getStringListForDisplayNames(trips));
}

void MainWindow::on_tripComboBox_currentIndexChanged(int index) {
    // Skip on inactive UI
    if (!ui->tripComboBox->isEnabled()) {
        return;
    }

    // Clear search field
    ui->searchTextEdit->clear();

    // Update table
    std::string tripId = trips[index].first;
    updateStopTimesTable("", tripId);
}

void MainWindow::updateStopTimesTable(std::string needle, std::string tripId) {
    const auto& stopTimes = myNetwork.searchStopTimesForTrip(needle, tripId);
    stopTimesModel.setDisplayedStopTimes(stopTimes);
    ui->searchTextEdit->setEnabled(true);
    ui->stopTimeTableView->setEnabled(true);
    ui->stopTimeTableView->resizeColumnsToContents();
}

QStringList MainWindow::getStringListForDisplayNames(const std::vector<std::pair<std::string, std::string>>& items) {
    QStringList result;
    for (auto &item : items) {
        result << QString(item.second.c_str());
    }
    return result;
}