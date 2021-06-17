from torchvision import transforms
from torch.utils.data import DataLoader
from torchvision.datasets import MNIST

from recognition.training import train_model
from recognition.settings import setup_seed
from recognition.model import DigitClassifier


def customize_train(config):
    print('start model training')
    setup_seed(10000)

    transform = transforms.Compose([
        transforms.ToTensor(),
        transforms.Normalize((0.1307,), (0.3081,))
    ])

    train_set = MNIST('./recognition/', train=True, download=True, transform=transform)
    val_set = MNIST('./recognition/', train=False, download=True, transform=transform)

    train_loader = DataLoader(train_set, config['batch_size'], shuffle=True)
    val_loader = DataLoader(val_set, config['batch_size'], shuffle=True)

    model = DigitClassifier().to(config['device'])
    train_model(model, train_loader, val_loader, config)
