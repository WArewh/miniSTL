# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file './window/trainlayout.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(400, 300)
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(80, 70, 101, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.batch_text = QtWidgets.QLineEdit(Form)
        self.batch_text.setGeometry(QtCore.QRect(180, 70, 131, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.batch_text.setFont(font)
        self.batch_text.setObjectName("batch_text")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(80, 120, 101, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.epoch_text = QtWidgets.QLineEdit(Form)
        self.epoch_text.setGeometry(QtCore.QRect(180, 120, 131, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.epoch_text.setFont(font)
        self.epoch_text.setObjectName("epoch_text")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(80, 170, 101, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.learning_rate_text = QtWidgets.QLineEdit(Form)
        self.learning_rate_text.setGeometry(QtCore.QRect(180, 170, 131, 31))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.learning_rate_text.setFont(font)
        self.learning_rate_text.setObjectName("learning_rate_text")
        self.submit_button = QtWidgets.QPushButton(Form)
        self.submit_button.setGeometry(QtCore.QRect(80, 240, 93, 28))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.submit_button.setFont(font)
        self.submit_button.setObjectName("submit_button")
        self.return_button = QtWidgets.QPushButton(Form)
        self.return_button.setGeometry(QtCore.QRect(220, 240, 93, 28))
        font = QtGui.QFont()
        font.setFamily("Consolas")
        font.setPointSize(12)
        self.return_button.setFont(font)
        self.return_button.setObjectName("return_button")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.label.setText(_translate("Form", "训练批次："))
        self.label_2.setText(_translate("Form", "训练轮次："))
        self.label_3.setText(_translate("Form", "学习率："))
        self.submit_button.setText(_translate("Form", "提交"))
        self.return_button.setText(_translate("Form", "返回"))

