*This project has been created as part of the 42 curriculum by saan, hwiskim.*

# Discription

2차원 평면의 정보를 기반으로 3차원 공간을 구현하는 프로젝트. mlx 라이브러리를 사용하여 파일의 유효성 검사를 수행하고 `.cub` 확장자를 가진 파일 내부에 정의된 정보로 3차원을 렌더링 한다.

## 1. 프로젝트의 목적

초기 울펜슈타인의 렌더링 알고리즘인 raycasting을 이해하고 구현한다. <br>
## 2. 프로세스

실행 시 `.cub` 파일을 인자로 받는다.<br>
해당 파일에 정의된 요소들의 유효성을 검사한다.<br>
<br>
이후 실제로 사용할 데이터들을 초기화하고, raycasting으로 계산된 거리를 사용하여 화면에 렌더링한다.<br>
<br>
렌더링 사이 델타 타임으로 연산속도에 따른 이동속도 보정및 프레임 고정한다.
<br>
## 3. 주의사항

헤더파일에 미리 정의된 크기의 texture 파일이 아닐경우 실행되지 않는다. <br>
<br>
미리 준비된 texture 파일이 수정된다면 프로그램이 실행되지않을 가능성이 높다. <br>
<br>
현재 프로젝트의 시뮬레이션은 종료조건이나 클리어 조건이 없으므로<br>
종료를 원할 시 ESC키 혹은 우측 상단 윈도우의 'x'을 클릭 한다.<br>
<br><br>


# Instructions

intra의 프로젝트 페이지에서 minilibx-linux.tgz를 다운받는다.<br>
이후 현재 프로젝트 root폴더에서 압축을 풀고 압축을 푼 폴더의 이름을 mlx로 변경한다.<br>
<br>
현재 프로젝트의 root폴더에서 터미널을 연다.<br>
```bash
make
```
위 커맨드로 컴파일 한다.

<br>

```bash
./cub3D {path_of_.cub_file}
```
위 방법으로 프로그램을 실행시킨다.

keymap<br>
---
W : 앞<br>
A : 왼쪽<br>
S : 오른쪽<br>
D : 뒤<br>

<- : 왼쪽으로 회전<br>
-> : 오른쪽으로 회전<br>

ESC : 종료<br>

<br>

```bash
make clean
```
위 커맨드로 obj파일을 지울 수 있다.

<br>

```bash
make fclean
```
위 커맨드로 obj파일과 프로그램을 지울 수 있다.

<br>

# Resources

[raycasting tutorial 한글번역]<https://github.com/365kim/raycasting_tutorial/tree/master><br>
[raycasting tutorial]https://www.youtube.com/watch?v=g8p7nAbDz6Y<br>
[raycasting의 이해]https://sikpang.tistory.com/32<br>
[회전 행렬]https://xoft.tistory.com/109<br>
[델타 타임]https://blog.naver.com/since_1992_/221412390449<br>
<br><br>

# AI가 사용된곳
<br>

```C
static void	draw_wall_column(t_game *g, int x, int top, int bot)
```
화면에 찍을 texture의 위치값 비율 계산방법.<br>
최적화를 위한 고정 소수점 shift연산.<br>

```C
void	put_pixel(t_game *g, int x, int y, int color)
```
연산 최적화를 위한 연산 및 인덱스 접근 아이디어.

__벡터 연산 및 표현의 이해__<br>
__valgrind에서 검출된 누수 및 오류 분석 (gnl의 static누수, invalid read 등)__<br>
__현재 Readme 번역__<br>
__전반적인 멘탈케어__<br>
