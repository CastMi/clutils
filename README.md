Prerequisites:

	sudo apt-get install autoconf automake autotools-dev libtool-bin pccts

Briefly, the shell commands:

	autoreconf -fi && mkdir obj && cd obj && ../configure && make && sudo make install
