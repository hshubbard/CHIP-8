FROM rockylinux:9

# Set working directory
WORKDIR /home/user

# Update and install required packages
RUN dnf upgrade --refresh -y && \
    dnf group install "Development Tools" -y && \
    dnf install -y vim tmux tree man man-pages mesa-dri-drivers mesa-libEGL SDL2 SDL2-devel xorg-x11-server-Xorg xorg-x11-xauth xorg-x11-utils

# Clean up
RUN dnf clean all

# Set the environment variable for the XDG runtime
ENV XDG_RUNTIME_DIR=/run/user/1000
ENV DISPLAY=host.docker.internal:0



