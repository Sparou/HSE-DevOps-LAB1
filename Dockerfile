# Используем образ Ubuntu
FROM ubuntu:latest

# Обновляем необходимые пакеты для сборки и выполнения C++ приложения
RUN apt-get update && apt-get install -y g++

# Устанавливаем рабочую директорию внутри контейнера
WORKDIR /app

# Копируем исходный код вашего приложения внутрь контейнера
COPY main.cpp .

# Компилируем приложениеa
RUN g++ -o calculator main.cpp

# Определяем команду, которая будет выполняться при запуске контейнера
CMD [ "./calculator" ]