from xillybus import *
import numpy as np

fpga = Xillybus32()
to_fpga = 10
fpga.write(to_fpga)

from_fpga = fpga.read()
print(from_fpga)

x = np.array([[1, 2, 3], [4, 5, 6]], dtype='i4')
print(x)
fpga.write_ndarray(x)

y = fpga.read_ndarray(24)
print(y)
print(y.reshape(2, 3))
