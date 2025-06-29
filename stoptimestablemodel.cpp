#include "stoptimestablemodel.h"

StopTimesTableModel::StopTimesTableModel(const bht::Network& network, QObject *parent)
    : QAbstractTableModel(parent), network(network)
{
    headerFont.setBold(true);
    sequenceNumberFont.setItalic(true);
}

QVariant StopTimesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static std::string headerNames[] = {"Nr.", "Name Haltestelle", "Ankunszeit", "Abfahrtszeit"};

    // Ignore all other orientations besides horizontal
    if (orientation != Qt::Horizontal) {
        return QVariant();
    }

    // Return data matching the desired role
    if (role == Qt::FontRole) {
        // We want bold headers
        return headerFont;
    }
    else if (role == Qt::TextAlignmentRole) {
        // We want left alight, vertically centered headers
        return (int)(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole) {
        // Return header names
        return QString(headerNames[section].c_str());
    }
    else {
        return QVariant();
    }
}

int StopTimesTableModel::rowCount(const QModelIndex &) const
{
    return displayedStopTimes.size();
}

int StopTimesTableModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant StopTimesTableModel::data(const QModelIndex &index, int role) const
{
    // Return data matching the desired role
    if (role == Qt::FontRole) {
        // We want a special font for the sequence number
        return index.column() == 0 ? sequenceNumberFont : contentFont;
    }
    else if (role == Qt::TextAlignmentRole) {
        // We want left alight, vertically centered headers
        return (int)(Qt::AlignLeft | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole) {
        // Return cell data
        const bht::StopTime &item = displayedStopTimes[index.row()];
        switch (index.column()) {
        case 0:
            return QString::number(item.stopSequence);
        case 1:
            return QString(network.getStopById(item.stopId).name.c_str());
        case 2:
            return QString("%1:%2:%3")
                .arg(static_cast<int>(item.arrivalTime.hour), 2, 10, QLatin1Char('0'))
                .arg(static_cast<int>(item.arrivalTime.minute), 2, 10, QLatin1Char('0'))
                .arg(static_cast<int>(item.arrivalTime.second), 2, 10, QLatin1Char('0'));
        case 3:
        default:
            return QString("%1:%2:%3")
                .arg(static_cast<int>(item.departureTime.hour), 2, 10, QLatin1Char('0'))
                .arg(static_cast<int>(item.departureTime.minute), 2, 10, QLatin1Char('0'))
                .arg(static_cast<int>(item.departureTime.second), 2, 10, QLatin1Char('0'));
        }
    }
    else {
        return QVariant();
    }
}

void StopTimesTableModel::setDisplayedStopTimes(const std::vector<bht::StopTime>& data) {
    beginResetModel();
    displayedStopTimes = data;
    endResetModel();
}

void StopTimesTableModel::clear() {
    beginResetModel();
    displayedStopTimes.clear();
    endResetModel();
}