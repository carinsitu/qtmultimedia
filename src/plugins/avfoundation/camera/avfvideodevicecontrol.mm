/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "avfcameradebug.h"
#include "avfvideodevicecontrol.h"
#include "avfcameraservice.h"

QT_USE_NAMESPACE

AVFVideoDeviceControl::AVFVideoDeviceControl(AVFCameraService *service, QObject *parent)
   : QVideoDeviceSelectorControl(parent)
   , m_service(service)
   , m_selectedDevice(0)
   , m_dirty(true)
   , m_defaultDevice(0)
{
    AVCaptureDevice *defaultDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    NSArray *videoDevices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    int i = 0;
    for (AVCaptureDevice *device in videoDevices) {
        m_devices << QString::fromUtf8([[device uniqueID] UTF8String]);
        m_deviceDescriptions << QString::fromUtf8([[device localizedName] UTF8String]);
        if (defaultDevice && [[device uniqueID] isEqualToString:[defaultDevice uniqueID]])
            m_defaultDevice = i;
        ++i;
    }
}

AVFVideoDeviceControl::~AVFVideoDeviceControl()
{
}

int AVFVideoDeviceControl::deviceCount() const
{
    return m_devices.size();
}

QString AVFVideoDeviceControl::deviceName(int index) const
{
    return m_devices[index];
}

QString AVFVideoDeviceControl::deviceDescription(int index) const
{
    return m_deviceDescriptions[index];
}

int AVFVideoDeviceControl::defaultDevice() const
{
    return m_defaultDevice;
}

int AVFVideoDeviceControl::selectedDevice() const
{
    return m_selectedDevice;
}

void AVFVideoDeviceControl::setSelectedDevice(int index)
{
    if (index != m_selectedDevice) {
        m_dirty = true;
        m_selectedDevice = index;
        Q_EMIT selectedDeviceChanged(index);
        Q_EMIT selectedDeviceChanged(m_devices[index]);
    }
}

AVCaptureDevice *AVFVideoDeviceControl::createCaptureDevice()
{
    m_dirty = false;
    AVCaptureDevice *device = 0;

    if (!m_devices.isEmpty()) {
        QString deviceId = m_devices.at(m_selectedDevice);

        device = [AVCaptureDevice deviceWithUniqueID:
                    [NSString stringWithUTF8String:
                        deviceId.toUtf8().constData()]];
    }

    if (!device)
        device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];

    return device;
}

#include "moc_avfvideodevicecontrol.cpp"
