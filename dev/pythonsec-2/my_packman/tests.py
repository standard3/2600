import my_packman

test1 = my_packman.ushort_uint(b'\x01\x42\x00\x01\x02\x03\xde\xad')
assert test1 == (322, 66051)

test2 = my_packman.buf2latin(b'\x00\x04G\xE9g\xe9zzz')
assert test2 == (4, 'Gégé')

test3 = my_packman.ascii2buf("I", "like", "the", "game")
assert test3 == bytearray(b'\x00\x00\x00\x04\x00\x01I\x00\x04like\x00\x03the\x00\x04game')

test4 = my_packman.img2buf("./", "grayscale_bear_and_tiger.png")
#print(test4)

test5 = my_packman.buf2img(test4)
#print(test5)

test6 = my_packman.sample_method_grayrggb2img("./", "matrgb_bear_and_tiger.png")
