FROM ubuntu:20.10 

# Add install artifacts
ARG COMMIT=''
ARG BUILD_TIME=''

# Working directory 
WORKDIR /usr/src/ 
COPY ./src /usr/src/ 

# Install dependencies 
RUN apt-get update && \ 
    apt-get install -y cmake build-essential git rapidjson-dev && \     
    apt install -y software-properties-common

# Install pistache     
# RUN add-apt-repository ppa:pistache+team/unstable && apt-get update && apt-get install -y libpistache-dev
RUN apt-get install -y meson
RUN apt-get install -y python3-distutils
RUN git clone https://github.com/pistacheio/pistache.git
RUN cd pistache
RUN meson setup build
RUN meson install -C build


# Build the service 
WORKDIR /usr/src/
# RUN mkdir build && cd build && \ 
#     cmake -DBUILD_TESTING=OFF -DWITH_EXAMPLES=OFF .. && \ 
#     make 

# Start the service 
# CMD ["./build/utask"] 
 
