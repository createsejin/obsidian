우선은 MS의 공식 글인 [이곳](https://learn.microsoft.com/en-us/dotnet/core/tutorials/with-visual-studio-code?pivots=dotnet-8-0)을 참고해보자.

`dotnet new console --framework net8.0 --use-program-main`
이 명령어를 쓰자. 그러면 현재 디렉토리에 간단히 project template를 만들어준다.

`Program.cs`의 `class Program`이 entry point다. 

VSCode 기준, `Ctrl + backtick`을 눌러서 터미널을 열고 
`dotnet run`을 해보자.
program이 동작하며 Hello, world! 가 출력될 것이다.