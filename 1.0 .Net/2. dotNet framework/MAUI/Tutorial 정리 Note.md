`MauiProgram.cs`는 MAUI app의 Entry Point이다.
각 페이지는 모두 `.xaml`과 `.cs`가 짝궁이며 XAML은 UI의 요소를 만들어주고, cs 파일은 그 page의 code base이다.

`AppShell.xaml`은 각 page들의 visual hierarchy를 나타낸다. 

`xmlns:models="clr-namespace:Notes.Models"`
이런식으로 .Net namespce인 `Notes.Models`과 XML namespce인 `models`를  mapping 할 수 있다.

AppShell.xaml을 살펴보자.
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<Shell
  x:Class="Notes.AppShell"
  xmlns="http://schemas.microsoft.com/dotnet/2021/maui"
  xmlns:x="http://schemas.microsoft.com/winfx/2009/xaml"
  xmlns:views="clr-namespace:Notes.Views"
  Shell.FlyoutBehavior="Disabled">

  <TabBar>
    <ShellContent
      Title="Notes"
      ContentTemplate="{DataTemplate views:NotePage}"
      Icon="{OnPlatform 'icon_notes.png', iOS='icon_notes_ios.png', MacCatalyst='icon_notes_ios.png'}"/>

    <ShellContent
      Title="About"
      ContentTemplate="{DataTemplate views:AboutPage}"
      Icon="{OnPlatform 'icon_about.png', iOS='icon_about_ios.png', MacCatalyst='icon_about_ios.png'}"/>
  </TabBar>
</Shell>
```
우선 `xmlns:views="clr-namespace:Notes.Views"`를 통해서 XML의 namespace인 `views`와 .Net의 namespace인 `Notes.Views`를 mapping하고 있다. 이러한 namespace mapping을 통해 `TabBar`의 `ShellContent`에서 `ContentTemplate="{DataTemplate views:NotePage}"`과 같이 XML namespace를 통해서 각 페이지를 불러오고 있다.

NotePage.xaml을 살펴보자.
```xml
<?xml version="1.0" encoding="utf-8" ?>
<ContentPage xmlns="http://schemas.microsoft.com/dotnet/2021/maui"
             xmlns:x="http://schemas.microsoft.com/winfx/2009/xaml"
             xmlns:models="clr-namespace:Notes.Models"
             x:Class="Notes.Views.AboutPage">
  <ContentPage.BindingContext>
    <models:About/> <!--instance of About-->
  </ContentPage.BindingContext>
  <VerticalStackLayout Spacing="10"
                       Margin="10">
    <HorizontalStackLayout Spacing="10">
      <Image Source="dotnet_bot.png"
             SemanticProperties.Description="The dot net bot waving hello!"
             HeightRequest="64"/>
      <Label FontSize="22"
             FontAttributes="Bold"
             Text="{Binding Title}"
             VerticalOptions="End"/>
      <Label FontSize="22"
             Text="{Binding Version}"
             VerticalOptions="End"/>
    </HorizontalStackLayout>
    <Label Text="{Binding Message}"/>
    <Button Text="Learn more..."
            Clicked="LearnMore_Clicked"/>
  </VerticalStackLayout>
</ContentPage>
```
이런식으로 만들어지는데, 가장 root는 `ContentPage`이며, 여기에서 `xmlns:models="clr-namespace:Notes.Models"`는 XML namespce인 `models`와 .Net namespace인 `Notes.Models`를 mapping하고 있다.  
`x:Class="Notes.View.AboutPage"`는 이 XAML과 연관된 code base가 `Notes.View.AboutPage`임을 나타내고 있다.
그리고 루트의 첫번째 child node인 `ContentPage.BindingContext`에서는 `<models:About/>`을 통해서 XML namespace `models`에 .Net `About` 클래스의 인스턴스를 생성하고 있다. 
이 instance는 추후에 `Label` node에서 `Text="{Binding Title}"`, `Text="{Binding Version}"`과 같은 형식으로 사용되고 있다. `Binding`으로 시작해서 뒷 부분에 `About` 클래스의 property 이름을 통해서 값을 불러온 것이다. 

그리고 밑에 보면 `Button`이 있는데, 여기에서는 namespace와 관련된게 없다. 따라서 이 XAML과 짝궁인 `AboutPage.xaml.cs` code base의 `LearnMore_Clicked` 메서드가 이 버튼의 Clicked Event를 handling할 메서드라고 지정하고 있는것이다.

이제 AllPage를 분석해보자.
일단 AppShell은 다음과 같이 바뀌었다.
```XML
<?xml version="1.0" encoding="UTF-8" ?>
<Shell
  x:Class="Notes.AppShell"
  xmlns="http://schemas.microsoft.com/dotnet/2021/maui"
  xmlns:x="http://schemas.microsoft.com/winfx/2009/xaml"
  xmlns:views="clr-namespace:Notes.Views"
  Shell.FlyoutBehavior="Disabled">

  <TabBar>
    <ShellContent
      Title="Notes"
      ContentTemplate="{DataTemplate views:AllNotesPage}"
      Icon="{OnPlatform 'icon_notes.png', iOS='icon_notes_ios.png', MacCatalyst='icon_notes_ios.png'}"/>

    <ShellContent
      Title="About"
      ContentTemplate="{DataTemplate views:AboutPage}"
      Icon="{OnPlatform 'icon_about.png', iOS='icon_about_ios.png', MacCatalyst='icon_about_ios.png'}"/>
  </TabBar>
</Shell>
```
여기에서 이제 `TabBar`의 첫번째 요소는 `views:AllNotesPage`로 바뀌었다. ^a

```csharp
using Notes.Models;
namespace Notes.Views;

public partial class AllNotesPage : ContentPage
{
	public AllNotesPage()
	{
		InitializeComponent();

    BindingContext = new AllNotes();
	}
```
이것은 `AllNotesPage.xaml.cs`의 첫머리다. 
여기서 눈여겨볼 점은 `BindingContext`가 `AllNotes`인 것인데, `AllNotes`는 `.Models`의 model class이다. 

`AllNotes`를 살펴보면 
```csharp
internal class AllNotes
{
  private readonly string _downloadPath = @"C:\Users\creat\Downloads";
  public ObservableCollection<Note> Notes { get; set; } = []; 
  public AllNotes() => LoadNotes();
  public void LoadNotes()
  {
    Notes.Clear();
    var notes = Directory.EnumerateFiles(_downloadPath, "*.notes.txt")
      .Select(filename => new Note() {
        FileName = filename,
        Text = File.ReadAllText(filename),
        Date = File.GetCreationTime(filename)
      })
      .OrderBy(note => note.Date);
    foreach(var note in notes)
    {
      Notes.Add(note);
    }
  } 
}
```
일단 `LoadNotes`를 보면 처음에 `Notes` collection을 clear하고 있고, `_downloadPath`에서 note들의 파일을 읽어서 `Select`를 통해 `Note` 객체로 변환하고 있다. 그 후 `OrderBy`를 통해서 `Note` 객체들을 `Date`에 따라 정렬하고 있다. 그리고 마지막에 이 `notes`를 순회하며 `Notes` 배열에 `Note` 객체들을 하나씩 넣고있다. 이 메서드를 통해서 `AllNotes`를 초기화하고 있다. 그런데 엄밀히 말하면 `public AllNotes() => LoadNotes();` 이런 형태는 진정한 초기화는 아니다. 아마도 Lazy initialization 인것 같다. 

그럼 이제 `AllNotesPage.xaml`을 보자
```xml
<?xml version="1.0" encoding="utf-8" ?>
<ContentPage xmlns="http://schemas.microsoft.com/dotnet/2021/maui"
             xmlns:x="http://schemas.microsoft.com/winfx/2009/xaml"
             x:Class="Notes.Views.AllNotesPage"
             Title="AllNotesPage">
  <ContentPage.ToolbarItems>
    <ToolbarItem Text="Add"
                 Clicked="Add_Clicked"
                 IconImageSource="{FontImage Glyph='+', Color=Black, Size=22}"/>
  </ContentPage.ToolbarItems>
  <!-- Display notes in a list -->
  <CollectionView x:Name="notesCollection"
                  ItemsSource="{Binding Notes}"
                  Margin="20"
                  SelectionMode="Single"
                  SelectionChanged="NotesCollection_SelectionChanged">

    <!-- Designate how the collection of items are laid out -->
    <CollectionView.ItemsLayout>
      <LinearItemsLayout Orientation="Vertical"
          ItemSpacing="10"/>
    </CollectionView.ItemsLayout>

    <!-- Define the appearance of each item in the list -->
    <CollectionView.ItemTemplate>
      <DataTemplate>
        <StackLayout>
          <Label Text="{Binding Text}"
              FontSize="22"/>
          <Label Text="{Binding Date}"
              FontSize="14"
              TextColor="Silver"/>
        </StackLayout>
      </DataTemplate>
    </CollectionView.ItemTemplate>
  </CollectionView>
</ContentPage>
```
일단 `x:Class`에서는 `AllNotesPage`를 가리키고 있는데 이것은 이 xaml의 짝궁인 `AllNotesPage.xaml.cs`의 `AllNotesPage` class이다.
그 다음에는 `ToolbarItem`을 넣고 있다. 이 Add를 누르면 `AllNotesPage` class의 `Add_Clicked`가 호출될 것이다.
그 아래에는 `CollectionView`가 사용되고 있다.  여기에서 `ItemsSource="{Binding Notes}"`가 사용되고 있는데, 앞서 `AllNotesPage.xaml.cs`의 첫머리에서 
`BindingContext = new AllNotes();`를 통해서 현재 바인딩된 context는 `.Models`의 `AllNotes` class이다. 따라서 `AllNotes` class의 `ObservableCollection<Note> Notes` 가 `ItemsSource`로 사용되고 있다. 그 밑에는 `ItemLayout`으로 이 `CollectionView`가 어떻게 나열될건지 설정하고 있고, 그 밑에는 `ItemTemplate`를 통해 `StackLayout`으로 두 개의 `Label`이 표시되는데, 여기서는 앞선 `ItemSource`의 요소들이 바인딩되고 있다. `Note` 객체의 `Text`, `Date` 속성이 `Label`의 `Text`에 쓰이고 있다.

이제 `AllNotesPage.xaml.cs`의 나머지 부분을 살펴보자.
```csharp
  protected override void OnAppearing()
  {
    ((AllNotes)BindingContext).LoadNotes();
  }
```
이 부분은 `AllNotesPage`가 노출될때마다 실행된다. 여기에서는 현재 `BindingContext`는 `AllNotes` 모델 객체인데, 다시 역으로 `BindingContext`를 `AllNotes`로 캐스팅해서 `LoadNotes` 메서드를 부르고있다. 이 메서드는 `_downloadPath`의 파일들을 읽어서 각 `Note`들을 만들고 이것을 `Notes` collection에 담고, `AllNotesPage`에서 `CollectionView`에 표시한다. 
```csharp
  private async void Add_Clicked(object sender, EventArgs e)
  {
    await Shell.Current.GoToAsync(nameof(NotePage));
  }
```
이 부분은 Add 버튼을 누르면 실행되는데, `NotePage`로 이동하도록 하고 있다. `NotePage`에서는 노트를 작성하고 save 하거나 delete할 수 있다.

```csharp
  private async void NotesCollection_SelectionChanged(object sender, SelectionChangedEventArgs e)
  {
    if (e.CurrentSelection.Count != 0)
    {
      var note = (Note)e.CurrentSelection[0];
      await Shell.Current.GoToAsync($"{nameof(NotePage)}?{nameof(NotePage.ItemId)}={note.FileName}");
      notesCollection.SelectedItem = null;
    }
  }
```
그 다음은 `NotesCollection_SelectionChanged` 메서드인데, `AllNotesPage`에서 `CollectionView`에 `SelectionChanged="NotesCollection_SelectionChanged"`로 설정되어있다.
이것은 `CollectionView`의 요소를 선택이 바뀔때마다 이 메서드를 호출한다는 것인데,  메서드를 살펴보면 `SelectionChangedEventArgs e` 이벤트 변수가 메서드 매개변수로 사용되고 있고, 그 안에서 만약 `e.CurrentSelection.Count != 0`이면 `var note = (Note)e.CurrentSelection[0]`를 통해 현재 선택한 요소의 `Note` 객체 `note`를 가져오고 있다. 
그 다음에는 다소 복잡한 표현식이 사용되었는데, 아마도 웹페이지에서 특정 item을 찾는 주소와 유사하다. 이것을 URI라고 부르는것 같다. 
`NotePage?ItemId=path\on\device\XYZ.notes.txt` 이런식으로 표현되는것 같다.

`NotePage.xaml.cs`를 살펴보면,
```csharp
[QueryProperty(nameof(ItemId), nameof(ItemId))]
public partial class NotePage : ContentPage
{
  private readonly string _noteName = "notes.txt";
  private readonly string _downloadPath = @"C:\Users\creat\Downloads";
  private readonly string _fileName = string.Empty;
  public string ItemId { set => LoadNote(value); }
```
이런식으로 되어있는데.. 솔직히 `QueryProperty`가 왜 저렇게 됐는지는 잘 모르겠지만.. 아마도 `ItemId`라는 속성에 `ItemId` class 속성을 부여한다라는 뜻 같은데.. 이름이 똑같아서 사실 뭐가 뭔지는 잘 구분이 안된다. 

또한 `public string ItemId { set => LoadNote(value); }` 이 부분도 다소 의문이다.
`LoadNote`는 다음과 같이 되어있는데.. 
```csharp
  private void LoadNote(string file_name)
  {
    Note note_model = new() { FileName = file_name };
    if (File.Exists(file_name))
    {
      note_model.Date = File.GetCreationTime(file_name);
      note_model.Text = File.ReadAllText(file_name);
    }
    BindingContext = note_model;
  }
```
그러니까 저기에서 `value`는 이 `LoadNote` 메서드를 보면 `string file_name`인데. 의문인 점은 `LoadNote`가 void 인데 이걸 `set =>`에 넘긴다? 그러니까 `ItemId`가 set될때 이 메서드를 불러서 `Note` 모델을 `BindingContext`로 설정한다 라는것 같다.

```csharp
  private async void SaveButton_Clicked(object sender, EventArgs e)
  {
    // Save the file.
    if (BindingContext is Note note)
      File.WriteAllText(note.FileName, TextEditor.Text);
    await Shell.Current.GoToAsync("..");
  }
  private async void DeleteButton_Clicked(object sender, EventArgs e)
  {
    if (BindingContext is Note note)
    {
      if (File.Exists(note.FileName)) File.Delete(note.FileName);
    }

    await Shell.Current.GoToAsync("..");
  }
```
그리고 마지막으로 `NotePage`에서 Save 버튼과 Delete 버튼에 대한 동작을 정의하고 있는데, 먼저 Save 버튼에서는 만약 `BindingContext`가 `Note` type이면 `TextEditor.Text`를 `note` 객체의 파일로 쓴뒤에 `await Shell.Current.GoToAsync("..")`를 통해 뒤로 가기를 하고 있다. 이 경우에는 `AllNotesPage`가 나올것이다.

Delete 버튼을 눌렀을때에는 똑같이 `BindingContext`가 `Note`일때 만약 그 `note` 객체의 파일이 존재한다면 그걸 지운뒤 뒤로가기를 하고 있다.

마지막으로 Add 버튼을 눌렀을때 `NotePage`로 Navigate하기 위해서 `AppShell.xaml.cs`에 이것을 등록해줘야한다.
```csharp
public partial class AppShell : Shell
{
	public AppShell()
	{
		InitializeComponent();

    Routing.RegisterRoute(nameof(NotePage), typeof(NotePage));
	}
}
```
이런식으로 등록해주면 된다. `AppShell.xaml`의 첫번째 탭에 `AllNotesPage`를 등록하는건 [[#^a|앞 코드]]에서 살펴봤다.