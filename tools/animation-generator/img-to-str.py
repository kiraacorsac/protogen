from pathlib import Path
import sys
from PIL import Image
import numpy as np
import json

if len(sys.argv) != 2:
    print("Not like this :<")
    print("Usage: python img-to-str.py folder_path ")
    sys.exit(1)

folder_path = sys.argv[1]

# Get a list of all the image files in the folder
image_files = [f for f in Path(folder_path).iterdir(
) if f.is_file() and f.suffix in {'.jpg', '.jpeg', '.png', '.bmp'}]

# Create an empty dictionary to store the results
result_dict = {}

# Create an empty dictionary to store the color palette
color_palette = {}

# Keep track of the number of colors encountered
num_colors = 0

# Loop through all the image files
for input_filename in image_files:

    # Load the image
    img = Image.open(input_filename)

    # Convert the image to RGB
    img = img.convert("RGB")

    # Resize the image to 16x16
    img = img.resize((16, 16))

    # Convert the image data to a 16x16 array of RGB values
    pixel_data = np.array(img.getdata()).reshape((16, 16, 3))

    # Create an empty array to store the 4-bit pixel data
    pixel_data_4bit = np.zeros((16, 16), dtype=np.uint8)

    # Loop through all the pixels and add them to the color palette if they are not already in it
    for i in range(16):
        for j in range(16):
            color = tuple(pixel_data[i, j])
            if color not in color_palette:
                if num_colors >= 16:
                    raise ValueError("Too many colors encountered")
                color_palette[color] = num_colors
                num_colors += 1
            pixel_data_4bit[i, j] = color_palette[color]

    # Convert the array to a hexadecimal string
    hex_string = "".join(format(x, "X") for x in pixel_data_4bit.flatten())

    # Add the result to the dictionary
    result_dict[Path(input_filename).stem] = hex_string

# Convert the color palette to JSON
color_palette_json = json.dumps({format(value, "X"): {
                                "r": int(color[0]), "g": int(color[1]), "b": int(color[2])} for color, value in color_palette.items()})

# Output the color palette and dictionary as JSON strings
print("Color palette:\n" + color_palette_json)
print("Result dictionary:\n" + json.dumps(result_dict))
