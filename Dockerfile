FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    gcc-11 \
	git \
	libbsd-dev \
	libxext-dev \
    make \
    && ln -sf /usr/bin/gcc-11 /usr/bin/gcc \
    && ln -sf /usr/bin/gcc-11 /usr/bin/cc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

CMD ["bash"]
