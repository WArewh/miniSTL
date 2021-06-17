import torch.nn as nn


class DigitClassifier(nn.Module):
    def __init__(self):
        super().__init__()
        self.cnn_layers = nn.Sequential(
            nn.Conv2d(1, 32, (5, 5)),  # 24*24
            nn.ReLU(),
            nn.MaxPool2d(2, 2, 0),  # 12*12
            nn.ReLU(),
            nn.Conv2d(32, 64, (3, 3)),  # 10*10
            nn.ReLU(),
            nn.Conv2d(64, 64, (3, 3)),  # 8*8
            nn.ReLU(),
            nn.Conv2d(64, 64, (3, 3)),  # 6*6
            nn.ReLU(),
            nn.Conv2d(64, 128, (3, 3)),  # 4*4
            nn.ReLU(),
        )

        self.fc_layers = nn.Sequential(
            nn.Linear(128 * 4 * 4, 512),
            nn.Dropout(0.1),
            nn.ReLU(),
            nn.Linear(512, 128),
            nn.ReLU(),
            nn.Linear(128, 10)
        )

        self.act_fn = nn.LogSoftmax(dim=1)

    def forward(self, x):
        x = self.cnn_layers(x)
        x = x.flatten(1)
        x = self.fc_layers(x)
        x = self.act_fn(x)
        return x
