/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qffmpegmediadevices_p.h"
#include "qmediadevices.h"
#include <private/qcameradevice_p.h>

#include "qffmpeg_p.h"

#include <qdebug.h>


QT_BEGIN_NAMESPACE

QFFmpegMediaDevices::QFFmpegMediaDevices(QPlatformMediaIntegration *integration)
    : QPlatformMediaDevices(integration)
{
    qDebug() << "QFFMpegMediaDevices constructor";
    avdevice_register_all();
}

QList<QAudioDevice> QFFmpegMediaDevices::audioInputs() const
{
    QList<QAudioDevice> devices;

    qDebug() << "listing audio inputs:";
    AVInputFormat *device = nullptr;
    while ((device = av_input_audio_device_next(device))) {
        auto *d = new QCameraDevicePrivate;
        d->id = device->name;
        d->description = QString::fromUtf8(device->long_name);
        AVDeviceInfoList *deviceList = nullptr;
        int nInputs = avdevice_list_input_sources(device, nullptr, nullptr, &deviceList);
        if (nInputs >= 0 && deviceList && deviceList->nb_devices) {
            qDebug() << "    " << device->name << device->long_name << nInputs;
            qDebug() << "    devices:";
            for (int i = 0; i < deviceList->nb_devices; ++i) {
                auto info = deviceList->devices[i];
                qDebug() << info->device_name << info->device_description;
            }
        }
    }

    return devices;
}

QList<QAudioDevice> QFFmpegMediaDevices::audioOutputs() const
{
    QList<QAudioDevice> devices;

    qDebug() << "listing audio outputs:";
    AVOutputFormat *device = nullptr;
    while ((device = av_output_audio_device_next(device))) {
        auto *d = new QCameraDevicePrivate;
        d->id = device->name;
        d->description = QString::fromUtf8(device->long_name);
        AVDeviceInfoList *deviceList = nullptr;
        int nInputs = avdevice_list_output_sinks(device, nullptr, nullptr, &deviceList);
        if (nInputs >= 0 && deviceList && deviceList->nb_devices) {
            qDebug() << "    " << device->name << device->long_name << nInputs;
            qDebug() << "    devices:";
            for (int i = 0; i < deviceList->nb_devices; ++i) {
                auto info = deviceList->devices[i];
                qDebug() << info->device_name << info->device_description;
            }
        }
    }

    return devices;
}

QList<QCameraDevice> QFFmpegMediaDevices::videoInputs() const
{
    QList<QCameraDevice> devices;

    qDebug() << "listing video inputs:";
    AVInputFormat *device = nullptr;
    while ((device = av_input_video_device_next(device))) {
        auto *d = new QCameraDevicePrivate;
        d->id = device->name;
        d->description = QString::fromUtf8(device->long_name);
        AVDeviceInfoList *deviceList = nullptr;
        int nInputs = avdevice_list_input_sources(device, nullptr, nullptr, &deviceList);
        if (nInputs >= 0 && deviceList && deviceList->nb_devices) {
            qDebug() << "    " << device->name << device->long_name << nInputs;
            qDebug() << "    devices:";
            for (int i = 0; i < deviceList->nb_devices; ++i) {
                auto info = deviceList->devices[i];
                qDebug() << info->device_name << info->device_description;
            }
        }
    }

    return devices;
}

QPlatformAudioSource *QFFmpegMediaDevices::createAudioSource(const QAudioDevice &/*deviceInfo*/)
{
    return nullptr;//new QFFmpegAudioSource(deviceInfo);
}

QPlatformAudioSink *QFFmpegMediaDevices::createAudioSink(const QAudioDevice &/*deviceInfo*/)
{
    return nullptr;//new QFFmpegAudioSink(deviceInfo);
}

QT_END_NAMESPACE
