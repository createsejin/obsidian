죄송합니다, 이해를 잘못하고 있었습니다. 원하시는 것은 실시간으로 체스 보드를 업데이트하고 출력하지만 개행하지 않는 라이브러리를 찾고 계신 것이군요.

C++에서는 콘솔 화면을 제어하는 기능을 제공하는 라이브러리가 제한적이기 때문에 개행 없이 실시간으로 출력을 업데이트하는 것은 어려울 수 있습니다. 일반적으로 콘솔 화면에서는 출력을 개행하여 새로운 내용을 표시하거나, 기존 출력을 지우고 다시 그리는 방식으로 화면을 업데이트합니다.

하지만 조금 더 다양한 기능을 제공하는 라이브러리로는 "ncurses"가 있습니다. "ncurses"는 터미널 기반의 사용자 인터페이스를 구현하는 데 사용되는 라이브러리로, 콘솔 화면을 좀 더 유연하게 제어할 수 있습니다. "ncurses"를 사용하면 키 입력을 받을 수도 있고, 색상을 변경하거나 화면을 분할할 수도 있습니다.

"ncurses" 라이브러리는 C 언어로 작성되었지만, C++에서도 사용할 수 있습니다. Vcpkg를 통해 "ncurses"를 설치하고, C++에서 사용하는 방법은 다음과 같습니다.

터미널에서 vcpkg 디렉토리로 이동한 후 "ncurses" 라이브러리를 설치합니다.
```
$ ./vcpkg install ncurses
```

C++ 프로젝트의 CMakeLists.txt 파일에 다음과 같이 "ncurses" 라이브러리를 추가합니다.

```cmake

find_package(Curses REQUIRED)
target_link_libraries(프로젝트명 PRIVATE ${CURSES_LIBRARIES})

아래는 "ncurses" 라이브러리를 사용한 간단한 예제 코드입니다.
```

```cpp

    #include <ncurses.h>
    #include <unistd.h>

    int main() {
        initscr();  // ncurses 초기화
        noecho();   // 입력 문자 출력 안 함
        curs_set(0);  // 커서 숨김
        timeout(0);  // 입력 대기 시간 없음

        const int BOARD_WIDTH = 8;
        const int BOARD_HEIGHT = 8;

        char board[BOARD_HEIGHT][BOARD_WIDTH] = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
        };

        while (true) {
            clear();  // 화면 지우기

            // 체스 보드 출력
            for (int i = 0; i < BOARD_HEIGHT; i++) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    mvprintw(i, j * 2, "%c ", board[i][j]);
                }
            }

            refresh();  // 화면 업데이트

            // 임시로 보드 상태 변경
            board[1][1] = 'x';

            usleep(100000);  // 0.1초 대기
        }

        endwin();  // ncurses 종료

        return 0;
    }
```

위 예제 코드에서는 "ncurses" 라이브러리를 사용하여 콘솔 화면을 초기화하고, 체스 보드를 출력하는 기능을 구현하였습니다. clear() 함수를 사용하여 화면을 지우고, mvprintw() 함수를 사용하여 체스 보드를 출력하고, refresh() 함수를 사용하여 화면을 업데이트합니다. 또한, usleep() 함수를 사용하여 잠시 대기하는 시간을 추가하였습니다.

"ncurses" 라이브러리를 사용하면 콘솔 화면을 좀 더 유연하게 제어할 수 있으므로, 실시간으로 체스 보드를 업데이트하고 출력하는 데에 도움이 될 수 있습니다. 추가로 궁금한 점이 있으면 언제든지 물어보세요!