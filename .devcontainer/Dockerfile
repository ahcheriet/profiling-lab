# Use the official GCC image as base
FROM gcc:latest

# Create a non-root user for development
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Install essential profiling and debugging tools
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    binutils \
    valgrind \
    make \
    git \
    sudo \
    && groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the default user
USER $USERNAME

# Set working directory
WORKDIR /workspace
