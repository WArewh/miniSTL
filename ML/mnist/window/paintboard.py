import sys
from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPixmap, QPainter, QPen, QColor
from PyQt5.QtCore import Qt, QPoint, QSize


class PaintBoard(QWidget):
    def __init__(self, Parent=None, Size=QSize(231, 231), Fill=QColor(0, 0, 0, 255)):
        super().__init__(Parent)

        self.size = Size
        self.fill = Fill

        self.thickness = 16
        self.penColor = QColor(255, 255, 255, 255)

        self.begin_point = QPoint()
        self.end_point = QPoint()

        self.board = QPixmap(self.size)
        self.board.fill(Fill)
        self.setFixedSize(self.size)
        self.painter = QPainter()

    def getImage(self):
        return self.board.toImage()

    # 清空画板
    def clear(self):
        self.board.fill(self.fill)
        self.update()

    # 双缓冲绘图，绘图事件
    def paintEvent(self, paintEvent):
        self.painter.begin(self)
        self.painter.drawPixmap(0, 0, self.board)
        self.painter.end()

    def mousePressEvent(self, mouseEvent):
        if mouseEvent.button() == Qt.LeftButton:
            self.begin_point = mouseEvent.pos()
            self.end_point = self.begin_point

    def mouseMoveEvent(self, mouseEvent):
        if mouseEvent.buttons() == Qt.LeftButton:
            self.end_point = mouseEvent.pos()

            # 画入缓冲区
            self.painter.begin(self.board)
            self.painter.setPen(QPen(self.penColor, self.thickness))
            self.painter.drawLine(self.begin_point, self.end_point)
            self.painter.end()

            self.begin_point = self.end_point
            self.update()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = PaintBoard()
    demo.show()
    sys.exit(app.exec_())
