# Use jcsda/docker as base image
FROM jcsda/docker-gnu-openmpi-dev:1.9

RUN useradd -ms /bin/bash builder

# Set working directory
WORKDIR /home/builder

# Switch to the non-root user
USER builder

# Set default command
CMD ["/bin/bash"]