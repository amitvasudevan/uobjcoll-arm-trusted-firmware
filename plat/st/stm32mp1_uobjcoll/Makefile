#   trustzone firmware Makefile refactored to use the überSpark next-gen toolkit
#   
#   author: ethan joseph <ethanj217@gmail.com>
#

.PHONY: all
all:
	@echo building stm32 collection...
	uberspark staging switch stm32mp1 
	uberspark uobjcoll build -v --platform=st --arch=armv8_32 --cpu=generic .
	@echo built stm32 collection successfully!

.PHONY: stage
stage:
	@echo creating staging
	uberspark staging create stm32mp1 
	# uberspark staging config-set --setting-name=uobjcoll_binary_image_load_address --setting-value=0x06200000
	# uberspark staging config-set --setting-name=uobj_binary_image_size --setting-value=0x14900000
	uberspark staging config-set --root-dir=/home/yeeb16 --setting-name=bridge_cc_bridge --setting-value=container/amd64/cc-bridge/armv8_32/generic/gcc/v5.4.0


	uberspark staging config-set --root-dir=/home/yeeb16 --setting-name=as_bridge_namespace --setting-value=uberspark/bridges/container/amd64/as-bridge/armv8_32/generic/gnu-as/v2.26.1
	uberspark staging config-set --root-dir=/home/yeeb16 --setting-name=ld_bridge_namespace --setting-value=uberspark/bridges/container/amd64/ld-bridge/armv8_32/generic/gnu-ld/v2.26.1
	@echo staging created successfully!

.PHONY: clean
clean: 
	rm -rf _build
