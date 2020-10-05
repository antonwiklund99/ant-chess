# Build cmd: docker build -t chess_bot:latest --build-arg CONFIG_YML="$(cat ~/Downloads/lichess-bot/config.yml)" .
# Run cmd: docker run --detach --rm chess_bot
FROM gcc:10
WORKDIR /app
COPY . .
RUN make clean
RUN make

FROM python:3
ARG CONFIG_YML
WORKDIR /app
RUN git clone https://github.com/ShailChoksi/lichess-bot.git
WORKDIR /app/lichess-bot
RUN pip install -r requirements.txt
RUN echo "$CONFIG_YML" > config.yml
COPY --from=0 /app/main engines/engine
CMD ["python", "lichess-bot.py"]