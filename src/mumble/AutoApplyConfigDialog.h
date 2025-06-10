// Copyright The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#ifndef MUMBLE_MUMBLE_AUTOAPPLYCONFIGDIALOG_H_
#define MUMBLE_MUMBLE_AUTOAPPLYCONFIGDIALOG_H_

#include "ConfigDialog.h"
#include <QTimer>

class AutoApplyConfigDialog : public ConfigDialog {
    Q_OBJECT
private:
    QTimer m_autoApplyTimer;
    static const int AUTO_APPLY_INTERVAL_MS = 5000; // 5 seconds

public:
    AutoApplyConfigDialog(QWidget *p = nullptr);
    ~AutoApplyConfigDialog() Q_DECL_OVERRIDE;

private slots:
    void onAutoApplyTimer();
};

#endif 