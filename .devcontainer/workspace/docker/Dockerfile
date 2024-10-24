FROM mcr.microsoft.com/devcontainers/cpp:latest

RUN apt-get update -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    gh \
    && apt-get clean \
    && rm -rf /var/cache/apt/* /var/lib/apt/lists/

CMD [ "/bin/bash" ]
