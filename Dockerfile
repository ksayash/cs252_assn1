FROM ubuntu
RUN apt-get update && apt-get install -y  build-essential
ADD ./images /images
ADD server.c /
RUN gcc -std=gnu99 -Wall server.c -o server
EXPOSE 5432
CMD ./server 
