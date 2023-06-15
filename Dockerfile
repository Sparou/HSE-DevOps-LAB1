# Используем образ Ubuntu c GCC
FROM gcc:latest

# Копируем исходный код вашего приложения внутрь контейнера
COPY . .

# Компилируем приложениеa
RUN g++ -o calculator main.cpp

# Определяем команду, которая будет выполняться при запуске контейнера
CMD [ "./calculator < tests/input.txt > output.txt", "cat output.txt" ]