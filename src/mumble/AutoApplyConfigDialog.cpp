// Copyright The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

#include "AutoApplyConfigDialog.h"
#include "Global.h"

AutoApplyConfigDialog::AutoApplyConfigDialog(QWidget *p) : ConfigDialog(p) {
    // Connect the timer to our slot
    connect(&m_autoApplyTimer, &QTimer::timeout, this, &AutoApplyConfigDialog::onAutoApplyTimer);
    
    // Start the timer when the dialog is shown
    connect(this, &QDialog::showEvent, [this](QShowEvent *) {
        m_autoApplyTimer.start(AUTO_APPLY_INTERVAL_MS);
    });
    
    // Stop the timer when the dialog is hidden
    connect(this, &QDialog::hideEvent, [this](QHideEvent *) {
        m_autoApplyTimer.stop();
    });
}

AutoApplyConfigDialog::~AutoApplyConfigDialog() {
    m_autoApplyTimer.stop();
}

void AutoApplyConfigDialog::onAutoApplyTimer() {
    // Only apply if the dialog is visible
    if (isVisible()) {
        apply();
    }
} 