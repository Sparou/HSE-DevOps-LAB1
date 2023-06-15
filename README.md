# HSE-DevOps-LAB1

**Цель работы**: Ознакомиться с принципами непрерывной интеграции и непрерывной доставки (CI/CD), научиться создавать пайплайн сборки и выгрузки готовых артефактов с использованием GitHub Actions и технологии Docker.

<hr>

## Задачи и прогресс их выполнения

- [x] Создать приложение по вашему выбору (веб-приложение, мобильное приложение, консольное приложение и т.д.).
- [x] Настроить систему сборки и установить необходимые зависимости.
- [x] Создать простой пайплайн сборки в GitHub Actions.
- [x] Расширить пайплайн для выгрузки артефактов после успешной сборки.
- [x] Дополнить пайплайн выгрузкой артефактов во внешнюю систему (например, сервер, хранилище или облачный сервис).
- [x] Расширить пайплайн для упаковки приложения в Docker-контейнер.
- [x] Добавить шаги для выгрузки готового Docker-контейнера после успешной сборки в пайплайн и загрузки контейнера в Docker Hub.
- [x] Добавить дополнительные шаги в пайплайн, например, статический анализ кода, проверка стиля кодирования и другие полезные инструменты.
- [x] Добавить дополнительные этапы в пайплайн, например, развертывание приложения на тестовом сервере или контейнеризация приложения.
- [x] Добавить шаги для развертывания приложения на тестовом сервере или сборка на собственном подключенном агенте (можно использовать облачные сервисы или собственный ПК), если возможно.
- [x] Пайплайн в GitHub Actions настроен для автоматической сборки, тестирования и выгрузки артефактов при каждом пуше в репозиторий или создании Pull Request.

<hr>

## Навигация
- [HSE-DevOps-LAB1](#hse-devops-lab1)
  - [Задачи и прогресс их выполнения](#задачи-и-прогресс-их-выполнения)
  - [Навигация](#навигация)
  - [Создание приложения](#создание-приложения)
  - [Триггеры автоматической сборки и тестирования](#триггеры-автоматической-сборки-и-тестирования)
  - [Настройка системы сборки, установка зависимостей](#настройка-системы-сборки-установка-зависимостей)
    - [Сборка под Linux](#сборка-под-linux)
    - [Сборка под Windows](#сборка-под-windows)
  - [Выгрузка артефактов](#выгрузка-артефактов)
  - [Выгрузка артефактов во внешнюю систему](#выгрузка-артефактов-во-внешнюю-систему)
  - [Дополнительные шаги: статический анализ кода](#дополнительные-шаги-статический-анализ-кода)
  - [Дополнительные шаги: проверка форматирования](#дополнительные-шаги-проверка-форматирования)
  - [Контейнеризация](#контейнеризация)
    - [Dockerfile](#dockerfile)
    - [Создание контейнера и пуш в **docker hub**](#создание-контейнера-и-пуш-в-docker-hub)
    - [Развертывание на локальном ПК](#развертывание-на-локальном-пк)
  - [Тестирование](#тестирование)

<hr>

## Создание приложения 

В качестве приложения был выбран простейший калькулятор, написаный на **C++**

``` C++

#include <iostream>

int main() {

  while (true) {
      char op;
      float num1, num2;

      std::cin >> op;

      if (op == 'q')
      {
        return 0;
      }

      std::cin >> num1 >> num2;
      
      switch(op) {

        case '+':
          std::cout << num1 + num2 << std::endl;
          break;

        case '-':
          std::cout << num1 - num2 << std::endl;
          break;

        case '*':
          std::cout << num1 * num2 << std::endl;
          break;

        case '/':
          std::cout << num1 / num2 << std::endl;
          break;

        default:
          std::cout << "Error! operator is not correct" << std::endl;
          break;
      }
    }

  return 0;
}

```

<hr>

## Триггеры автоматической сборки и тестирования 

Автоматическая сборка и тестирование проекта запускаются при **push** или **pull request** в **main**.

```yml
on:
  push:
    branches:
      - main
  pull_request:
    branches:
      - main
```

<hr>


## Настройка системы сборки, установка зависимостей

В моей реализации проект собирается под две операционные системы: **Windows** и **Linux**. 

### Сборка под Linux

Данная система не требует установки дополнительных компонентов для успешной сборки проекта.

```yml
  build_on_linux:
    # Указываем систему, на который будем билдить проект
    runs-on: ubuntu-latest

    # Клонируем репозиторий
    steps:
      - name: Checkout repository
        uses: actions/checkout@v3

    # Компилируем main.cpp под Linux
      - name: Build Project
        run: |
          g++ -o calculator main.cpp
```


### Сборка под Windows

В отличие от **Linux**, **Windows** требует установки компилятора. Так как проект был крошечным и мне требовалось скомпилировать только один файл, выбор пал на **Clang**.

```yml
 build_on_windows:
    runs-on: windows-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v3

      # Устанавливаем Clang как компилятор для Windows
      - name: Set up Clang
        uses: egor-tensin/setup-clang@v1
        with:
          version: latest
          platform: x64

      # Билдим проект под Windows
      - name: Build with Clang
        run: |
          clang++ main.cpp -o calculator.exe

      - name: Upload Artifact
        uses: actions/upload-artifact@v3
        with:
          name: calculator.exe
          path: calculator.exe
```

<hr>

## Выгрузка артефактов

```yml
      - name: Upload Artifact
        uses: actions/upload-artifact@v3
        with:
          name: calculator
          path: calculator
```

<hr>

## Выгрузка артефактов во внешнюю систему

В качестве внешней системы был выбран удобный и простой в использовании **Telegram**. В **Telegram** отправляется версия под **Windows**, так как это моя основная операционная система. Важно отметить, что данная джоба не компилирует проект, а скачивает готовый артефакт и отправляет его мне в личные сообщения.

```yml

  send_to_telgram:
    needs: build_on_windows
    runs-on: ubuntu-latest
    
    steps:    

      - name: Checkout repository
        uses: actions/checkout@v3

      - uses: actions/download-artifact@v3
        with:
          name: calculator.exe

      - name: Archive C++ Application
        run: |
          7z a calculator.7z calculator.exe

      - name: Send Telegram message
        uses: appleboy/telegram-action@master
        with:
            to: ${{ secrets.TELEGRAM_CHAT_ID }}
            token: ${{ secrets.TELEGRAM_BOT_TOKEN }}
            message: Windows Application
            document: calculator.7z    

```

<hr>

## Дополнительные шаги: статический анализ кода

Для статического анализа кода было выбрано популярное расширение на **GitHub Markeplace "Codacy"**. Для самого анализа использовались стандартные настройки этого расширения.

Codecy URL: https://github.com/marketplace/actions/codacy-analysis-cli

```yml
  # Анализ кода с помощью Codacy
  analyse_code:
    runs-on: ubuntu-latest
    
    steps:
      - name: Checkout repository
        uses: actions/checkout@v3

      - name: Run Codacy Analysis CLI
        uses: codacy/codacy-analysis-cli-action@master
```

<hr>

## Дополнительные шаги: проверка форматирования

**Formatting Check** ищет в репозитории **.clang-format** и, если находит, проверяет существующий код на корректность форматирования согласно стилю, заданному в **.clang-format**.

```yml
  # Проверка корректности форматирования
  formatting-check:
    name: Formatting Check
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Run clang-format style check for C/C++/Protobuf programs.
        uses: jidicula/clang-format-action@v4.11.0
        with:
          clang-format-version: '13'
          check-path: 'src'
```
<hr>

## Контейнеризация

### Dockerfile

Используемый **Dockerfile**:

```Dockerfile
FROM gcc:latest as build
COPY . .
RUN g++ -static -o a.out main.cpp

FROM alpine 
COPY --from=build a.out a.out
COPY tests/input.txt input.txt
CMD sh -c './a.out < input.txt'
```

Последняя строчка обсуловлена тем, что мы не имеем прямого доступа к консоли, в который агент запускает программу, так что стандартный поток ввода заменяется файлом **input.txt**.

### Создание контейнера и пуш в **docker hub**

Для успешной контейнеризации и пуша готового докер-образа на **docker hub** использоваль расширения из **GitHub Marketplace**. docker/**login-action@v2** выполняет авторизацию, **docker/setup-buildx-action@v2** создает и загружает билдер для последующей сборки, а **docker/build-push-action@v4** собирает **docker image** и результат пушит в **docker hub**.

```yml
  docker_application:
    runs-on: ubuntu-latest
    steps:
      -
        name: Checkout
        uses: actions/checkout@v3
      -
        name: Login to Docker Hub
        uses: docker/login-action@v2
        with:
          username: ${{ secrets.DOCKERHUB_USERNAME }}
          password: ${{ secrets.DOCKERHUB_TOKEN }}
      -
        name: Set up Docker Buildx
        uses: docker/setup-buildx-action@v2
      -
        name: Build and push
        uses: docker/build-push-action@v4
        with:
          context: .
          file: ./Dockerfile
          push: true
          tags: ${{ secrets.DOCKERHUB_USERNAME }}/calculator:latest

```


### Развертывание на локальном ПК

Для того, чтобы развернуть приложение на собственном ПК я создал **self-hosted** раннер, а после реализовал еще один **job**.

```yml
 deploy_to_local_machine:
    name: Deploy to local machine
    runs-on: self-hosted
    needs: docker_application

    steps:
      - name: Pull docker image to local machine
        run: |
          docker pull ${{ secrets.DOCKERHUB_USERNAME }}/calculator:latest

      - name: Run docker container on local machine
        run: |
          docker run ${{ secrets.DOCKERHUB_USERNAME }}/calculator:latest
```


<hr>

## Тестирование

Автоматическое тестирование также присутствует в проекте и ввиду простоты программы реализовано методом банального сравнения **output.txt** и **expected_output.txt**. Также, как и в случае отправки артефактов в телеграм на этот **job** установлена зависимость, которая позволяет ему выполниться только после выгрузки свежего артефакта.

```yml
  tests:
    needs: build_on_linux
    runs-on: ubuntu-latest
    

    steps:
      
      - name: Checkout repository
        uses: actions/checkout@v3

      - uses: actions/download-artifact@v3
        with:
          name: calculator

      - name: Change file permissions
        run: chmod +x calculator

      - name: Run tests
        run: |
          ./calculator < tests/input.txt > output.txt

      - name: Check test results
        run: |
          diff output.txt tests/expected_output.txt
```
