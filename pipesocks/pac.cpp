/*
This file is part of pipesocks. Pipesocks is a pipe-like SOCKS5 tunnel system.
Copyright (C) 2016  yvbbrjdr

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "pac.h"

PAC::PAC(qintptr handle,QObject *parent):QObject(parent) {
    csock=new TcpSocket;
    connect(csock,SIGNAL(RecvData(QByteArray)),this,SLOT(RecvData(QByteArray)));
    connect(csock,SIGNAL(disconnected()),this,SLOT(EndSession()));
    csock->setSocketDescriptor(handle);
    cthread=new QThread(csock);
    csock->moveToThread(cthread);
    cthread->start();
}

void PAC::RecvData(const QByteArray &Data) {

}

void PAC::EndSession() {
    emit csock->Disconnect();
    cthread->exit();
    cthread->wait();
    csock->deleteLater();
    deleteLater();
}