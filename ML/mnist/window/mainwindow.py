import threading
import time
from math import exp

import torch
import torch.nn as nn

from PyQt5.QtWidgets import QMainWindow, QFileDialog
from PyQt5.QtGui import QPixmap

from PIL import ImageQt, Image
from torchvision import transforms

from window.mainlayout import Ui_Form
from window.paintboard import PaintBoard
from window.trainwindow import TrainWindow
from recognition.model import DigitClassifier
from recognition.mnist import customize_train


class MainWindow(QMainWindow, Ui_Form):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setupUi(self)

        self.clear_button.clicked.connect(self.clearDataArea)
        self.choose_model_button.clicked.connect(self.chooseModel)
        self.choose_image_button.clicked.connect(self.chooseImage)
        self.choose_paint_button.clicked.connect(self.choosePaint)
        self.recognition_button.clicked.connect(self.recognitionImage)
        self.train_button.clicked.connect(self.chooseTrain)
        self.save_button.clicked.connect(self.chooseSave)

        self.train_config = {
            'batch_size': 16,
            'n_epochs': 12,
            'learning_rate': 0.001,
            'device': torch.device('cuda' if torch.cuda.is_available() else 'cpu'),
            'optimizer': 'Adam',
            'criterion': nn.CrossEntropyLoss(),
            'model_path': './test/models/default.pth',
        }

        self.transform = transforms.Compose([
            transforms.ToTensor(),
            transforms.Normalize((0.1307,), (0.3081,))
        ])

        self.model = DigitClassifier()
        self.model.load_state_dict(torch.load(self.train_config['model_path']))
        self.model.eval()

        self.paintboard = PaintBoard()
        self.data_area.addWidget(self.paintboard)
        self.area_state = True  # 画板1 图片0

        self.train_win = TrainWindow()

    def clearDataArea(self):
        self.result_area.clear()
        self.image_area.clear()
        self.paintboard.clear()

    def chooseModel(self):
        model_path, _ = QFileDialog.getOpenFileName(self, '打开模型', './test/models', 'model (*.pth)')
        if model_path != '':
            self.model.load_state_dict(torch.load(model_path))
            self.model.eval()

    def chooseImage(self):
        self.area_state = False
        self.clearDataArea()
        self.image_area.raise_()
        self.paintboard.lower()
        image_path, _ = QFileDialog.getOpenFileName(self, '打开图片', './test/images', 'image (*.jpg)')
        if image_path != '':
            image = QPixmap(image_path).scaled(231, 231)
            self.image_area.setPixmap(image)

    def choosePaint(self):
        self.area_state = True
        self.clearDataArea()
        self.paintboard.raise_()
        self.image_area.lower()

    def chooseTrain(self):
        self.train_win.show()

    def trainModel(self, is_train: bool):
        if is_train:
            cur_time = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
            self.train_config['model_path'] = r'./test/models/{}.pth'.format(cur_time)
            self.train_button.setEnabled(False)
            self.train_button.setText('训练中...')
            customize_train(self.train_config)
            self.train_button.setText('训练模型')
            self.train_button.setEnabled(True)

    def chooseSave(self):
        threading.Thread(target=self.saveImage).start()

    def saveImage(self):
        image = self.loadImage()
        pred, _ = self.getPredition(image)
        cur_time = time.strftime("%Y-%m-%d-%H-%M-%S", time.localtime())
        image_path = r'./test/images/{}.jpg'.format(cur_time + '_' + str(pred))
        image.save(image_path, quality=100)

    def loadImage(self):
        if self.area_state:  # 画板
            image = self.paintboard.getImage()
        else:  # 图片
            image = self.image_area.pixmap().toImage()

        image = ImageQt.fromqimage(image)
        return image

    def getPredition(self, image):
        image = image.resize((28, 28), Image.ANTIALIAS).convert('L')
        image = transforms.ToTensor()(image).reshape(1, 1, 28, 28)  # batch channel H W

        output = self.model(image)
        pred_val, pred = output.max(1, keepdim=True)

        output = output.detach().numpy().tolist()[0]
        exp_output = [exp(val) for val in output]
        prob = exp(pred_val) / sum(exp_output)
        return pred.item(), prob

    def recognitionImage(self):
        image = self.loadImage()
        image = image.resize((28, 28), Image.ANTIALIAS).convert('L')
        pred, prob = self.getPredition(image)
        self.probability_text.setText('输出概率为:%.3f' % prob)
        self.result_area.setText(str(pred))
