import threading

from PyQt5.QtWidgets import QMessageBox

from window.mainwindow import MainWindow


class Controller:
    def __init__(self):
        self.main_win = MainWindow()

        self.main_win.quit_button.clicked.connect(self.main_win.close)

        self.main_win.train_win.return_button.clicked.connect(self.main_win.train_win.close)
        self.main_win.train_win.submit_button.clicked.connect(self.modifyParameterAndTrain)

    def modifyParameterAndTrain(self):
        is_train = False
        batch_size, epoch, learning_rate = self.main_win.train_win.getParameter()
        if batch_size is not None and \
                epoch is not None and \
                learning_rate is not None:
            self.main_win.train_config['batch_size'] = batch_size
            self.main_win.train_config['n_epochs'] = epoch
            self.main_win.train_config['learning_rate'] = learning_rate
            QMessageBox.information(self.main_win, '提示', '修改成功')
            self.main_win.train_win.close()
            is_train = True
        threading.Thread(target=self.main_win.trainModel, args=(is_train,)).start()

    def run(self):
        self.main_win.show()
