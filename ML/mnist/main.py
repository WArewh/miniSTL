import sys
from PyQt5.QtWidgets import QApplication
from window.controller import Controller

if __name__ == "__main__":
    app = QApplication(sys.argv)
    controller = Controller()
    controller.run()
    sys.exit(app.exec_())
