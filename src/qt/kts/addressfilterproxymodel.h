// Copyright (c) 2019 The KTS developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTS_CORE_NEW_GUI_ADDRESSFILTERPROXYMODEL_H
#define KTS_CORE_NEW_GUI_ADDRESSFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "addresstablemodel.h"


class AddressFilterProxyModel final : public QSortFilterProxyModel
{
    const QString m_type;

public:
    AddressFilterProxyModel(const QString& type, QObject* parent)
            : QSortFilterProxyModel(parent)
            , m_type(type) {
        setDynamicSortFilter(true);
        setFilterCaseSensitivity(Qt::CaseInsensitive);
        setSortCaseSensitivity(Qt::CaseInsensitive);
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex& parent) const override;
};


#endif //KTS_CORE_NEW_GUI_ADDRESSFILTERPROXYMODEL_H
