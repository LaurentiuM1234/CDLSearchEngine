#! /bin/bash


STATUS_LIBGTK=$(dpkg-query -W --showformat='${Status}\n' libgtk-3-dev | grep "install ok installed")

if [ "" == "$STATUS_LIB_GTK" ]; then
	apt-get --yes install libgtk-3-dev
fi

