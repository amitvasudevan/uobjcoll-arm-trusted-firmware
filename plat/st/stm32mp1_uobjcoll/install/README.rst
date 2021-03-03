Populate SD-card
-----------------

The SD-card has to be formated with GPT. It should contain at least these partitions:
* fsbl: to copy the `tf-a-stm32mp157c-ev1.stm32` binary
* ssbl: to copy the `u-boot.stm32` binary

Guide adapted from https://trustedfirmware-a.readthedocs.io/en/latest/plat/stm32mp1.html
