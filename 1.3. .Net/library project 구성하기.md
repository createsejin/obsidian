[이 문서](https://learn.microsoft.com/en-us/dotnet/core/tutorials/library-with-visual-studio-code?pivots=dotnet-8-0)를 참조했다.

루트 프로젝트 폴더를 하나 만든다. 그리고 그곳으로 들어간다.
```
dotnet new sln
```
최상단에 솔루션 파일을 만들었다.

```
dotnet new classlib -o MyLibrary
```
`-o` 옵션으로 해당되는 이름으로 그 하위 폴더에 library project를 만든다.

```
dotnet sln add MyLibrary/MyLibrary.csproj
```
루트 솔루션 파일에 라이브러리 프로젝트 파일을 추가해준다.

```
dotnet new console -o ShowCase
```
바이너리 라이브러리를 만든다.

```
dotnet sln add ShowCase/ShowCase.csproj
```
루트 솔루션 파일에 바이너리 라이브러리의 프로젝트 파일을 추가해준다.

바이너리 프로젝트로 폴더로 진입한다.
```
cd ShowCase
dotnet add reference ../MyLibarary.csproj
```
바이너리 프로젝트에 라이브러리 프로젝트 참조를 추가해준다. 

여기에서 유닛 테스트 코드를 추가하려면 [[NUnit Test|NUnit]]을 사용하는게 좋다. 