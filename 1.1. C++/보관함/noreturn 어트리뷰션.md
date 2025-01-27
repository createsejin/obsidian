# 
```cpp
[[noreturn]] void forceProgramTermination() { // 이 어트리뷰트를 지정하면 호출 지점으로 다시 돌아가지 않는다.  
    exit(1); // <cstdlib>에 정의됨  
}  
```

```cpp
bool isDongleAvilable() {  
    bool isAvailable {false};  
    // 라이선싱 동글을 사용할 수 있는지 확인하는 코드 ..    return isAvailable;  
}  
  
bool isFeatureLicensed(int featureId) {  
    if (!isDongleAvilable()) {  
        // 사용 가능한 라이선싱 동글이 없다면 프로그램을 종료한다.  
        forceProgramTermination();  
    } else {  
        bool isLicensed { featureId == 42};  
        // 동글이 있다면 주어진 기능에 대한 라이선스 검사를 한다.  
        return isLicensed;  
    }  
}  
  
void study013() {  
    /*addNumbers(3.4, 3.43);  
    func1();*/    bool isLicensed {isFeatureLicensed(42)};  
    cout << format("license is {}", isLicensed) << endl;  
}
```

>[[noreturn]]은 C++11에서 도입된 특수한 함수 속성(attribute)입니다. 이는 해당 함수가 반환하지 않음을 컴파일러에게 알리는 역할을 합니다. 즉, 해당 함수가 호출되면 실행 흐름이 호출 지점으로 다시 돌아오지 않음을 의미합니다.
>
>이 속성은 프로그램 종료나 예외 발생과 같이 실행 흐름이 원래의 위치로 돌아오지 않는 경우에 사용됩니다. 주어진 코드에서 `forceProgramTermination()` 함수는 프로그램을 종료하기 때문에 [[noreturn]] 속성이 적합합니다.
>
>그런데 [[noreturn]] 어트리뷰트를 제거하면 `non-void function does not return a value in all control paths` 경고가 발생하는 이유는, `isFeatureLicensed()` 함수의 모든 실행 경로에서 값이 반환되지 않기 때문입니다.
>
>`isFeatureLicensed()` 함수는 bool 값을 반환해야 하지만, `forceProgramTermination()` 호출 후에는 아무 값도 반환하지 않습니다. 그러나 [[noreturn]] 어트리뷰트가 없다면 컴파일러는 `forceProgramTermination()` 함수가 실제로 반환하지 않음을 인식하지 못하고, 그 결과 모든 경로에서 값이 반환되지 않았다고 판단하여 경고를 발생시킵니다.
>
>따라서 [[noreturn]] 어트리뷰트를 사용함으로써 이런 유형의 경고를 방지하고 코드의 의도를 더 명확하게 표현할 수 있습니다.

그러니까 isFeatureLicensed 함수에서 종료 코드로 인해 반환값을 모두 반환 하지 않을때 컴파일러는 경고를 발생시키는데, noreturn 어트리뷰션을 활용하면 미리 컴파일러에게 이 함수는 호출 지점으로 다시 돌아오지 않는다는걸 알려주므로써 경고 발생을 차단한다.