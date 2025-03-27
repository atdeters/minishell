#! /bin/bash

# Build the Docker image (this installs dependencies and compiles Minishell)
docker build -t minishell .

# Run Minishell inside a Docker container
docker run -it minishell
