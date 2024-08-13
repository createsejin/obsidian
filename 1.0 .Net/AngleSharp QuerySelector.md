	[참고 article](https://code-maze.com/csharp-parsing-html-with-anglesharp/)

tagname `li`, `class=blue`
```csharp
var blueListItemElements = document.Body
  .QuerySelectorAll<IHtmlListItemElement>("li.blue")
  .ToList();

var blueListItemElementsLinq = document.All
  .Where(e => e.LocalName == "li" && e.ClassList.Contains("blue"))
  .ToList();
```

tagname `form`, `id=sign-up-form`
```csharp
var formElement = document.Body.QuerySelector<IHtmlFormElement>("form#sign-up-form");
```

using css selector
```csharp
var userNameInputElement = document.Body.QuerySelector<IHtmlInputElement>("form > input[name='username']");
```

tagname `input`, `name=username`
```csharp
var userNameInputElementLinq = document.All
  .First(e => e.LocalName == "input" && e.Attributes["name"]?.Value == "username");
```

by name
```csharp
var keyword_input = form.Elements["keywords"] as IHtmlInputElement;
```

by tagname, type and value
```csharp
var relevanceRadioButton = form.QuerySelector<IHtmlInputElement>(@"input[type='radio'][value='relevance']");
```