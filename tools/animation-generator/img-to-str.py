from pathlib import Path
import sys
from PIL import Image
import numpy as np

if len(sys.argv) != 2:
    print("Not like this :<")
    print("Usage: python img-to-str.py input.png ")
    sys.exit(1)

input_filename = sys.argv[1]

# Load the PNG image
img = Image.open(input_filename)

# Convert the image to grayscale
img = img.convert("L")

# Resize the image to 16x16
img = img.resize((16, 16))

# Convert the image data to a 16x16 array of pixel values
pixel_data = np.array(img.getdata()).reshape((16, 16))

# Convert each pixel value to a 4-bit number
pixel_data_4bit = np.right_shift(pixel_data, 4).astype(np.uint8)

# Convert the array to a hexadecimal string
hex_string = "".join(format(x, "X") for x in pixel_data_4bit.flatten())

print(f'"{Path(input_filename).stem}": "{hex_string}"')
