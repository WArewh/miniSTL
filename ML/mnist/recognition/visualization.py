from PIL import Image
import numpy as np


def image_show(bytes, path):
    bytes = [int(str(byte).encode('ascii'), 16) for byte in bytes]
    pixels = np.array(bytes, dtype=np.uint8).reshape(28, 28)
    image = Image.fromarray(pixels).convert('L')
    image.save(path)
