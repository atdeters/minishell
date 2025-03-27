# Use an official lightweight Linux image
FROM debian:latest  

# Install dependencies
RUN apt update && apt install -y build-essential libreadline-dev git  

# Copy your project into the container
COPY . /minishell  

# Set the working directory
WORKDIR /minishell  

# Build the Minishell program
RUN make  

# Run Minishell when the container starts
CMD ["./minishell"]
