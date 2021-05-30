# Operating system assignment
## #1. myshell-program

<h3> 목표  </h3>
 <b> 터미널에서 사용자로부터 명령어(command)를 입력받아 상호작용하는 myshell 프로그램 구현 </b>

<h3> 실행 </h3>

> make (makefile 이용)

<h3> 코드 컴파일 및 디버깅 </h3>

- gcc 설치
> sudo apt-get install gcc

- gdb 설치
> sudo apt-get install gdb

- 코드 컴파일 후 실행하기
> gcc myshell.c -o myshell <br>
> myshell

- 코드 디버깅
> gcc -g -o myshell_d myshell.c <br>
> gdb myshell_d

## #2. synchronization using mutex, semaphore

<h3> 목표  </h3>
 <b> 동기화 문제 해결 </b>

<h3> 실행 </h3>

> make (makefile 이용하여 두 개의 파일 동시에 컴파일)

<h3> 코드 컴파일 및 디버깅 </h3>

- 코드 컴파일 후 실행하기
> gcc synch_pthread.c -o synch_pthread -lpthread (-lpthread를 통해 pthread.h을 찾는다.) <br>
> synch_pthread <br>
> gcc synch_semaphore.c -o synch_semaphore -lpthread (-lpthread를 통해 pthread.h을 찾는다.) <br>
> synch_semaphore <br>

<hr>
<b> 개발 환경 : Ubuntu 20.04.1 LTS </b> <br>
<b> gcc version : gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 </b>
