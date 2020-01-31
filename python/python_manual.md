xillybus.py manual
=====

This module makes it easy to access an FPGA connected by PCI-Express using Xillybus.

# Examples
You can use this class to access an FPGA device connected by PCIe like below.

```python:Example.py
from xillybus import *

# For 32 bit Xillybus.
# If the device file path is different with default one,
# you have to set the arguments for this function.
fpga = Xillybus32()

# If you want 8 bit Xillybus, use below.
# fpga = Xillybus8()

# Send a data.
# You have to use integer type only.
to_fpga = 10
fpga.write(to_fpga)

# Read the data from FPGA.
# If there is nothing to send on the FPGA,
# this function never returns any value.
from_fpga = fpga.read()
```