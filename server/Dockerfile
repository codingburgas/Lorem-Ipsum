FROM gcc

WORKDIR /backend/

COPY . .

RUN apt-get update

RUN apt-get install -y cmake

RUN apt-get install -y python3

RUN apt-get install -y libxslt-dev libxml2-dev libpam-dev libedit-dev 

EXPOSE 3000

CMD ["python3", "run.py"]