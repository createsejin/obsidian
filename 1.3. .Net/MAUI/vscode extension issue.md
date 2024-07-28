<!-- ⚠️⚠️ Do Not Delete This! bug_report_template ⚠️⚠️ -->
<!-- Please read our Rules of Conduct: https://opensource.microsoft.com/codeofconduct/ -->
<!-- 🕮 Read our guide about submitting issues: https://github.com/microsoft/vscode/wiki/Submitting-Bugs-and-Suggestions -->
<!-- 🔎 Search existing issues to avoid creating duplicates. -->
<!-- 🧪 Test using the latest Insiders build to see if your issue has already been fixed: https://code.visualstudio.com/insiders/ -->
<!-- 💡 Instead of creating your report here, use 'Report Issue' from the 'Help' menu in VS Code to pre-fill useful information. -->
<!-- 🔧 Launch with `code --disable-extensions` to check. -->
Does this issue occur when all extensions are disabled?: Yes/No

<!-- 🪓 If you answered No above, use 'Help: Start Extension Bisect' from Command Palette to try to identify the cause. -->
<!-- 📣 Issues caused by an extension need to be reported directly to the extension publisher. The 'Help > Report Issue' dialog can assist with this. -->
- VS Code Version: 1.91.1
- OS Version: Windows 11 23H2

I'm trying to start the .Net MAUI project with the VSCode .Net MAUI extension. I installed .Net SDK and Android SDK through Visual Studio 2022 Installer. And I installed JDK 17.

Steps to Reproduce:
1. On Windows11, Start VSCode with administrator privilege
2. .Net New Project -> .Net MAUI App -> Create Project
3. Get a warning popup message: Android licenses not accepted. Accept the licenses or check the .NET MAUI output for more info.
4. Click 'Accept licenses' button on the popup message.
5. Get the following error in the MUAI extension task terminal:
```
 *  Executing task: & 'C:\Program Files (x86)\Android\android-sdk\cmdline-tools\11.0\bin\sdkmanager' --licenses --verbose 

ParserError: 
Line |
   1 |  … nsole]::InputEncoding = [System.Text.Encoding]::UTF8 -Command & 'C:\P …
     |                                                         ~~~~~~~~
     | Unexpected token '-Command' in expression or statement.
```
6. I'm trying to do this with the same command on my other Windows Terminal Powershell.
7. cd 'C:\Program Files (x86)\Android\android-sdk\cmdline-tools\11.0\bin'
8. .\sdkmanager --licenses --verbose
9. all agreements are accepted by "y"
```
  ---------------------------------------
  Accept? (y/N): y
  All SDK package licenses accepted
```
11. Restart VSCode with the same MAUI project
12. VSCode Still popup message: Android licenses not accepted. Accept the licenses or check the .NET MAUI output for more info.

When I started the VSCode debug run on the same MAUI project, I got a similar ParserError in the MAUI extension task terminal:
```
 *  Executing task: dotnet build -t:Build -p:Configuration=Debug -f net8.0-windows10.0.19041.0 -p:WindowsPackageType=None -p:CustomAfterMicrosoftCSharpTargets="c:\Users\creat\.vscode\extensions\ms-dotnettools.dotnet-maui-1.1.16-win32-x64\dist\resources\Custom.After.Microsoft.CSharp.targets" -p:_DeletePriConfigXml=True -v:normal C:\Users\creat\Projects\the_cave\tests\MAUI001\Notes\Notes\Notes.csproj 

ParserError: 
Line |
   1 |  … nsole]::InputEncoding = [System.Text.Encoding]::UTF8 -Command dotnet  …
     |                                                         ~~~~~~~~
     | Unexpected token '-Command' in expression or statement.
```

I have some relative setup scripts for the Powershell profile:
```
[Console]::InputEncoding = [Console]::OutputEncoding = [System.Text.Encoding]::UTF8
$PSDefaultParameterValues['*:Encoding'] = 'utf8'
```
So I did comment on these lines, but I still got the same problem.
