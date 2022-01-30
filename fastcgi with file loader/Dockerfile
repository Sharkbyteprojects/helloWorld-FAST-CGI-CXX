FROM ubuntu:latest

RUN apt-get update && apt-get install -y locales && rm -rf /var/lib/apt/lists/* \
    && localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8
WORKDIR /app

RUN apt-get update
RUN export DEBIAN_FRONTEND=noninteractive
RUN ln -fs /usr/share/zoneinfo/Europe/Berlin /etc/localtime
RUN apt-get install -y libfcgi-dev spawn-fcgi nginx curl build-essential
RUN dpkg-reconfigure --frontend noninteractive tzdata
RUN mkdir assets

COPY . .

#COMPILE
RUN g++ fastcgitest.cpp -lfcgi++ -lfcgi -o fastcgir

RUN chmod +x start.sh
WORKDIR /app
EXPOSE 80
CMD ["./start.sh"]
