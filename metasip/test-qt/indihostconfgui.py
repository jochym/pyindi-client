#!/usr/bin/env python
# coding=UTF-8
#
# Generated by pykdeuic4 from indihostconf.ui on Sun Jan 13 18:30:31 2013
#
# WARNING! All changes to this file will be lost.
from PyKDE4 import kdecore
from PyKDE4 import kdeui
from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_INDIHostConf(object):
    def setupUi(self, INDIHostConf):
        INDIHostConf.setObjectName(_fromUtf8("INDIHostConf"))
        INDIHostConf.resize(437, 178)
        INDIHostConf.setSizeGripEnabled(True)
        self.vboxlayout = QtGui.QVBoxLayout(INDIHostConf)
        self.vboxlayout.setSpacing(6)
        self.vboxlayout.setMargin(11)
        self.vboxlayout.setObjectName(_fromUtf8("vboxlayout"))
        self.hboxlayout = QtGui.QHBoxLayout()
        self.hboxlayout.setSpacing(6)
        self.hboxlayout.setMargin(0)
        self.hboxlayout.setObjectName(_fromUtf8("hboxlayout"))
        self.vboxlayout1 = QtGui.QVBoxLayout()
        self.vboxlayout1.setSpacing(6)
        self.vboxlayout1.setMargin(0)
        self.vboxlayout1.setObjectName(_fromUtf8("vboxlayout1"))
        self.textLabel1_3 = QtGui.QLabel(INDIHostConf)
        self.textLabel1_3.setObjectName(_fromUtf8("textLabel1_3"))
        self.vboxlayout1.addWidget(self.textLabel1_3)
        self.textLabel1 = QtGui.QLabel(INDIHostConf)
        self.textLabel1.setObjectName(_fromUtf8("textLabel1"))
        self.vboxlayout1.addWidget(self.textLabel1)
        self.textLabel1_2 = QtGui.QLabel(INDIHostConf)
        self.textLabel1_2.setObjectName(_fromUtf8("textLabel1_2"))
        self.vboxlayout1.addWidget(self.textLabel1_2)
        self.hboxlayout.addLayout(self.vboxlayout1)
        self.vboxlayout2 = QtGui.QVBoxLayout()
        self.vboxlayout2.setSpacing(6)
        self.vboxlayout2.setMargin(0)
        self.vboxlayout2.setObjectName(_fromUtf8("vboxlayout2"))
        self.nameIN = KLineEdit(INDIHostConf)
        self.nameIN.setObjectName(_fromUtf8("nameIN"))
        self.vboxlayout2.addWidget(self.nameIN)
        self.hostname = KLineEdit(INDIHostConf)
        self.hostname.setObjectName(_fromUtf8("hostname"))
        self.vboxlayout2.addWidget(self.hostname)
        self.portnumber = KLineEdit(INDIHostConf)
        self.portnumber.setObjectName(_fromUtf8("portnumber"))
        self.vboxlayout2.addWidget(self.portnumber)
        self.hboxlayout.addLayout(self.vboxlayout2)
        self.vboxlayout.addLayout(self.hboxlayout)
        spacerItem = QtGui.QSpacerItem(30, 35, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.vboxlayout.addItem(spacerItem)
        self.hboxlayout1 = QtGui.QHBoxLayout()
        self.hboxlayout1.setSpacing(6)
        self.hboxlayout1.setMargin(0)
        self.hboxlayout1.setObjectName(_fromUtf8("hboxlayout1"))
        spacerItem1 = QtGui.QSpacerItem(20, 20, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Minimum)
        self.hboxlayout1.addItem(spacerItem1)
        self.buttonOk = QtGui.QPushButton(INDIHostConf)
        self.buttonOk.setAutoDefault(True)
        self.buttonOk.setDefault(True)
        self.buttonOk.setObjectName(_fromUtf8("buttonOk"))
        self.hboxlayout1.addWidget(self.buttonOk)
        self.buttonCancel = QtGui.QPushButton(INDIHostConf)
        self.buttonCancel.setAutoDefault(True)
        self.buttonCancel.setObjectName(_fromUtf8("buttonCancel"))
        self.hboxlayout1.addWidget(self.buttonCancel)
        self.vboxlayout.addLayout(self.hboxlayout1)

        self.retranslateUi(INDIHostConf)
        QtCore.QObject.connect(self.buttonOk, QtCore.SIGNAL(_fromUtf8("clicked()")), INDIHostConf.accept)
        QtCore.QObject.connect(self.buttonCancel, QtCore.SIGNAL(_fromUtf8("clicked()")), INDIHostConf.reject)
        QtCore.QMetaObject.connectSlotsByName(INDIHostConf)
        INDIHostConf.setTabOrder(self.nameIN, self.hostname)
        INDIHostConf.setTabOrder(self.hostname, self.portnumber)
        INDIHostConf.setTabOrder(self.portnumber, self.buttonOk)
        INDIHostConf.setTabOrder(self.buttonOk, self.buttonCancel)

    def retranslateUi(self, INDIHostConf):
        self.textLabel1_3.setText(kdecore.i18n(_fromUtf8("Name:")))
        self.textLabel1.setText(kdecore.i18n(_fromUtf8("Host:")))
        self.textLabel1_2.setText(kdecore.i18n(_fromUtf8("Port:")))
        self.buttonOk.setText(kdecore.i18n(_fromUtf8("&OK")))
        self.buttonCancel.setText(kdecore.i18n(_fromUtf8("&Cancel")))

from PyKDE4.kdeui import KLineEdit
