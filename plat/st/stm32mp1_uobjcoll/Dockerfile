##############################################################################
#
# uberSpark bridge docker container template
#
##############################################################################

##############################################################################
# basic distro and maintainer -- CUSTOMIZABLE
##############################################################################

FROM amd64/ubuntu:20.04
LABEL maintainer="Amit Vasudevan <amitvasudevan@acm.org>" author="Ethan Joseph <ethanj217@gmail.com>"


##############################################################################
# required boilerplate commands below -- DO NOT CHANGE
##############################################################################

ENV DEBIAN_FRONTEND=noninteractive

# runtime arguments
ENV D_CMD=/bin/bash
ENV D_UID=1000
ENV D_GID=1000

# switch to root
USER root

# update apt packages, install sudo, and select non-interactive mode
RUN apt-get update -y &&\
    apt-get install -y --no-install-recommends apt-utils &&\
    apt-get install -y sudo &&\
    echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# create user uberspark and group uberspark so we have access to /home/uberspark
RUN addgroup --system uberspark &&\
    adduser --system --disabled-password --ingroup uberspark uberspark &&\
    usermod -aG sudo uberspark &&\
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

##############################################################################
# bridge specific installation commands -- CUSTOMIZABLE
# note: must remove any pre-defined user the FROM image may come
# with so that we don't conflict on uid/gid mappings. i.e., the
# container should only contain users root and uberspark 
##############################################################################

RUN apt-get update && \
    apt-get -yqq install build-essential \
    git libssl-dev bc \
    device-tree-compiler flex bison \
    gcc-10-arm-linux-gnueabihf \
    gcc-10-multilib-arm-linux-gnueabihf \
	binutils-arm-linux-gnueabihf && \
    apt-get clean && rm -rf /var/lib/apt/lists/* && \
    apt-get upgrade gcc

RUN ln -s /usr/arm-linux-gnueabi/libhf/ld-linux-armhf.so.3 /lib/ld-linux-armhf.so.3 && \
    ln -s /usr/arm-linux-gnueabihf/lib/libc.so.6 /usr/lib/libc.so.6 && \
    ln -s /usr/bin/arm-linux-gnueabihf-gcc-10 /usr/bin/arm-linux-gnueabihf-gcc && \
    ln -s /usr/bin/arm-linux-gnueabihf-cpp-10 /usr/bin/arm-linux-gnueabihf-cpp

##############################################################################
# entry point and permissions biolerplate -- DO NOT CHANGE
##############################################################################

# drop back to root
USER root

# change permissions of /home/uberspark so everyone can access it
WORKDIR "/home/uberspark"
RUN chmod ugo+rwx -R .

# setup entry point script that switches user uid/gid to match host
COPY ./docker-entrypoint-ubuntu.sh /docker-entrypoint-ubuntu.sh
RUN chmod +x /docker-entrypoint-ubuntu.sh

# invoke the entrypoint script which will adjust uid/gid and invoke d_cmd with d_cmdargs as user uberspark
CMD /docker-entrypoint-ubuntu.sh ${D_UID} ${D_GID} ${D_CMD}

