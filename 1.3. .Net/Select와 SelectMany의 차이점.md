[문서](https://learn.microsoft.com/en-us/dotnet/api/system.linq.queryable.selectmany?view=net-8.0#system-linq-queryable-selectmany-2(system-linq-iqueryable((-0))
```csharp
class PetOwner
{
    public string Name { get; set; }
    public List<String> Pets { get; set; }
}

public static void SelectManyEx1()
{
    PetOwner[] petOwners =
        { new PetOwner { Name="Higa, Sidney",
              Pets = new List<string>{ "Scruffy", "Sam" } },
          new PetOwner { Name="Ashkenazi, Ronen",
              Pets = new List<string>{ "Walker", "Sugar" } },
          new PetOwner { Name="Price, Vernette",
              Pets = new List<string>{ "Scratches", "Diesel" } } };

    // Query using SelectMany().
    IEnumerable<string> query1 =
        petOwners.AsQueryable().SelectMany(petOwner => petOwner.Pets);

    Console.WriteLine("Using SelectMany():");

    // Only one foreach loop is required to iterate through the
    // results because it is a one-dimensional collection.
    foreach (string pet in query1)
        Console.WriteLine(pet);

    // This code shows how to use Select() instead of SelectMany().
    IEnumerable<List<String>> query2 =
        petOwners.AsQueryable().Select(petOwner => petOwner.Pets);

    Console.WriteLine("\nUsing Select():");

    // Notice that two foreach loops are required to iterate through
    // the results because the query returns a collection of arrays.
    foreach (List<String> petList in query2)
    {
        foreach (string pet in petList)
        {
            Console.WriteLine(pet);
        }
        Console.WriteLine();
    }
}

/*
    This code produces the following output:

    Using SelectMany():
    Scruffy
    Sam
    Walker
    Sugar
    Scratches
    Diesel

    Using Select():
    Scruffy
    Sam

    Walker
    Sugar

    Scratches
    Diesel
*/
```

여길 보면 `PetOwners`라는 배열은 `PetOwner` 객체들의 배열인데, `PetOwner` 객체는 `name`과 `Pets`라는 배열을 가지고 있다.
```csharp
IEnumerable<string> query1 =
        petOwners.AsQueryable().SelectMany(petOwner => petOwner.Pets);
```
먼저 `petOwners` 배열에 대해 `SelectMany`에서 배열의 각 요소인 `petOwner`에 대해 `petOwner.Pets`를 쿼리하고 있다. 그러면 여기에서는 `Pets` 배열에 담긴 요소들을 모두 모아서 한꺼번에 반환한다. 즉, 반환되는 `query1`은 각 pet들의 string값을 담고 있다. 따라서 여기에서는 `foreach`를 한번만 하면 모든 쿼리 요소를 출력할 수 있다.

```csharp
IEnumerable<List<String>> query2 =
        petOwners.AsQueryable().Select(petOwner => petOwner.Pets);
```
이와 달리 `petOwners` 배열에 대한 `Select`는 배열의 각 요소인 `petOwner`에 대해 `petOwner.Pets`를 쿼리하는데, 이때에는 `Pets`그 자체. 즉 쿼리 결과는 `Pets` List들에 대한 배열이다. 즉, 배열의 배열이기 때문에 `foreach`를 중첩해서 콘솔에 출력해야한다는 것.

나는 이것을 다음처럼 사용해봤다.
```csharp
    // 이미지 확장자 배열
    string[] img_extensions = ["*.jpg", "*.jpeg", "*.png"];
    var img_files = img_extensions
      .SelectMany(ext => Directory.EnumerateFiles(path, ext, SearchOption.AllDirectories));
    // 만약 img_files가 하나라도 있다면,
    if (img_files.Any())
    {
      // 그 이미지 파일들을 콘솔에 출력한다.
      foreach (var file in img_files)
      {
        Console.WriteLine($"{Path.GetFileName(file)}");
      }
      Console.WriteLine();
    }
```
`img_extensions` 배열에 대해 `SelectMany`를 이용해서 이 배열의 요소인 `ext`를 `Directory.EnumerateFiles` 메소드의 두번째 파라미터, 즉, search pattern에 사용한 것이다.  이것에 의해 `Directory.EnumerateFiles`가 반환하는 모든 요소들을 배열 변수 `img_files`에 담아서 그것이 하나라도 존재한다면 `foreach`를 이용해서 그 요소들인 `file`들을 출력하는 코드다.

즉, Select는 표현 람다식에서 반환되는 요소들을 모아서 `IEnumerable` 콜렉션으로 반환하고,
Where은 표현 람다식에서 true인 요소만 모아서 콜렉션으로 반환한다.