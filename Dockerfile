FROM gcc:latest as build
COPY . .
RUN g++ -static -o a.out main.cpp

FROM alpine 
COPY --from=build a.out a.out
COPY tests/input.txt input.txt
ENTRYPOINT sh -c './a.out <
