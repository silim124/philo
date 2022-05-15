# philo
## 개요
스레드가 C에서 어떻게 작동하는지 이해하고, 운영체제의 교착상태를 설명하기 위한 문제인 '식사하는 철학자'를 해결해보는 것입니다. 모든 철학자가 충분히 먹거나, 철학자가 한명이라도 죽으면 시뮬레이션이 중지됩니다.
<br><br>
알고리즘에는 두 가지 버전이 있습니다.<br>
philo는 스레드와 뮤텍스에 관한 것입니다.<br>
philo_bonus는 프로세스와 세마포어에 관한 것입니다.<br>

## 프로젝트 빌드 및 실행
repo를 클론합니다
```shell
 git clone https://github.com/silim124/philo.git
```
루트 디렉토리로 이동한 다음 philo(or philo_bonus)로 이동하고 make를 실행합니다.
```c
 cd 42_philosophers/philo_one
 make
./philo arg1 arg2 arg3 arg4 (arg5)philo
```
<br>
arg1은 철학자의 수입니다.  <br>
arg2는 죽을 시간(ms)입니다.  <br>
arg3은 식사 시간(ms)입니다.  <br>
arg4는 ms 단위의 휴식 시간입니다.  <br>
arg5(선택 사항)는 각 철학자가 시뮬레이션을 종료하기 위해 먹어야 하는 시간입니다.  <br>

### 참고
- [유닉스 시스템 프로그래밍][1]
- [Mutex와 Semaphore의 차이][2]
- [fork 프로세스에서 sempahores를 사용하는 방법][3]

[1]: https://jihooyim1.gitbooks.io/unixbasic/content/contents/01.html
[2]: https://heeonii.tistory.com/14
[3]: https://stackoverflow.com/questions/16400820/how-to-use-posix-semaphores-on-forked-processes-in-c

