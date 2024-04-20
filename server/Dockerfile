FROM gcc

WORKDIR /backend/

COPY . .

ENV POSTGRES_USER=postgres
ENV POSTGRES_PASSWORD=postgres
ENV POSTGRES_DB=postgres
ENV POSTGRES_HOST=postgres
ENV POSTGRES_PORT=5432

ENV JWT_SECRET=secret

RUN apt-get update

RUN apt-get install -y cmake

RUN apt-get install -y python3

RUN apt-get install -y libxslt-dev libxml2-dev libpam-dev libedit-dev libssl-dev

EXPOSE 3000

CMD ["python3", "run.py"]