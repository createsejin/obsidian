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
      Icon="{OnPlatform 'icon_notes.png', iOS='icon_notes_ios.png', MacCatalyst='icon_notes_ios.png'}"/><!--
    AppShell.X @#-->

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
    </HorizontalStackLayout><!-- 
    AboutPage.X @#-->
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