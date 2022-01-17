FROM python:latest


WORKDIR /home

COPY ./requirments.txt requirments.txt

RUN pip3 install -r requirments.txt

WORKDIR /home/pidcontrol

EXPOSE 8000
