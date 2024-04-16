import struct
import numpy
import imageio.v2 as iio
import PIL

from typing import Tuple, List

def ushort_uint(buffer: bytes) -> Tuple[int, int]:
    """
    Extrait un entier court non signé en big endian, suivi
    d'un entier 32 bit non-signé en big endian
    """
    fmt_unsigned_16bit_be = ">H"
    fmt_unsigned_32bit_be = ">I"

    a = struct.unpack_from(fmt_unsigned_16bit_be, buffer, 0)
    b = struct.unpack_from(fmt_unsigned_32bit_be, buffer, 2)

    return a + b

def buf2latin(buffer: bytes) -> Tuple[int, str]:
    """
    Extrait la taille de la chaîne de caractère ISO Latin 1
    et la chaîne qui suit
    """
    # get buffer len
    length = struct.unpack_from(">H", buffer, 0)[0]

    # unpack string
    nb_bytes_size = 2
    string = buffer[nb_bytes_size:nb_bytes_size + length].decode("latin-1")

    return (length, string)

def ascii2buf(*args) -> bytearray:
    """
    Prend un nombre variable de params et les transforme en
    buffer tel que :
    * en premier nous avons le nombre d'élements total dans
      le buffer (entier non signé 32 bit)
    * ensuite chaque chaîne est concaténée et est préfixée
      par sa taille (entier non signé 16 bit)
    """
    res = bytearray()
    res += struct.pack(">I", len(args)) # total elements in buffer

    for s in args:
        s_size = len(s)
        res += struct.pack(">h", s_size) # size of current element

        for c in s: # current element
            res += struct.pack("c", c.encode("latin-1")) # encode and pack each char

    return res

def img2buf(path: str, filename: str) -> bytearray:
    """
    Convertit une image grayscale et retourne un buffer tel
    que :
    1. la hauteur de l'image (big-endian unsigned short)
    2. la largeur (big-endian unsigned short)
    3. valeur des pixels de l'image (big-endian unsigned short)
    4. nom du fichier
    """
    image = iio.imread(f'{path}{filename}')
    height, width = image.shape

    res = bytearray()

    # Height and width
    res += struct.pack(">HH", height, width)

    # Image pixels value
    res += image.tobytes()

    # Filename
    for c in filename:
        res += struct.pack("c", c.encode("latin-1")) # encode and pack each char

    return res

def buf2img(buffer: bytearray) -> numpy.ndarray:
    """
    Retourne un array à 2d à partir du buffer produit par img2buf()
    """
    height, width = struct.unpack(">HH", buffer[:4])

    filename = buffer[struct.calcsize(">HH") + (height * width):]

    packed_image = buffer[4:-len(filename)]
    deserialized_image = PIL.Image.frombytes("L", (height, width), packed_image) # L for grayscale image (https://stackoverflow.com/a/52307690)
    image = numpy.reshape(deserialized_image, (height, width))

    return image

def sample_method_grayrggb2img(path: str, filename: str) -> numpy.ndarray:
    """
    Traite une image grayscale par copie pixels voisins pour y ajouter
    des couleurs et retourne un array 3d
    """

    image = iio.imread(f"{path}{filename}")
    height, width, depth = image.shape

    rgb_array = numpy.zeros(
        (height, width, depth),
        dtype=numpy.uint8
    )

    for i in range(height):
        for j in range(width):
            # red
            if i % 2 == 0 and j % 2 == 0:
                rgb_array[i, j, 0] = image[i, j][0]

            # blue
            elif i % 2 == 1 and j % 2 == 1:
                rgb_array[i, j, 2] = image[i, j][2]

            # green
            else:
                rgb_array[i, j, 1] = numpy.mean(
                    [ image[i - 1, j],
                      image[i, j - 1] ]
                )

    return rgb_array
