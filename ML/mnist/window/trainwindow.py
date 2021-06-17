import sys

from PyQt5.QtWidgets import QMainWindow, QApplication, QMessageBox

from window.trainlayout import Ui_Form


class TrainWindow(QMainWindow, Ui_Form):
    def __init__(self):
        super(TrainWindow, self).__init__()
        self.setupUi(self)

    def getParameter(self):
        batch_size = self.getBatchParameter()
        epoch = self.getEpochParameter()
        learning_rate = self.getLearningRateParameter()
        return batch_size, epoch, learning_rate

    def getBatchParameter(self):
        try:
            batch_size = int(self.batch_text.text())
            if batch_size < 0:
                raise
            return batch_size
        except:
            QMessageBox.information(self, '提示', '请在批次中输入正整数')
            return None

    def getEpochParameter(self):
        try:
            epoch = int(self.epoch_text.text())
            if epoch < 0:
                raise
            return epoch
        except:
            QMessageBox.information(self, '提示', '请在轮次中输入正整数')
            return None

    def getLearningRateParameter(self):
        try:
            lr = float(self.learning_rate_text.text())
            if lr < 0:
                raise
            return lr
        except:
            QMessageBox.information(self, '提示', '请在学习率上输入正浮点数')
            return None

