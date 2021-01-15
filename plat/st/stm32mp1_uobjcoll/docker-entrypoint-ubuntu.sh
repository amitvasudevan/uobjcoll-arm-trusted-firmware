#!/bin/sh

# author: Amit Vasudevan <amitvasudevan@acm.org>

# turn off command echo; use -x for debugging
set +x

# if we are running as root then drop to user uberspark
if [ "$(id -u)" = "0" ]; then
    #grab host uid and gid passed to us via command line parameters
    uid=$1
    gid=$2

    #debug
        #uname=`id -u -n`
        #echo "ROOT; username: $uname"
        #echo "parameters: $@"
        #echo "UID to set= $uid"
        #echo "GID to set= $gid"

    # revise parameters by removing the uid and gid from command line
    shift 2

    #debug
        #echo "revised parameters: $@"

    
    # get rid of existing uberspark user
    deluser uberspark

    # add new uberspark group and user with host uid and gid
    addgroup --gid $gid --system uberspark
    adduser --uid $uid --no-create-home --system --disabled-password --ingroup uberspark uberspark &&\
    usermod -aG sudo uberspark 

    # drop to user uberspark and execute this script with the remaining parameters
    sudo -u uberspark /docker-entrypoint-ubuntu.sh $@

   
else
    # now we are run as user uberspark, so execute the command
    temp=$@

    #debug
        #echo "temporary value: $temp"

    # remove leading and trailing double quotes if any
    # this can happen when we pass environment variables via exec system calls
    parm="${temp%\"}"
    parm="${parm#\"}"
    
    #parm=$temp

    #debug
        #uname=`id -u -n`
        #echo "NON-ROOT; username: $uname"
        #echo "parameters: $parm"

    opam_present=`command -v opam`
    if [ -z "$opam_present" ]
    then 
        echo No opam detected. Skipping opam initialization...
    else
        opam switch 4.09.0+flambda
        eval $(opam env)
    fi

    # execute the command and actual parameters as user uberspark
    
    exec /bin/sh -c "$parm"

fi


